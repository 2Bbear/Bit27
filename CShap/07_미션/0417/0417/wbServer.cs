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
        private List<Socket> socklist = new List<Socket>();

        public Socket Server { get; private set; }

        public wbServer(int port, LogMessage ldel, DataMessage ddel)
        {
            LMessageDel = ldel;
            DMessageDel = ddel;
            Init(port);
        }

        public void SendMessage(Socket sock, string msg)
        {
  //          byte[] smsg = Encoding.Default.GetBytes(msg);
            Send(sock, msg);
            //sock.Send(smsg, smsg.Length, SocketFlags.None); // 문자열 전송
         }

        public void SendAllMessage(Socket sock, string msg)
        {
            //byte[] smsg = Encoding.Default.GetBytes(msg);
            foreach (Socket s in socklist)
            {
                if( s.Equals(sock)== false)
                    Send(s, msg);
                    //s.Send(smsg, smsg.Length, SocketFlags.None); // 문자열 전송
            }
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
                    socklist.Add(client);

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
                    //int value = client.Receive(data);
                    byte[] data = ReceiveData(client);
                    string str = Encoding.Default.GetString(data);
                    DMessageDel(client, str);
                }
                catch (Exception)
                {
                    socklist.Remove(client);
                    IPEndPoint ip = (IPEndPoint)client.RemoteEndPoint;
                    string temp = string.Format("{0}#{1}",
                        ip.Address, ip.Port);
                    LMessageDel(LogType.ClientClose,temp);
                    client.Close();
                    return;
                }
            }
        }


        //2)  send 함수 구현
        private void Send(Socket client, string msg)
        {
            try
            {
                if (client.Connected)
                {
                    byte[] data = Encoding.Default.GetBytes(msg);
                    this.SendData(client, data);
                }
                else
                {
                    LMessageDel(LogType.Error, ("메시지 전송 실패!"));
                }
            }
            catch (Exception ex)
            {
                LMessageDel(LogType.Error, ex.Message);
            }
        }

        // 3) SendData 함수 구현
        private void SendData(Socket client, byte[] data)
        {
            try
            {
                int total = 0;
                int size = data.Length;
                int left_data = size;
                int send_data = 0;

                // 전송할 실제 데이터의 크기 전달
                byte[] data_size = new byte[4];
                data_size = BitConverter.GetBytes(size);
                send_data = client.Send(data_size);

                // 실제 데이터 전송
                while (total < size)
                {
                    send_data = client.Send(data, total, left_data, SocketFlags.None);
                    total += send_data;
                    left_data -= send_data;
                }
            }
            catch (Exception ex)
            {
                LMessageDel(LogType.Error, ex.Message);
            }
        }

        // 2) 
        private byte[] ReceiveData(Socket client)
        {
            try
            {
                int total = 0;
                int size = 0;
                int left_data = 0;
                int recv_data = 0;
                // 수신할 데이터 크기 알아내기   
                byte[] data_size = new byte[4];
                recv_data = client.Receive(data_size, 0, 4, SocketFlags.None);
                size = BitConverter.ToInt32(data_size, 0);
                left_data = size;

                byte[] data = new byte[size];
                // 서버에서 전송한 실제 데이터 수신
                while (total < size)
                {
                    recv_data = client.Receive(data, total, left_data, 0);
                    if (recv_data == 0) break;
                    total += recv_data;
                    left_data -= recv_data;
                }
                return data;
            }
            catch (Exception ex)
            {
                LMessageDel(LogType.Error, ex.Message); 
                return null;
            }
        }

    }
}
