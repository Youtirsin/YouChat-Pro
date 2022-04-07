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
        "username" : "han",
        "password" : "123456"
    }
    
    fetchlist = {
        "type" : "fetchlist"
    }
    
    s = connect()
    
    request = json.dumps(user)
    s.send(request.encode())
    
    recv = s.recv(1024).decode()
    print(recv)
    
    
    request = json.dumps(fetchlist)
    s.send(request.encode())
    
    recv = s.recv(1024).decode()
    print(recv)
        
    s.close()
    

if __name__ == "__main__":
    main()
