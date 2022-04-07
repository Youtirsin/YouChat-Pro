import socket, json

HOST = "127.0.0.1"
PORT = 10086


def connect():
    s = socket.socket()
    s.connect((HOST,PORT))
    print('connected...')
    return s


def main():
    user = {
        "type" : "signin",
        "username" : "You",
        "password" : "password"
    }
    
    s = connect()
    
    request = json.dumps(user)
    s.send(request.encode())
    
    while True:
        recv = s.recv(1024).decode()
        
        if recv == b"": break
        
        print(recv)
        
        
    s.close()
    

if __name__ == "__main__":
    main()
