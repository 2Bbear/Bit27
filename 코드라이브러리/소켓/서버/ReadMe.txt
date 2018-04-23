***********************************************
사용법

using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

1. wbServer , Packet.cs 파일을 프로젝트에 추가한다.

1-1 . Server의 시작부는 
 private wbServer server;
 server = new wbServer(7000, LogMessage, DataMessage); 로 시작한다.

2. wbServer에서 받은 데이터를 처리하기 위해 원하는 곳에/////////////////////////////////////////////////////

 public void DataMessage(Socket sock, string msg)
    {
        string[] filter = msg.Split('@');
        //메세지 전송
        if (filter[0].Equals("SENDMESSAGE"))
        {
            string[] filter1 = filter[1].Split('#');
            string nickname = filter1[0];
            string message = filter1[1];
            ConsolePrint(nickname, message);
            server.SendAllMessage(sock, msg);
        }
        //닉네임 중복 체크
        else if (filter[0].Equals("NICKNAMECHECK"))
        {
            //"NICKNAMECHECK@NICKNAME
            string pack;
            if(CheckNickanme(filter[1])==true)
            {
                pack = Packet.NickNameCheckResult(filter[1],true);
            }
            else
            {
                pack = Packet.NickNameCheckResult(filter[1], false);
            }
            server.SendMessage(sock, pack);
        }
        
        //로그아웃

        //전체 회원 리스트 얻기


        //Console.WriteLine(">> " + msg);        
    }

DataMessage를 처리한다.

3. wbServer가 받거나 처리하는 과정에서 생성되는 로그들을 처리하고 재 전송하기 위해 원하는 곳에 아래의 함수를 정의한다.

public void LogMessage(LogType ltype, string msg)
    {
        if(ltype == LogType.ClientConnect)
        {
            string[] temp = msg.Split('#');
            Console.WriteLine("[클라이언트 접속] {0}:{1}",
                temp[0], temp[1]);
        }
        else if(ltype == LogType.ClientClose)
        {
            string[] temp = msg.Split('#');
            Console.WriteLine("[클라이언트 해제] {0}:{1}",
                temp[0], temp[1]);
        }
        else
        {
            Console.WriteLine(msg);
        }
    }

//////////////////////////////////////////////////////////////////////////////////////////////