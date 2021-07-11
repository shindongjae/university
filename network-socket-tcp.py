//server
from socket import *

save=list()

host = '127.0.0.1'
port = 5000

s = socket()  	#s는 소켓변수
s.bind(('', port))  	#설정된 포트에서 임의의 연결을 대기중
s.listen(5)		#연결요청을 듣는다, 파라미터는 연결의 최대수
print("Waiting for c client's Connection \n =>", end=' ')
c, addr = s.accept()      #클라이언트가 문을 두드리면 지정된 c소켓 서버에 생성후 tcp연결

print("Connection from: " + str(c) + str(addr))   #현재 tcp 연결 상태.

while True:
    r_data = c.recv(1024)
    data = r_data.decode()

    if data=='1':  #입력하세요 문장을 전달후 클라이언트로부터 입력받은 문자열 save에 저장
        string="입력하세요"
        c.send(string.encode())

        r_data = c.recv(1024)
        save.append(r_data.decode())

    if data=='2':   #저장된 배열원소 개수를 먼저 보내서 for문을 돌릴수 있게 하고, 그 수만큼 배열원소를 전송
        print(len(save))
        c.send(str(len(save)).encode())
        for i in range(len(save)):
            c.send(save[i].encode())

    if data=='3':  #찾을 문자열을 입력받아 검색한뒤에 존재한다면 존재한다는 문자열 전송.
        string="찾을 문자열은?"
        c.send(string.encode())

        r_data=c.recv(1024)
        string=r_data.decode()

        for i in range(len(save)):
            if save[i]==string:
                string=str(i)+"번째 인덱스에 "+ string+"이 존재합니다"
                c.send(string.encode())
                string=""

c.close()



/*//client
from socket import *

host = '127.0.0.1'
port = 5000

s = socket(AF_INET, SOCK_STREAM)	#ipv4, tcp소켓
s.connect((host, port)) #연결

while 1:
    print("1.입력 2.리스트 출력 3.검색")   
    message = input("-> ")
    s.send(message.encode())

    if message=='1':   #string을 입력받아서 서버에 전송
        r_data = s.recv(1024)
        data = r_data.decode()

        print(data)
        message = input("-> ")
        s.send(message.encode())

    if message=='2':  #서버에서 배열 원소 개수를 받아 그 개수만큼 for문을 돌려서 해당 데이터들을 받는다.
        r_data=s.recv(1024)
        data=r_data.decode()

        i=int(data)

        for k in range(i):
            r_data=s.recv(1024)
            print(r_data.decode())
            print('  ')


    if message=='3':   #찾을 단어를 입력받아 전송하여 결과를 전송받는다.
        r_data=s.recv(1024)
        data=r_data.decode()
        string=input(data)

        s.send(string.encode())
        r_data=s.recv(1024)
        data=r_data.decode()
        print(data)


s.close()
*/
