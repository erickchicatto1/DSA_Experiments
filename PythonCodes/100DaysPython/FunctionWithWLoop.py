#This function format a name and have an infinite loop with a while

def get_formatted_name(first_name,last_name):
    """Return a full name , formatted"""
    full_name = f"{first_name} {last_name}"
    return full_name.title()
#
while True:
    print("Please tell me your name ")
    
    f_name = input("First_name")
    l_name = input("Last_name")
    
    if f_name == 'q':
        break
    
    if l_name == 'q':
        break
    
    formatted_name = get_formatted_name(f_name,l_name)
    print(f"\nHello {formatted_name}")
