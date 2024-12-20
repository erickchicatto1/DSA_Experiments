
'''
#Python dictionary
alien_0 = {'x_position':0,'y_position':25,'speed':'medium'}
print(f"Original position : {alien_0['x_position']}")

#Move the alien to the right
if alien_0['speed']== 'slow':
    x_increment = 1
elif alien_0['speed']== 'medium':
    x_increment = 2
else:
    x_increment = 3
    
#The new position is the old position plus the increment
alien_0['x_position'] = alien_0['x_position'] + x_increment
print(f"New position : {alien_0['x_position']}")
'''
'''
#looping in a dictionarie************
user_0 = {
    'userName':'erick',
    'first':'lopez',
    'last':'chicatto'
}

for key,value in user_0.items():
    print(f"\nKey : {key}")
    print(f"Value:  {value}")
    
#*************************************    

'''
'''
#Looping the keys in the python dictionarie
favorite_languages = {
    'jen':'python',
     'erick':'c',
     'edward':'ruby',
     'phil':'python',
}

for name in favorite_languages.keys():
    print(name.title())

'''
#Mix of list and dictionaries in Python 
favorite_languages = {
    'jen':'python',
    'erick':'c',
    'edward':'ruby',
    'phil':'python',
}

friends = ['chucho','marco','phil']

for name in favorite_languages.keys():
    print(f"Hi {name.title()}.")
    
    if name in friends:
        language = favorite_languages[name].title()
        print(f"\t {name.title()}, I see you love {language}")
        
        


        



