#By Erick Chicatto
#This code send data to PCAN using crc algorithms
#2 Jan 2025 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <https://www.gnu.org/licenses/>.


import can
import logging
import time

logging.basicConfig(level=logging.INFO)

# Config the channel
def powerOffCan(bus):
    """
    Power off the bus
    """
    try:
        bus = can.Bus(interface="pcan", channel="PCAN_USBBUS1", bitrate=500000)
        print("Canal inicializado correctamente")
        bus.shutdown()
    except can.CanError as e:
        print(f"Error inicializando el bus : {e}")

# Reset channel
def reset_bus(bus):
    """
    Reset the bus
    """
    try:
        bus.reset()
        print("Bus reiniciado con éxito")
    except Exception as e:
        print(f"Error reiniciando el bus: {e}")

# Calculate the Checksum  
def compute_xbr_checksum(message, counter):
    """
    Computes an XBR checksum per SAE J1939 SPN 3188.
    """
    checksum = sum(message.data[:7])
    checksum += sum(message.arbitration_id.to_bytes(length=4, byteorder="big"))
    checksum += counter & 0x0F
    xbr_checksum = ((checksum >> 4) + checksum) & 0x0F
    return xbr_checksum

# Build the message 
def build_crc_msg(msg):
    """
    Build the message with crc
    """
    messages = []
    
    for counter in range(16):
        checksum = compute_xbr_checksum(msg, counter)
        msg.data[7] = counter + (checksum << 4)  # El último bit 7 es el del checksum
        messages.append(
            can.Message(arbitration_id=msg.arbitration_id, data=msg.data[:])  # Pasar la lista completa 
        )
    return messages


# Send crc message
def crc_send(bus):
    """
    Sends periodic messages every 1 s with no explicit timeout. Modifies messages
    after 8 seconds, sends for 10 more seconds, then stops.
    """
    msg = can.Message(arbitration_id=0x12345678, data=[1, 2, 3, 4, 5, 6, 7, 0])
    messages = build_crc_msg(msg)
    
    print("Starting to send a message with updating counter and checksum every 1 s for 8 s")
    
    task = bus.send_periodic(messages, 1)
    assert isinstance(task, can.CyclicSendTaskABC)
    time.sleep(8)
    
    msg = can.Message(arbitration_id=0x12345678, data=[8, 9, 10, 11, 12, 13, 14, 0])
    messages = build_crc_msg(msg)

    print("Sending modified message data every 1 s for 10 s")
    task.modify_data(messages)
    time.sleep(10)
    task.stop()
    print("Stopped cyclic send")   
    
    
if __name__ == "__main__":
    with can.Bus(interface="pcan", channel="PCAN_USBBUS1", bitrate=500000) as bus:
        while True:
            crc_send(bus)
            time.sleep(1)



