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
    
    load = {
        "type" : "privateload",
        "to_id" : 4,
        "page" : 1,
        "size" : 5
    }
    
    s = connect()
    
    request = json.dumps(user)
    s.send(request.encode())
    
    recv = s.recv(1024).decode()
    print(recv)
    
    
    request = json.dumps(load)
    s.send(request.encode())
    
    recv = s.recv(1024).decode()
    print(recv)
        
    s.close()
    

if __name__ == "__main__":
    main()
