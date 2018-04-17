using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using wb.lib;
namespace SocketCCMServerSocket_0417
{

    //Server
    class Program
    {
        private WbServer server;



        static void Main(string[] args)
        {
            new Program().Run();
            
        }
        public void LogMessage(LogType ltype, string msg)
        {
            if(ltype== LogType.ClientConnect)
            {
                string []temp = msg.Split('#');
                Console.WriteLine("클라이언트 접속 :{0}{1} ",temp[0], temp[1]);
            }
            else if(ltype == LogType.ClientClose)
            {
                string[] temp = msg.Split('#');
                Console.WriteLine("클라이언트 해제 :{0}{1} ", temp[0], temp[1]);
            }
            else
            {
                Console.WriteLine(msg);
            }
        }
        public void DataMessage(Socket sock, string msg)
        {
            Console.WriteLine(">>" + msg);

            server.SendMessage(sock, msg);
        }
        public void Run()
        {
            server = new WbServer(7000, LogMessage, DataMessage);

            Console.ReadLine();
        }

        
    }

}
