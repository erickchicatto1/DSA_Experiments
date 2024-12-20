filename = 'PythonCodes//100DaysPython//pi_digits.txt'
ToStore = []

with open(filename) as file_object:
    lines = file_object.readlines()

#To store the data in one list 
for line in lines:
    ToStore.append(line)
    print(line.rstrip())
    
for store in ToStore:
    print(ToStore)
    