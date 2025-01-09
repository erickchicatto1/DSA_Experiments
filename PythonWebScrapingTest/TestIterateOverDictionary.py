#Create an dictionary of data 
data = {
    "Nombre":["Juan","Maria","Carlos"],
    "Edad" : [25,30,35],
    "Ciudad":["Madrid","Lima","Bogota"]
}

#Iterate the values in the dictionary
for Key,Value in data.items():
    print(f"\n Key : {Key}")
    print(f"Value: {Value}")

#Extract information inside of the dictionary    
print(data['Nombre'][0])
print(data['Nombre'][1])
print(data['Nombre'][2])

print(data["Edad"])
print(data["Edad"][0])
print(data["Edad"][1])
print(data["Edad"][2])





