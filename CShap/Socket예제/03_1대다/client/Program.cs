/*****************************************************************
 * [System.NET ]
 * 
 * TCP Client
 *****************************************************************/
using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using wb.lib;
using System.Threading;

class Program
{
    private wbClient client;

    public void Run(string ip, int port)
    {
        client = new wbClient(ip, port, LogMessage, DataMessage);

        while (true)
        {
                try
                {
                    string str = Console.ReadLine();

                    client.SendMessage(client.Server, str);
                }
                catch (Exception ex)
                {
                    Console.WriteLine(ex.Message);
                }
        }
    }

    public void LogMessage(LogType ltype, string msg)
    {
            if (ltype == LogType.Connect)
            {
                string[] temp = msg.Split('#');
                Console.WriteLine("[서버 접속] {0}:{1}",
                    temp[0], temp[1]);
            }
            else if (ltype == LogType.DisConnect)
            {
                string[] temp = msg.Split('#');
                Console.WriteLine("[서버 접속 해제] {0}:{1}",
                    temp[0], temp[1]);
            }
            else
            {
                Console.WriteLine(msg);
            }
    }

    public void DataMessage(Socket sock, string msg)
    {
            Console.WriteLine(msg);
    }
    
    static void Main(string[] args)
    {
        new Program().Run("192.168.0.52", 7000);        
    }
}





