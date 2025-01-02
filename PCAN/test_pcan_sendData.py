import logging
import unittest
import can

logging.getLogger(__file__).setLevel(logging.DEBUG)


class ZeroDLCTest(unittest.TestCase):
    def setUp(self):
        try:
            self.bus_send = can.Bus(interface="pcan", channel="PCAN_USBBUS1", bitrate=500000)
            self.bus_recv = can.Bus(interface="pcan", channel="PCAN_USBBUS1", bitrate=500000)
        except can.CanError as e:
            self.fail(f"Error al inicializar el bus: {e}")

    def tearDown(self):
        if hasattr(self, "bus_send"):
            self.bus_send.shutdown()
        if hasattr(self, "bus_recv"):
            self.bus_recv.shutdown()

    def test_recv_non_zero_dlc(self):
        data = [0, 1, 2, 3, 4, 5, 6, 7]
        msg_send = can.Message(is_extended_id=False, arbitration_id=0x100, data=data)

        self.bus_send.send(msg_send)
        msg_recv = self.bus_recv.recv()

        self.assertTrue(msg_recv)

    def test_recv_none(self):
        msg_recv = self.bus_recv.recv(timeout=0)
        self.assertFalse(msg_recv)

    def test_recv_zero_dlc(self):
        msg_send = can.Message(is_extended_id=False, arbitration_id=0x100, data=[])
        self.bus_send.send(msg_send)
        msg_recv = self.bus_recv.recv()
        self.assertTrue(msg_recv)


if __name__ == "__main__":
    unittest.main()
