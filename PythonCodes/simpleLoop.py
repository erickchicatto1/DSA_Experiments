def greet_user():
    "Display a simple greeting"
    print("Hello!"

def greet_user(username):
    print("Hello , " + username + "!")
    
def make_pizza(topping='bacon'):
    print("Have a " + topping + "!")

def add_numbers(x,y):
    return x+y    



#A simple while loop

current_value = 1
while current_value <= 5:
    print(current_value)
    current_value += 1
    
#Letting the user choice when to quit

msg = ''
while msg != 'quit':
    msg = input("Whats your message?")
    print(msg)
    


    
