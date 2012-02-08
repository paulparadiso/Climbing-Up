import serial

class SCL:
    
    def __init__(self, port):
        self.ser_port = serial.Serial(port)
        self.ser_port.setTimeout(0.01)
        self.send_scl('HR')
        self.height = 0
        self.clicks_per_inch = 8600
        
    def read_scl(self):
        r = ''
        ret = ''
        while r != '\r':
            r = self.ser_port.read()
            ret += r
        return r

    def send_scl(self, cmd, *args):
        str_out = cmd
        for i in args:
            str_out += i
        str_out += '\r\n'
        self.ser_port.write(str_out)
        return self.read_scl()

    def setAccel(self,val):
        self.send_scl('AC',val)

    def setDecel(self,val):
        self.send_scl('DE',val)

    def setVelocity(self,val):
        self.send_scl('VE',val)

    def move(self, val):
        self.send_scl('FL',val)

    def moveInches(self, val):
        self.move(str(val * self.clicks_per_inch))

    def setJogSpeed(self,val):
        self.send_scl('JS',val)

    def adjustJogSpeed(self, val):
        self.send_scl('CS',val)

    def setJogDir(self,val):
        self.send_scl('DI',val)

    def startJog(self):
        self.send_scl('CJ')
    
    def stopJog(self):
        self.send_scl('SJ')

    def setHeight(self,val):
        distance_to_move = val - self.height
        self.moveInches(distance_to_move)
        self.height = val

    def setClicksPerInch(self, val):
        self.clicks_per_inch = val
