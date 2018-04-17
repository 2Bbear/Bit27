using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using wb.lib;
using System.Threading;

namespace Client
{
    //Client
    
    class Program
    {
        private WbClient client;

        static void Main(string[] args)
        {
            new Program().Run();
        }
        public void LogMessage(LogType ltype, string msg)
        {

        }
        public void DataMessage(Socket sock, string msg)
        {

        }
        void Run()
        {
            client = new WbClient(IPAddress.Parse("192.168.0.52"),7000, LogMessage, DataMessage);

            
        }
    }
}
