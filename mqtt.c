/*#By Erick Chicatto

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
*/

#include <stdio.h>
#include <string.h>

// Simulación de la estructura esp_netif_t
typedef struct{
	const char *name;
	const char *ip_address;
}esp_netif_t;

//Declaracion de interfaces de red generadas
esp_netif_t wifi_sta = {"Wifi STA" , "192.168.1.100"};
esp_netif_t wifi_ap = {"Wifi AP" , "192.168.1.1"};
esp_netif_t ethernet = {"Ethernet", "192.168.0.100"};

//Funcion para obtener una interfaz segun el descriptor 
esp_netif_t *get_example_netif_from_desc(const char *desc){
	
	if (strcmp(desc, "WiFi_STA") == 0) {
		return &wifi_sta;
	}
	
	else if (strcmp(desc, "WiFi_AP") == 0){
		return &wifi_ap;
	}
	
	else {
        return NULL; // No se encontró una interfaz que coincida
    }
	
}