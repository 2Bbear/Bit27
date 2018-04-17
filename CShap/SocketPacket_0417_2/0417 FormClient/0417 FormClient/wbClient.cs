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
    public enum LogType { Connect, DisConnect, ClientClose, Error }

    public delegate void LogMessage(LogType ltype, string msg);
    public delegate void DataMessage(Socket sock, string msg);

    public class wbClient
    {
        private LogMessage LMessageDel;
        private DataMessage DMessageDel;

        public Socket Server { get; private set; }

        public wbClient(string ip, int port, LogMessage ldel, DataMessage ddel)
        {
            LMessageDel = ldel;
            DMessageDel = ddel;
            Init(ip, port);
        }

        public void SendMessage(Socket sock, string msg)
        {
            Send(sock, msg);
            //byte[] smsg = Encoding.Default.GetBytes(msg);
            //sock.Send(smsg, smsg.Length, SocketFlags.None); // 문자열 전송
        }

        public void DisConnect()
        {         
            IPEndPoint ip = (IPEndPoint)Server.RemoteEndPoint;
            string temp = string.Format("{0}#{1}",
                ip.Address, ip.Port);
            LMessageDel(LogType.DisConnect, temp);

            Server.Close();
        }

        private void Init(string ip, int port)
        {
            try
            {
                IPEndPoint ipep = new IPEndPoint(IPAddress.Parse(ip), port);
                Server = new Socket(AddressFamily.InterNetwork,
                                         SocketType.Stream, ProtocolType.Tcp);
                Server.Connect(ipep);  // 127.0.0.1 서버 7000번 포트에 접속시도
                string temp = string.Format("{0}#{1}",
                        ipep.Address, ipep.Port);
                LMessageDel(LogType.Connect, temp);  // 만약 서버 접속이 실패하면 예외 발생

                //==================================
                Thread thread = new Thread(RecvThread);
                thread.IsBackground = true;
                thread.Start(Server);
                //==================================
            }
            catch(Exception ex)
            {
                LMessageDel(LogType.Error, ex.Message);  // 만약 서버 접속이 실패하면 예외 발생
            }
        }
   

        private void RecvThread(Object obj)
        {
            Socket client = (Socket)obj;
            IPEndPoint ip = (IPEndPoint)client.RemoteEndPoint;
            string temp = string.Format("{0}#{1}",
                ip.Address, ip.Port);
           
            while (true)
            {
                try
                {
                    byte[] data = ReceiveData(client);
                    string str = Encoding.Default.GetString(data);
                    DMessageDel(client, str);
                }
                catch (Exception)
                {
                  //  if (client.Connected == false)
                  //      return;

                    LMessageDel(LogType.DisConnect, temp);
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
