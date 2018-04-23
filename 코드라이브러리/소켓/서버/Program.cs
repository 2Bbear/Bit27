/*****************************************************************
 * [System.NET ]
 * 
 * TCP Server
 *****************************************************************/
using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using wb.lib;
using _0417;
using System.Collections.Generic;

class Program
{
    private wbServer server;
    private List<Member> memlist = new List<Member>();

    public void Run()
    {
        server = new wbServer(7000, LogMessage, DataMessage);
    }

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
        //id 중복 체크
        else if (filter[0].Equals("IDCHECK"))
        {
            //IDCHECK@아이디
            string pack;
            if (CheckID(filter[1]) == true)
            {
                pack = Packet.IDCheckResult(filter[1], true);
            }
            else
            {
                pack = Packet.IDCheckResult(filter[1], false);
            }
            server.SendMessage(sock, pack);
        }
        //회원 가입 
        else if (filter[0].Equals("NEWMEMBER"))
        {
            //NEWMEMBER@아이디#패스워드#닉네임
            string[] filter1 = filter[1].Split('#');
            string pack = "";
            try
            {
                memlist.Add(new Member(filter1[0], filter1[1], filter1[2]));
                pack = Packet.NewMember(filter1[0], true);
                
                Console.WriteLine(String.Format("id{0} 접속", filter1[0], filter1[1]));
            }
            catch(Exception)
            {
                pack = Packet.NewMember(filter1[0], false);
            }
            finally
            {
                server.SendMessage(sock, pack);
            }
        }
        //로그인
        else if(filter[0].Equals("LOGIN"))
        {
            Console.WriteLine("누군가의 접속 시도...");
            //LOGIN@아이디#패스워드
            string[] filter1 = filter[1].Split('#');
            string pack = "";
            
            if (CheckID(filter1[0]) == false&& CheckPW(filter1[1])==true)
            {
                pack = Packet.LogIn(FindNickNameInMeberList(filter1[0]), true);
            }
            else
            {
                pack = Packet.LogIn("해당 아이디가 없음", false);
            }
            server.SendMessage(sock, pack);
        }
        //회원 삭제
        else if(filter[0].Equals("DELMEMBER"))
        {
            
            //"DELMEMBER@아이디
            string[] filter1 = filter[1].Split('#');
            string pack = "";
            Console.WriteLine("{0}의 회원 탈퇴 시도...", filter1[0]);

            if (DeleteMeber(filter1[0]) == true)
            {
                pack = Packet.DelMember(filter1[0], true);
                
            }
            else
            {
                pack = Packet.DelMember(filter1[0], false);
               
            }

            server.SendMessage(sock, pack);
        }
        //회원 닉네임 수정
        else if (filter[0].Equals("UPDATENICKNAME"))
        {
            Console.WriteLine("누군가의 닉네임 변경 시도...");
            //"UPDATENICKNAME@원래닉네임#수정할닉네임
            string[] filter1 = filter[1].Split('#');
            string pack = "";

            if (CheckID(filter1[0]) == false )
            {
                Console.WriteLine("누군가의 닉네임 변경 시도...");
                pack = Packet.UpdateNickName(ModifyIdInMeberList(filter1[0], filter1[1]), true);
            }
            else
            {
                pack = Packet.UpdateNickName("해당 아이디가 없음", false);
            }
            server.SendMessage(sock, pack);
        }
        //로그아웃

        //전체 회원 리스트 얻기


        //Console.WriteLine(">> " + msg);        
    }
    public bool DeleteMeber(string _id)
    {
        bool result = false;
        int idx = 0;
        foreach (Member t in memlist)
        {
            if (t.NickName.Equals(_id))
            {
                Console.WriteLine("{0} 삭제 성공",t.Id);
                memlist.RemoveAt(idx);
                return true;
            }
            idx++;
        }
        Console.WriteLine("삭제 실패");
    
        return result;

    }
    public String ModifyIdInMeberList(string oldNickName,String newNickName)
    {
        foreach (Member t in memlist)
        {
            if (t.NickName.Equals(oldNickName))
            {
                Console.WriteLine("닉네임 매칭 성공");
                t.NickName = newNickName;
                return t.NickName;
            }

        }
        Console.WriteLine("닉네임 매칭 실패");
        return null;
    }
    public String FindNickNameInMeberList(string id)
    {
        foreach(Member t in memlist)
        {
            if(t.Id.Equals(id))
            {
                Console.WriteLine("id 매칭 성공");
                t.IsLogindState = true;
                return t.NickName;
            }
   
        }
        Console.WriteLine("id 매칭 실패");
        return null;
    }
    public void ConsolePrint(string nn, string msg)
    {
        Console.WriteLine("[{0}]  {1}", nn, msg);
    }

    public bool CheckNickanme(string nickname)
    {
        foreach (Member mem in memlist)
        {
            if (mem.NickName.Equals(nickname))
                return false;
        }
        return true;
    }


    public bool CheckPW(string pw)
    {
        foreach (Member mem in memlist)
        {
            if (mem.Password.Equals(pw))
                return true;
        }
        return false;
    }

    public bool CheckID(string id)
    {
        foreach (Member mem  in memlist)
        {
            if (mem.Id.Equals(id))
                return false;
        }
        return true;
    }


    static void Main(string[] args)
    {
        new Program().Run();

        Console.ReadKey();
    }
}




