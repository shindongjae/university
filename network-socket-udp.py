//client

import random
from socket import *

host='127.0.0.1'    #자기 자신 ip주소로
port = 12000       #12000번 포트

a=0
b=0

x=range(0,9,1)
while 1:
    s=socket(AF_INET, SOCK_DGRAM)  #ipv4, udp
    string=""
    array=[]

    for i in range(2000):
        string=string+str(random.choice(x))  #2000자리 숫자 생성



    s.sendto(string.encode(),(host,port)) #전송
    message, serverAddress=s.recvfrom(2048) #패킷 데이터, 패킷 소스 할당, 2048을 버퍼크기로
    if message.decode()==string:
        a=a+1
    b=b+1   #만약 정상적으로 전달됬으면 분모 분자+1, 아니라면 분모만 +1
    s.close()

    print(a,'/',b)

/*//server

from socket import *

port=12000   #12000번 포트
serverSocket=socket(AF_INET, SOCK_DGRAM)  #ipv4, udp
serverSocket.bind(('',port)) #포트번호 12000을 서버의 포트로 할당
print('The server is ready to receive') 
while True:
    message, clientAddress=serverSocket.recvfrom(2048)
    modifiedMessage=message.decode()
    serverSocket.sendto(modifiedMessage.encode(), clientAddress)#보낸 문자를 다시 전송
*/
