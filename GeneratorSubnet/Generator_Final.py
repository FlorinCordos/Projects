import ipaddress
import math
from lan import LAN
from prettytable import PrettyTable

# Calcularea noului prefix
def calculate_expression(n):
    return 32 - math.ceil(math.log2(n))

# Sortarea LAN-urilor
def sort_lans_by_hosts(lans):
    return sorted(lans, key=lambda lan: lan.get_hosts(), reverse=True)

# Funcția pentru a crea LAN-uri
def create_lans(num):
    lans = {}
    for i in range(1, num + 1):
        lan_name = "LAN" + str(i)
        lan_instance = LAN(lan_name, i-1)  # Adăugăm indexul original
        lans[lan_name] = lan_instance
    return lans

# Funcția pentru a înlocui numele unui LAN
def replace_name(lans, actual_name, new_name):
    if actual_name in lans:
        lans[actual_name].set_name(new_name)
        lans[new_name] = lans.pop(actual_name)
    else:
        print(f"LAN-ul cu numele {actual_name} nu există.")

def main():
    ip_input = input("Introduceți clasa de IP: ")
    try:
        # Adresa IP cu prefix
        interface = ipaddress.ip_interface(ip_input)
        major_interface = interface
        
        # Obținerea adresei IP fara prefix
        ip_address = interface.ip
        
        # Crearea unui obiect IPv4Network fără prefix
        IPv4IP = interface.network
        
        networkAddress = IPv4IP.network_address
        broadcastAddress = IPv4IP.broadcast_address
        masca = IPv4IP.netmask
        
        # Crearea LAN-urilor și setarea numărului de gazde pentru fiecare LAN
        num_lans = int(input("NR LAN-uri: "))
        lans = create_lans(num_lans)
        for lan_name, lan in lans.items():
            num_lan_hosts = int(input(f"Hosts {lan_name}: "))
            lan.set_hosts(num_lan_hosts)
        
        # Sortarea LAN-urilor în funcție de numărul de gazde
        sorted_lans = sort_lans_by_hosts(list(lans.values()))
        
        # Parcurgerea LAN-urilor sortate și setarea adresei IP pentru fiecare LAN
        for i in range(len(sorted_lans)):
            current_lan = sorted_lans[i]
            if i == 0:
                n = current_lan.get_hosts()
                if n <= 2:
                    n += 2
                new_prefix = calculate_expression(n)
                new_network = ipaddress.IPv4Network(str(ip_address) + "/" + str(new_prefix), strict=False)
                current_lan.set_ip_address(new_network.network_address)  # Alege adresa LAN
                interface = ipaddress.ip_interface(f"{new_network.network_address}/{new_prefix}")
                current_lan.set_interface(interface)  # Interfața LAN cu tot cu prefix
                current_lan.set_network(new_network.network_address)  # Network
                current_lan.set_broadcast(new_network.broadcast_address)  # Broadcast
                current_lan.set_first_ip(new_network.network_address + 1)  # Primul IP
                current_lan.set_last_ip(new_network.broadcast_address - 1)  # Ultimul IP
                current_lan.set_mask(new_network.netmask)  # Masca
            else:
                previous_lan = sorted_lans[i - 1]
                previous_broadcast = ipaddress.IPv4Address(previous_lan.get_broadcast())
                new_start_ip = previous_broadcast + 1
                n = current_lan.get_hosts()
                if n <= 2:
                    n += 2
                new_prefix = calculate_expression(n)
                new_network = ipaddress.IPv4Network(str(new_start_ip) + "/" + str(new_prefix), strict=False)
                current_lan.set_ip_address(new_network.network_address)  # Alege adresa LAN
                interface = ipaddress.ip_interface(f"{new_network.network_address}/{new_prefix}")
                current_lan.set_interface(interface)  # Interfața LAN cu tot cu prefix
                current_lan.set_network(new_network.network_address)  # Network
                current_lan.set_broadcast(new_network.broadcast_address)  # Broadcast
                current_lan.set_first_ip(new_network.network_address + 1)  # Primul IP
                current_lan.set_last_ip(new_network.broadcast_address - 1)  # Ultimul IP
                current_lan.set_mask(new_network.netmask)  # Masca
        
        # Sortarea din nou a LAN-urilor pentru a păstra ordinea inițială
        sorted_lans.sort(key=lambda lan: lan.original_index)
        
        replace_name(lans,"LAN4","WAN1")
        replace_name(lans,"LAN5","WAN2")
        replace_name(lans,"LAN6","WAN3")
              
        # Afișarea detaliilor pentru fiecare LAN în ordinea originală
        print(f"Clasa de IP: {major_interface}  [N: {networkAddress} - {broadcastAddress} :B]")
        table = PrettyTable()
        table.field_names = ["Denumire", "Adresa LAN", "Network", "Broadcast", "Primul IP", "Ultimul IP", "Masca"]
        
        for lan in sorted_lans:
            table.add_row([
                lan.get_name(),
                str(lan.get_interface()),
                lan.get_network(),
                lan.get_broadcast(),
                lan.get_first_ip(),
                lan.get_last_ip(),
                lan.get_mask()
            ])
        print(table)
        
    except ValueError as e:
        print(f"Eroare: {e}")

if __name__ == "__main__":
    main()
