#This function retorn a dictionary 

def build_person(first_name, last_name):
    """Retorn a dictionary of information about a person """
    person = {'first':first_name , 'last_name':last_name}
    return person



musician = build_person('jimi','hendrix')
print(musician)


#Adding a key and value in the dictionary
def buildPersonTwo(first_name,last_name,age=None):
    """Retorn a dictionary of information about a person"""
    person = {'first':first_name , 'last_name':last_name}
    
    if age:
        person['age'] = age #assing key and then teh value 
    return person


musicianTwo = build_person('jimi','hendrix',age = 27)
print(musicianTwo)    