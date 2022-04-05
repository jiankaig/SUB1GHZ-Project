import asyncio
import sys
from datetime import datetime
now = datetime.now()
dt_string = now.strftime("%d/%m/%Y %H:%M:%S")
print("date and time =", dt_string)
ipaddr = '192.168.18.7' #'127.0.0.1'
port = 55007 #9999
async def get_steam_reader(pipe) -> asyncio.StreamReader:
    loop = asyncio.get_event_loop()
    reader = asyncio.StreamReader(loop=loop)
    protocol = asyncio.StreamReaderProtocol(reader)
    await loop.connect_read_pipe(lambda: protocol, pipe)
    return reader

class EchoServerProtocol:
    def connection_made(self, transport):
        self.transport = transport

    def datagram_received(self, data, addr):
        message = data.decode()
        print(f'{dt_string} Received %r from %s' % (message, addr))
        # print('Send %r to %s' % (message, addr))
        # self.transport.sendto(data, addr)
    def connection_lost(data, addr):
        print(f"EchoServerProtocol disconnected:  {data}: {addr}")

async def main():
    print("Starting UDP server")

    # Get a reference to the event loop as we plan to use
    # low-level APIs.
    loop = asyncio.get_running_loop()

    # One protocol instance will be created to serve all
    # client requests.
    transport, protocol = await loop.create_datagram_endpoint(
        lambda: EchoServerProtocol(),
        local_addr=(ipaddr, port))

    print(f"press any key and enter to exit..")
    reader = await get_steam_reader(sys.stdin)
    data = await reader.readline()
    if(data != 0):
        print(f"data: {data}")
        transport.close()
        quit()

    try:
        await asyncio.sleep(3600)  # Serve for 1 hour.
    finally:
        transport.close()

if __name__ == "__main__":
    import time
    s = time.perf_counter()
    asyncio.run(main())
    elapsed = time.perf_counter() - s
    print(f"{__file__} executed in {elapsed:0.2f} seconds.")