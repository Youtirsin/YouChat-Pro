import json


def main():
    d = {
        "type_": "register",
        "username": "han",
        "password": "okay"
    }
    print(json.dumps(d))


if __name__ == '__main__':
    a = "hello world"
    # b = a.
    
    print(a.encode("utf-8"))
