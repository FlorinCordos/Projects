import ipaddress
import math
from lan import LAN
from wan import WAN
from prettytable import PrettyTable

# Calcularea noului prefix
def calculate_expression(n):
    return 32 - math.ceil(math.log2(n))

# Sortarea LAN-urilor
def sort_lans_by_hosts(lans):
    return sorted(lans, key=lambda lan: lan.get_hosts(), reverse=True)

# Funcția pentru a crea LAN-uri
def create_lans(num):
    lans = []
    for i in range(1, num + 1):
        lan_name = "LAN" + str(i)
        lan_instance = LAN(lan_name, i-1)  # Adăugăm indexul original
        lans.append(lan_instance)
    return lans

#Crearea wan-urilor
def create_wan(num):
    wans=[]
    for i in range(1,num+1):
        wan_name="WAN"+str(i)
        wan_instance=WAN(wan_name,i-1) #Adaugare index original
        wans.append(wan_instance)
    return wans

def main():
    ip_input = input("Introduceți clasa de IP: ")
    try:
        interface = ipaddress.ip_interface(ip_input)
        
        # Obținerea adresei IP fără prefix
        ip_address = interface.ip
        
        # Crearea unui obiect IPv4Network fără prefix
        IPv4IP = interface.network
        
        networkAddress = IPv4IP.network_address
        broadcastAddress = IPv4IP.broadcast_address
        
        #primulIP = networkAddress + 1
        #ultimulIP = broadcastAddress - 1
        masca = IPv4IP.netmask
        
        # Crearea LAN-urilor și setarea numărului de gazde pentru fiecare LAN
        num_lans = int(input("NR LAN-uri: "))
        lans = create_lans(num_lans)
        for lan in lans:
            num_hosts = int(input(f"Hosts LAN-ul {lan.name}: "))
            lan.set_hosts(num_hosts)
        
        # Sortarea LAN-urilor în funcție de numărul de gazde
        sorted_lans = sort_lans_by_hosts(lans)
        
        # Parcurgerea LAN-urilor sortate și setarea adresei IP pentru fiecare LAN
        for i in range(len(sorted_lans)):
            current_lan = sorted_lans[i]
            if i == 0:
                n = current_lan.get_hosts()
                if n<=2:
                    n=n+2
                new_prefix = 32 - math.ceil(math.log2(n))
                new_network = ipaddress.IPv4Network(str(ip_address) + "/" + str(new_prefix), strict=False)
                current_lan.set_ip_address(new_network.network_address)  # Alege adresa LAN
                interface = ipaddress.ip_interface(f"{new_network.network_address}/{new_prefix}")
                current_lan.set_interface(interface) #interfata LAN cu tot cu prefix
                current_lan.set_network(new_network.network_address) # Network
                current_lan.set_broadcast(new_network.broadcast_address)  # Broadcast
                current_lan.set_first_ip(new_network.network_address + 1)  # Primul IP
                current_lan.set_last_ip(new_network.broadcast_address - 1)  # Ultimul IP
                current_lan.set_mask(new_network.netmask)  # Masca
            else:
                previous_lan = sorted_lans[i - 1]
                previous_broadcast = ipaddress.IPv4Address(previous_lan.get_broadcast())
                new_start_ip = previous_broadcast + 1
                n = current_lan.get_hosts()
                if n<=2:
                    n=n+2
                new_prefix = 32 - math.ceil(math.log2(n))
                new_network = ipaddress.IPv4Network(str(new_start_ip) + "/" + str(new_prefix), strict=False)
                current_lan.set_ip_address(new_network.network_address)  # Alege adresa LAN
                interface = ipaddress.ip_interface(f"{new_network.network_address}/{new_prefix}")
                current_lan.set_interface(interface) #interfata LAN cu tot cu prefix
                current_lan.set_network(new_network.network_address) # Network
                current_lan.set_broadcast(new_network.broadcast_address)  # Broadcast
                current_lan.set_first_ip(new_network.network_address + 1)  # Primul IP
                current_lan.set_last_ip(new_network.broadcast_address - 1)  # Ultimul IP
                current_lan.set_mask(new_network.netmask)  # Masca
        
        # Sortarea din nou a LAN-urilor pentru a păstra ordinea inițială
        sorted_lans.sort(key=lambda lan: lan.original_index)
        #Broadcast-ul de la cel mai mic LAN
        smallest_lan_broadcast = sorted_lans[-1].get_broadcast()
        # Afișarea detaliilor pentru fiecare LAN în ordinea originală
        table=PrettyTable()
        table.field_names=["Denumire", "Adresa LAN", "Network", "Broadcast", "Primul IP", "Ultimul IP", "Masca"]
        
        for lan in sorted_lans:
            table.add_row([
                lan.name, 
                str(lan.get_interface()), 
                lan.get_network(), 
                lan.get_broadcast(), 
                lan.get_first_ip(), 
                lan.get_last_ip(), 
                lan.get_mask()
            ])
        print(table)
        print(smallest_lan_broadcast)
    except ValueError as e:
        print(f"Eroare: {e}")

if __name__ == "__main__":
    main()
