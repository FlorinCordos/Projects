class Switch:
    def __init__(self, name):
        self.name = name
        self.interface = None
        self.subnet_mask = None
        self.default_gateway = None
    
    def set_interface(self, ip_address, subnet_mask):
        self.interface = ip_address
        self.subnet_mask = subnet_mask
    
    def set_default_gateway(self, gateway_ip):
        self.default_gateway = gateway_ip
    
    def get_name(self):
        return self.name

    def get_interface(self):
        return self.interface
    
    def get_subnet_mask(self):
        return self.subnet_mask
    
    def get_default_gateway(self):
        return self.default_gateway