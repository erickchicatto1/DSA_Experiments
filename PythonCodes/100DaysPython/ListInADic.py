#This is an python example of a list in a dictionarie
pizza = {
    'crust':'thick',
    'toppings' : ['mushrooms','extra cheese'],
}

#Summarize the order
print(f"you ordered a {pizza['crust']}")

#printing the values in the loop
for topping in pizz['toppings']:
    print(f"\t {topping}")
    
