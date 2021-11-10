#!/usr/bin/python3
import asyncio

global TheMessage
TheMessage = "None"


class EchoServerProtocol(asyncio.Protocol):

    def __init__(self):
        self.nconn = 1
        self.idMessage = id(TheMessage)
        print("INIT %d"  %self.idMessage)

    def connection_made(self, transport):
        self.transport = transport
        peername = self.transport.get_extra_info('peername')
        print('Connection from {}'.format(peername))

    def data_received(self, data):
        global TheMessage
        message = data.decode()
        print("server got Message: %s " %message)
        ipos = message.find('SDIR:')
        if ipos >= 0:
            shortMessage = message[ipos+5:]
            self.transport.write(TheMessage.encode())
            print(TheMessage)
            TheMessage = shortMessage




if __name__ == "__main__":   

    loop = asyncio.get_event_loop()
    serv = loop.create_server(lambda: EchoServerProtocol(),  \
        '127.0.0.1',15136)

    server = loop.run_until_complete(serv)
    try:
        loop.run_forever()
    except KeyboardInterrupt:
        print("exit")

    server.close()
    loop.run_until_complete(server.waut_closed())
    loop.close()

