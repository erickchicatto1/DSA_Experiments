"""
By Erick Chicatto
Demostrate how to receive messages via polling

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <https://www.gnu.org/licenses/>.

"""

import can 
from can.bus import BusState


def receive_all():
    """Receive all the messages and prints all"""
    with can.Bus() as bus:
        try:
            bus.state = BusState.PASSIVE
        except NotImplementedError:
            pass
        
        try:
            while True:
                msg = bus.recv(1)
                if msg is not None:
                    print(msg)
        except KeyboardInterrupt:
            pass

if __name__ == "__main__":
    receive_all()
        
        
        
    
    

