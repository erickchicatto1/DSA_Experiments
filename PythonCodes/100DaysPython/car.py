class Car:
    """A simple attempt to represent a car"""

    def __init__(self, make, model, year):
        self.make = make
        self.model = model
        self.year = year
        self._odometer_reading = 0  # Private attribute

    def get_descriptive_name(self):
        """Return a neatly formatted descriptive name"""
        long_name = f"{self.year} {self.make} {self.model}"
        return long_name.title()

    def read_odometer(self):
        """Print a statement showing the car's mileage"""
        print(f"This car has {self._odometer_reading} miles on it.")

    def update_odometer(self, mileage):
        """
        Set the odometer reading to the given value.
        Reject the change if it attempts to roll the odometer back.
        """
        if mileage >= self._odometer_reading:
            self._odometer_reading = mileage
        else:
            print("You can't roll back an odometer.")

    def increment_odometer(self, miles):
        """Add the given amount to the odometer reading"""
        self._odometer_reading += miles

        
class Battery:
    """A simple attempt to model a bettery for an electric car"""
    
    def __init__(self,battery_size=75):
        """Initialize the battery attributes"""
        self.battery_size = battery_size
        
    def describe_battery(self): 
        """Print a statement describing the battery size"""
        print(f"This car has a {self.battery_size}")
        
    def get_range(self):
        """Print a statement about the range this battery provides"""
        if self.battery_size  == 75: # se pueden usar atributos de la clase en otros metodos
            range = 60
        elif self.battery_size == 100:
            range = 35
        print(f"This car can go about {range} miles on full charge")


class ElectricCar(Car):
    """Represents an electric car"""

    def __init__(self, make, model, year):
        """
        Initialize attributes of the parent class.
        """
        super().__init__(make, model, year)
        self.battery = Battery() #instancia a la clase , lo que permite que el coche tenga asociadsa caracteristicas de la bateria


# Create instances of the Car and ElectricCar classes
my_new_car = Car('Audi', 'A4', 2019)
my_tesla = ElectricCar('Tesla', 'Model S', 2019)

# Access and modify attributes and methods
print(my_new_car.get_descriptive_name())
my_new_car.update_odometer(23)
my_new_car.increment_odometer(23200)
my_new_car.read_odometer()

print(my_tesla.get_descriptive_name())
my_tesla.battery.describe_battery()

#
my_tesla.battery.get_range() # usamos el objeto , despues la instancia a la clase , despues accedemos a sus metodos

