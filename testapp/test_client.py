import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

port = 42069;

s.connect(('192.168.137.188', port))

while True:
    try:
        print (s.recv(1024).decode())
    except KeyboardInterrupt:
        break
s.close()