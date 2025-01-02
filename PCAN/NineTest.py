"""
By Erick Chicatto
This code send data to PCAN
1 Jan 2025 7

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

"""

import can
import time
import pdb

def reset_bus(bus):
    try:
        bus.reset()
        print("Bus reiniciado con éxito.")
    except Exception as e:
        print(f"Error reiniciando el bus: {e}")

def send_can_message(bus, arbitration_id, data):
    msg = can.Message(
        arbitration_id=arbitration_id,
        data=data,
        is_extended_id=False
    )
    try:
        bus.send(msg)
        print(f"Mensaje enviado: ID=0x{arbitration_id:X}, Datos={data}")
    except can.CanError as e:
        print(f"Error enviando el mensaje: {e}")

def test_periodic_send_with_modifying_data(bus):
    """Send using ModifiableCyclicTaskABC"""
    print("Starting to send a message every 200ms. Initial data is four consecutive 1s")
    msg = can.Message(arbitration_id=0x0CF02200, data=[12, 13, 14, 15])     
    task = bus.send_periodic(msg,0.20)
    if not isinstance(task,can.ModifiableCyclicTaskABC):
        print("This interface doesn't seem to support modification")
        task.stop()
        return 
    time.sleep(2)
    
    print("Changing data of running task to begin with 1")
    msg.data[0] = 0x1
    task.modify_data(msg)
    time.sleep(2)
    task.stop()
    
    print("stopped cyclic send")
    print("Changing data of stopped task to single ff byte")    
    
    msg.data=bytearray([0xFF])
    msg.dlc = 1
    task.modify_data(msg)
    time.sleep(1)
    print("starting again")
    task.start()
    time.sleep(1)
    task.stop()
    print("done")
    

if __name__ == "__main__":
    with can.Bus(interface="pcan", channel="PCAN_USBBUS1", bitrate=500000) as bus:
        reset_bus(bus)
        #pdb.set_trace()
        # Prueba de diferentes mensajes
        messages = [
            (0x100, [1, 2, 3, 4, 5, 6, 7, 8]),
            (0x123, [72, 101, 108, 108, 111]),  # "Hello" en ASCII
            (0x200, [10, 20, 30]),
            (0x300, [0xFF, 0x00, 0xFF]),
        ]
        
        for i in range(5):
            test_periodic_send_with_modifying_data(bus)
            time.sleep(1)
        
        while True:
            for arbitration_id, data in messages:
                send_can_message(bus, arbitration_id, data)
                time.sleep(1)  # Espera 1 segundo entre mensajes
