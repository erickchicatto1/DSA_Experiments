import pytest
import can

@pytest.fixture(scope="function")
def can_buses():
    """Fixture to initialize and clean up CAN buses."""
    try:
        bus_send = can.Bus(interface="pcan", channel="PCAN_USBBUS1", bitrate=500000)
        bus_recv = can.Bus(interface="pcan", channel="PCAN_USBBUS1", bitrate=500000)
        yield bus_send, bus_recv
    finally:
        if 'bus_send' in locals() and bus_send is not None:
            bus_send.shutdown()
        if 'bus_recv' in locals() and bus_recv is not None:
            bus_recv.shutdown()

def test_recv_non_zero_dlc(can_buses):
    bus_send, bus_recv = can_buses
    data = [0, 1, 2, 3, 4, 5, 6, 7]
    msg_send = can.Message(is_extended_id=False, arbitration_id=0x100, data=data)

    bus_send.send(msg_send)
    msg_recv = bus_recv.recv()

    assert msg_recv is not None, "No message received for non-zero DLC"

def test_recv_none(can_buses):
    _, bus_recv = can_buses
    msg_recv = bus_recv.recv(timeout=0)
    assert msg_recv is None, "Expected no message to be received"

def test_recv_zero_dlc(can_buses):
    bus_send, bus_recv = can_buses
    msg_send = can.Message(is_extended_id=False, arbitration_id=0x100, data=[])
    
    bus_send.send(msg_send)
    msg_recv = bus_recv.recv()
    
    assert msg_recv is not None, "No message received for zero DLC"
