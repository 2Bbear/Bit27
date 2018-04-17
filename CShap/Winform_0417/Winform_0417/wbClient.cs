﻿using System;
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
            byte[] smsg = Encoding.Default.GetBytes(msg);
            sock.Send(smsg, smsg.Length, SocketFlags.None); // 문자열 전송
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
            catch (Exception ex)
            {
                LMessageDel(LogType.Error, ex.Message);  // 만약 서버 접속이 실패하면 예외 발생
            }
        }

        public void DistConnect()
        {
            Server.Close();
            IPEndPoint ip = (IPEndPoint)Server.RemoteEndPoint;
            string temp = string.Format("{0}#{1}", ip.Address, ip.Port);

            LMessageDel(LogType.DisConnect ,temp);

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
                    string str = Encoding.Default.GetString(data, 0, value);
                    DMessageDel(client, str);
                }
                catch (Exception)
                {
                    IPEndPoint ip = (IPEndPoint)client.RemoteEndPoint;
                    string temp = string.Format("{0}#{1}",
                        ip.Address, ip.Port);
                    LMessageDel(LogType.DisConnect, temp);
                    client.Close();
                    return;
                }
            }
        }
    }
}
