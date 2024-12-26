import can
import time

CHANNEL = "PCAN_USBBUS1"
BITRATE = 500_000

#Experiment with this class to store values
class TestClassPCAN:
    def __init__(self,question):
        self.question = question
        self.responses = []
        
    def show_questions(self):
        print(self.question)
    
    def store_response(self,new_response):
        self.responses.append(new_response)
    
    def show_results(self):
        print("Values recolected")
        for response in self.responses:
            print(f"-{response}")
            
#List to store all the received messages
store = []

#Set the can 
try:
    bus = can.interface.Bus(bustype='pcan',channel=CHANNEL,bitrate = BITRATE)
    print("Succesfull connection \n")
except can.CanErros as e:
    print(f"Error to connect to bus can : {e}")
    exit(1)
    
    
def decode_message(msg):
    
    dataStoreInCan = TestClassPCAN(msg.data.hex())
    
    question = "What do you want to do?"
    print("Enter q at any time to quit \n")
    
    while True:
        response = input("Enter a value")
        
        if response == 'q':
            break
        
        if msg.is_extended_id:
            print(f"Mensaje extendido recibido: ID=0x{msg.arbitration_id:X}, Datos={msg.data.hex()}")
            dataStoreInCan.store_response(str(msg.data.hex()))
            print(f"Data store")
            dataStoreInCan.show_results()
            print(f"Show results")
        else:
            print(f"Mensaje estándar recibido: ID=0x{msg.arbitration_id:X}, Datos={msg.data.hex()}")
            print(f"Is not extended Message")
        
    
def store_values(msg):
    #Dicctionary
    store.append({
        "id":msg.arbitration_id,
        "data":msg.data.hex(),
        "timestamp":msg.timestamp,   
    })
    
    print(f"Mensaje almacenado:{store[-1]}")
    
if __name__ == "__main__":
    
    try:
        print(f"\n Esperando Mensajes")
        AskUser = input("\n Enter r if you want to receive or s if you want to send")
        
        while True:
            #Ask to the user about how to transsmit the message if sender or receiver
            if AskUser == 'r':
                message = bus.recv(timeout = 1)
                if message:
                    while True:
                        decode_message(message)
                        time.sleep(1)
                elif AskUser=='s':
                    sendMessage = can.Message(arbitration_id=0x123, data=[0x11, 0x22, 0x33, 0x44], is_extended_id=False)
                    print(f"Mensaje Enviado\n")
                    time.sleep(1)
                    for msg in bus:
                        print(f"\n ID: {msg.arbitration_id}, Data:{msg.data}")
                        time.sleep(1)
    except KeyboardInterrupt:
        print(f"\n Finalizando la lectura de los mensajes")
    finally:
        bus.shutdown()
                        
    
        
