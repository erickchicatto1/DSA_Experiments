import can

try:
    bus = can.Bus(interface="pcan", channel="PCAN_USBBUS1", bitrate=500000)
    print("Canal inicializado correctamente")
    bus.shutdown()
except can.CanError as e:
    print(f"Error inicializando el bus: {e}")
