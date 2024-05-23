class LAN:
    def __init__(self, name,original_index):
        self.name = name
        self.ip_address = ""
        self.network = ""
        self.broadcast = ""
        self.first_ip = ""
        self.last_ip = ""
        self.mask = ""
        self.hosts= ""
        self.original_index = original_index
        self.interface=""
        
    def set_hosts(self,hosts):
        self.hosts=hosts
        
    def get_hosts(self):
        return self.hosts
    
    def set_ip_address(self, ip_address):
        self.ip_address = ip_address
    
    def get_ip_address(self):
        return self.ip_address
    
    def set_network(self, network):
        self.network = network
    
    def get_network(self):
        return self.network
    
    def set_broadcast(self, broadcast):
        self.broadcast = broadcast
    
    def get_broadcast(self):
        return self.broadcast
    
    def set_first_ip(self, first_ip):
        self.first_ip = first_ip
    
    def get_first_ip(self):
        return self.first_ip
    
    def set_last_ip(self, last_ip):
        self.last_ip = last_ip
    
    def get_last_ip(self):
        return self.last_ip
    
    def set_mask(self, mask):
        self.mask = mask
    
    def get_mask(self):
        return self.mask
    
    def set_interface(self,interface):
        self.interface=interface
        
    def get_interface(self):
        return self.interface
