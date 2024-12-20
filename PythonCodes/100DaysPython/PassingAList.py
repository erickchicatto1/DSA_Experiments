'''
def greet_users(names):
    """Print a simple greeting to each user in the list"""
    for name in names:
        msg = f"Hello, {name.title()}"
        print(msg)
        
usernames = ['erick','ty','margot']
greet_users(usernames)

'''

#Now the same code above but using annotations 
def greet_users(names: list[str]) -> None:
    """Prints a simple greeting to each user in the provided list.

    Args:
        names: A list of strings representing user names.

    Returns:
        None
    """

    for name in names:
        msg = f"Hello, {name.title()}"
        print(msg)


usernames = ['erick', 'ty', 'margot']
greet_users(usernames)


