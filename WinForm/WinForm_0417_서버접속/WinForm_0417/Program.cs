using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using System.Net;
using System.Net.Sockets;
using System.IO;

namespace WinForm_0417
{
    class Program
    {
        //#region Server
        //static void Main(string[] args)
        //{
        //    IPEndPoint ipep = new IPEndPoint(IPAddress.Any, 7000);
        //    Socket server = new Socket(AddressFamily.InterNetwork,
        //                                              SocketType.Stream, ProtocolType.Tcp);
        //    server.Bind(ipep);
        //    server.Listen(20);

        //    Console.WriteLine("서버 시작... 클라이언트 접속 대기중...");

        //    try
        //    {
        //        while (true)
        //        {
        //            Socket client = server.Accept();  // 클라이언트 접속 대기
        //                                              // 접속한 클라이언트 아이피 주소와 접속 포트번호 출력
        //            IPEndPoint ip = (IPEndPoint)client.RemoteEndPoint;
        //            Console.WriteLine("{0}주소, {1}포트 접속", ip.Address, ip.Port);

        //            //thread 호출
        //            //비동기 호출
        //            Thread thread = new Thread(ThreadFun);
        //            thread.Start(client);

        //            data = new byte[1024];

        //            ThreadFun();


        //            client.Close();         //  소켓 연결 끊기
        //        }
        //    }
        //    catch (Exception ex)
        //    {
        //        Console.WriteLine("서버 대기 오류"+ex.Message);
        //    }
        //    finally
        //    {
        //        server.Close();
        //    }

        //}

        //static void ThreadFun(Object obj)
        //{
        //    Socket client = (Socket)obj;
        //    while(true)
        //    {
        //        byte[] data = new byte[1024];
        //        try
        //        {
        //            if (client.Receive(data) != 0)   // 수신한 문자열이 있으면 화면에 출력
        //                Console.WriteLine("수신 메시지: " + Encoding.Default.GetString(data));
        //            else
        //                break;

        //            client.Send(data, data.Length, SocketFlags.None); // 문자열 전송
        //        }
        //        catch (Exception ex)
        //        {
        //            Console.WriteLine("통신오류"+ex.Message);
        //        }
        //        finally
        //        {
        //        }




        //    }

        //}
        //#endregion

        #region Client

        static void Main(string[] args)
        {
            IPEndPoint ipep = new IPEndPoint(IPAddress.Parse("192.168.0.33"), 7000);

            Socket server = new Socket(AddressFamily.InterNetwork,
                                     SocketType.Stream, ProtocolType.Tcp);

            server.Connect(ipep);  // 127.0.0.1 서버 7000번 포트에 접속시도

            Console.WriteLine("서버에 접속...");  // 만약 서버 접속이 실패하면 예외 발생


            #region Sending 

            string strSend = Console.ReadLine();
            Console.WriteLine("송신 : " + strSend);
            server.Send(Encoding.Default.GetBytes(strSend));

            #endregion

            #region Receive

            String sizeStr = "";
            byte[] dataSize = new byte[2];
            server.Receive(dataSize);//받을 데이터 크기
            sizeStr = Encoding.Default.GetString(dataSize);
           // int size = int.Parse(sizeStr);
            Console.WriteLine("크기 : " + sizeStr);

            //string strReceve = "";
            //byte[] data = new byte[1024];
            //server.Receive(data);//받을 데이터 크기
            //strReceve = Encoding.Default.GetString(data);
            //Console.WriteLine("수신 : " + strReceve);

            #endregion





            server.Close();
        }
        #endregion
    }
}
