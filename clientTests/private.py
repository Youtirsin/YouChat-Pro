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
        "username" : "Han",
        "password" : "123456"
    }
    private = {
        "type" : "private",
        "to_id" : 4,
        "msg" : "hello world"
    }
    
    s = connect()
    
    request = json.dumps(user)
    s.send(request.encode())
    
    recv = s.recv(1024).decode()
    print(recv)
    
    request = json.dumps(private)
    s.send(request.encode())
    
    while True:
        pass
    
    s.close()
    

if __name__ == "__main__":
    main()
