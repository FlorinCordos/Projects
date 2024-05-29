class Router:
    def __init__(self, name):
        self.name = name
        self.interfaces = {
            "Gig0/0": None,
            "Gig0/1": None,
            "Gig0/2": None,
            "S0/0/0": None,
            "S0/0/1": None
        }
    
    def set_interface(self, interface, ip_address, subnet_mask=None):
        if interface in self.interfaces:
            self.interfaces[interface] = (ip_address, subnet_mask)
    
    def get_interface(self, interface):
        return self.interfaces.get(interface, (None, None))
    
    def get_name(self):
        return self.name