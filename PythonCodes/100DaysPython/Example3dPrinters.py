#Here are the functions

def print_models(unprinted_desings,completed_models):  
    while unprinted_desings:
        current_desings = unprinted_desings.pop()
        print(f"Printing models: {current_desings}")
        completed_models.append(current_desings)
        
def show_completed_models(complete_models):
    print("\n The following models have been printed")
    for complete_model in complete_models:
        print(complete_model)
        


unprinted_desings = ['phone case','robot pendant','dodecatron']
complete_models = []

print_models(unprinted_desings,complete_models)
show_completed_models(complete_models)









