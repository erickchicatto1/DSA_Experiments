 import can
 import time 
 
 #small steps to solving a problem 
 def generate_response(response_data):
     """Generate a response for DTC for the serv 0x19"""
     dtc_codes = ["P0300", "P0420", "C1234"]
     #construct a uds response with the dtc simulated
     response_data = [0x50,0x19,len(dtc_codes)]
     
     for dtc in dtc_codes:
         dtc_hex = int(dtc[1:],16)
         print(dtc_hex)
         response_data.extend([(dtc_hex >> 8) & 0xFF, dtc_hex & 0xFF])
        
     #Be sure no exceded 8 bytes
     if len(response_data) > 8:
         print("Truncando response_data a 8 bytes:", response_data)
         response_data = response_data[:8]
     return response_data


dateForUds = 0x20
generate_response(dateForUds)

