***********************************************
����

using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

1. wbServer , Packet.cs ������ ������Ʈ�� �߰��Ѵ�.

1-1 . Server�� ���ۺδ� 
 private wbServer server;
 server = new wbServer(7000, LogMessage, DataMessage); �� �����Ѵ�.

2. wbServer���� ���� �����͸� ó���ϱ� ���� ���ϴ� ����/////////////////////////////////////////////////////

 public void DataMessage(Socket sock, string msg)
    {
        string[] filter = msg.Split('@');
        //�޼��� ����
        if (filter[0].Equals("SENDMESSAGE"))
        {
            string[] filter1 = filter[1].Split('#');
            string nickname = filter1[0];
            string message = filter1[1];
            ConsolePrint(nickname, message);
            server.SendAllMessage(sock, msg);
        }
        //�г��� �ߺ� üũ
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
        
        //�α׾ƿ�

        //��ü ȸ�� ����Ʈ ���


        //Console.WriteLine(">> " + msg);        
    }

DataMessage�� ó���Ѵ�.

3. wbServer�� �ްų� ó���ϴ� �������� �����Ǵ� �α׵��� ó���ϰ� �� �����ϱ� ���� ���ϴ� ���� �Ʒ��� �Լ��� �����Ѵ�.

public void LogMessage(LogType ltype, string msg)
    {
        if(ltype == LogType.ClientConnect)
        {
            string[] temp = msg.Split('#');
            Console.WriteLine("[Ŭ���̾�Ʈ ����] {0}:{1}",
                temp[0], temp[1]);
        }
        else if(ltype == LogType.ClientClose)
        {
            string[] temp = msg.Split('#');
            Console.WriteLine("[Ŭ���̾�Ʈ ����] {0}:{1}",
                temp[0], temp[1]);
        }
        else
        {
            Console.WriteLine(msg);
        }
    }

//////////////////////////////////////////////////////////////////////////////////////////////