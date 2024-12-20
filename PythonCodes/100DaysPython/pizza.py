#passing data to an empty list into a function 
def make_pizza(size,*topings):
    print(f"\n Making a {size} pizza with the following toppings")
    
    for topping in topings:
        print(f" -  {topping}")
        
make_pizza(12,'pepperoni')
make_pizza(12,'pepperoni','green peppers', 'extra cheese')


#passing data to an empty dictionary 
def build_profile(first,last,**user_info):
    """Build a dictionary to have everything we know about a user"""
    user_info['first'] = first
    user_info['last_name']= last 
    
    return user_info

userProfile = build_profile('albert','einstein',location='princenton',field = 'physics')
print(userProfile)
    

    

