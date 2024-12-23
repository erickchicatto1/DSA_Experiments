#This code is for experiment about the PCAN and try to make an automation

#1. Understand how connect pcan with python 
import can 
import time

bus = can.interface.Bus(
    interface = 'pcan', # Se usa Peak Can
    channel = 'PCAN_USBBUS1', #Nombre del canal 
    bitrate = 500_000 # The bitrate to send a value
)

#Send the message 
message = can.Message(arbitration_id=0x123, data=[0x11, 0x22, 0x33, 0x44], is_extended_id=False)#kind of message to send
store = []

def StoreValues(DataList):
    """Store the values from a can to a list"""
    store.append(DataList)
    
    #if store.len() <= 5:
    #    print(f"\n Has already 5 elements") # To store only 5 elements
        
#Another Idea is to save data in a json
#Save the data in a dictionary
#Make a class that simulate a car
#Simulate a logic to create an UDS messages
#Send all the data into an excel sheet 


try:
    bus.send(message) #send a message using the method send
    print(f"Mensaje enviado")
except can.CanError:
    print("Error al enviar el mensaje.")
    
#Print the messages over the bus

for msg in bus:
    print(f"ID: {msg.arbitration_id}, Data: {msg.data}") #To see the message in the terminal 
    StoreValues(msg)
    time.sleep(1)
   
        
    

