import turtle
import pdb

def setup():
    "Provide a config for the screen"
    turtle.title('Multiple square animation')
    turtle.setup(100,100,0,0)
    turtle.hideturtle()
    
def draw_square(size):
    turtle.forward(size)
    turtle.right(90)
    turtle.forward(size)
    turtle.right(90)
    turtle.forward(size)
    turtle.right(90)
    turtle.forward(size)
    
setup()

for i in range(0,12):
    breakpoint()
    draw_square(50)
    breakpoint()
    turtle.right(120)
    
turtle.exitonclick()
    