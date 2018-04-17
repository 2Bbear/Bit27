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

class Program
{
    private wbServer server; 

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
        Console.WriteLine(">> " + msg);

        server.SendMessage(sock, msg);
    }

    static void Main(string[] args)
    {
        new Program().Run();

        Console.ReadKey();
    }
}




