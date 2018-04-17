using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace wb.lib
{
    public enum LogType { ServerStart, ServerStop, ClientConnect, ClientClose, Error }

    public delegate void LogMessage(LogType ltype, string msg);
    public delegate void DataMessage(Socket sock, string msg);

    public class wbServer
    {
        private LogMessage LMessageDel;
        private DataMessage DMessageDel;

        public Socket Server { get; private set; }

        public wbServer(int port, LogMessage ldel, DataMessage ddel)
        {
            LMessageDel = ldel;
            DMessageDel = ddel;
            Init(port);
        }

        public void SendMessage(Socket sock, string msg)
        {
            byte[] smsg = Encoding.Default.GetBytes(msg);
            sock.Send(smsg, smsg.Length, SocketFlags.None); // 문자열 전송
         }

        private void Init(int port)
        {
            IPEndPoint ipep = new IPEndPoint(IPAddress.Any, port);
            Server = new Socket(AddressFamily.InterNetwork,
                                         SocketType.Stream, ProtocolType.Tcp);
            Server.Bind(ipep);
            Server.Listen(20);

            LMessageDel( LogType.ServerStart, "서버 시작... 클라이언트 접속 대기중...");

            //==================================
            Thread thread = new Thread(Run);
            thread.IsBackground = true;
            thread.Start();
            //==================================
        }

        private void Run()
        {
            try
            {
                while (true)
                {
                    Socket client = Server.Accept();  // 클라이언트 접속 대기
                    IPEndPoint ip = (IPEndPoint)client.RemoteEndPoint;

                    string temp = string.Format("{0}#{1}", ip.Address, ip.Port);
                    LMessageDel(LogType.ClientConnect,temp);

                    //thead 호출
                    Thread thread = new Thread(RecvThread);
                    thread.IsBackground = true;
                    thread.Start(client);
                }
            }
            catch (Exception ex)
            {
                LMessageDel( LogType.Error, ex.Message);
            }
            finally
            {
                Server.Close();
                LMessageDel(LogType.ServerStop, "서버 종료...");
            }        
        }
    
        private void RecvThread(Object obj)
        {
            Socket client = (Socket)obj;

            while (true)
            {
                try
                {
                    byte[] data = new byte[1024];
                    int value = client.Receive(data);
                    //string str = Encoding.Default.GetString(data, 0, value);
                    DMessageDel(client, str);
                }
                catch (Exception)
                {
                    IPEndPoint ip = (IPEndPoint)client.RemoteEndPoint;
                    string temp = string.Format("{0}#{1}",
                        ip.Address, ip.Port);
                    LMessageDel(LogType.ClientClose,temp);
                    client.Close();
                    return;
                }
            }
        }
    }
}
