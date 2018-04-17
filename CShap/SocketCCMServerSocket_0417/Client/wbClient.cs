using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;


namespace wb.lib
{
    public enum LogType { ServerConnectSuccess, ServerDisConnect, Error, ClientStart, ClientStop, ClientClose }

    public delegate void LogMessage(LogType ltype, String msg);
    public delegate void DataMessage(Socket sock, string msg);

    public class WbClient
    {
        #region Delegate
        private LogMessage LMessageDel;
        private DataMessage DMessageDel;

        #endregion

        #region Attribute/Property
        private Socket server;
        public Socket Server { get => server; private set => server = value; }

        #endregion

        #region Constructor
        public WbClient(IPAddress ip,int port, LogMessage ldel, DataMessage ddel)
        {
            DMessageDel = ddel;
            LMessageDel = ldel;

            Init(ip,port);

        }
        #endregion

        #region Method
        private void Init(IPAddress ip,int port)
        {
            IPEndPoint ipep = new IPEndPoint(ip, 7000);
            Server = new Socket(AddressFamily.InterNetwork,
                                         SocketType.Stream, ProtocolType.Tcp);
            Server.Connect(ipep);//서버에 접속 시도

            LMessageDel(LogType.ServerConnectSuccess, "서버 접속 성공...");
            //====================================================================
            Thread thread = new Thread(Run);
            thread.IsBackground = false;
            thread.Start();
            //=================================================================
        }

        private void Run()
        {
            try
            {
                while (true)
                {
                    //byte[] data = new byte[1024];
                    byte[] data;// = new byte[1024];
                   
                    Console.Write(" >> ");
                    string str = Console.ReadLine();
                    data = Encoding.Default.GetBytes(str);

                    server.Send(data, data.Length, SocketFlags.None); // 문자열 전송

                    Thread thread = new Thread(Run);
                    thread.IsBackground = false;
                    thread.Start();
                    
                    server.Receive(data);
                    Console.WriteLine("수신 데이터: " + Encoding.Default.GetString(data));
                    Console.WriteLine();


                }
            }
            catch (Exception ex)
            {
                LMessageDel(LogType.Error, ex.Message);

            }
            finally
            {
                server.Close();
                LMessageDel(LogType.ServerDisConnect, "서버와 연결이 끊김");
            }
        }
        public void SendMessage(Socket sock, string msg)
        {
            byte[] smsg = Encoding.Default.GetBytes(msg);
            sock.Send(smsg, smsg.Length, SocketFlags.None); // 문자열 전송
        }
        private void RecvThread(object obj)
        {
            Socket client = (Socket)obj;

            while (true)
            {
                try
                {
                    byte[] data = new byte[1024];
                    int value = client.Receive(data);
                    string str = Encoding.Default.GetString(data, 0, value);
                    //string str = Encoding.Default.GetString(data);

                    DMessageDel(client, str);


                }
                catch (Exception)
                {
                    IPEndPoint ip = (IPEndPoint)client.RemoteEndPoint;
                    string temp = string.Format("{0}#{1}", ip.Address, ip.Port);
                    LMessageDel(LogType.ClientClose, temp);
                    client.Close();         //  소켓 연결 끊기
                    return;

                }
            }

        }
        #endregion
    }
}
