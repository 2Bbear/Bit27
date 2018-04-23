using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using wb.lib;
using System.Net;
using System.Net.Sockets;
using System.Configuration;

namespace Server_0423
{
    class Control
    {
        #region SingleTone
        private wbServer server;
        public Form1 Mainform1 { get; set; }
        private static Control singleTone;
        public static Control Instance { get => singleTone; private set => singleTone = value; }
        private Control()
        {
            string serverport = ConfigurationManager.AppSettings["wbServerPort"];
            server = new wbServer(int.Parse(serverport), LogMessage, DataMessage);
        }
        static Control()
        {
            Instance = new Control();
        }

        #endregion
        //public void ServerConnect(int port)
        //{
        //    try
        //    {
        //        server = new wbServer(port, LogMessage, DataMessage);
        //    }
        //    catch (Exception ex)
        //    {
        //        MessageBox.Show(ex.ToString());
        //    }
        //    finally
        //    {
        //    }
        //}
       



        #region DB Method
        /// <summary>
        /// 계좌를 생성하는 함수
        /// @string name: 이름
        /// @int balance : 잔액
        /// int acctype : 계좌 종류
        /// DataTime time : 개설일자
        /// </summary>
        /// <returns>해당 함수가 성공했는지 실패했는지 반환</returns>
        private bool InsertAccount(String name, int balance,int acctype,DateTime time)
        {
            bool result = false;

            result= wbDB.Instance.InsertAccount(name,balance, acctype, time);

            return result;

        }

        private string SelectAllAccount()
        {
            String result =wbDB.Instance.SelectAllAccount();



            return result;
        }

        private bool DeleteAccount(int accID)
        {
            bool result = wbDB.Instance.DeleteAccount(accID);
            return result;
        }
        
        private bool InputAccount(int accID,int _inputmoney)
        {
            bool result = wbDB.Instance.InputAccount(accID, _inputmoney);
            return result;
        }
        private bool OutputAccount(int accID, int _outputmoney)
        {
            bool result = wbDB.Instance.OutputAccount(accID, _outputmoney);
            return result;
        }


        #endregion

       


        #region Scoket Code
        public void LogMessage(LogType ltype, string msg)
        {
            Mainform1.printLogMessage("로그메세지");
            if (ltype == LogType.ClientConnect)
            {
                string[] temp = msg.Split('#');
                String sendmessage = "[클라이언트 접속] "+temp[0]+" : "+temp[1];
                Mainform1.printLogMessage(sendmessage);
                Console.WriteLine();
            }
            else if (ltype == LogType.ClientClose)
            {
                string[] temp = msg.Split('#');
                Console.WriteLine();
                String sendmessage = "[클라이언트 해제] " + temp[0] + " : " + temp[1];
                Mainform1.printLogMessage(sendmessage);
            }
            else
            {
                Console.WriteLine(msg);
            }
        }

        public void DataMessage(Socket sock, string msg)
        {
            string[] filter = msg.Split('@');
            //InsertAccount
            if (filter[0].Equals("PACK _INSERTACCOUNT"))
            {
                string[] filter1 = filter[1].Split('#');
               
                string name = filter1[0];
                int acctype = int.Parse(filter1[1]);
                int balance = int.Parse(filter1[2]);
                String sendmessage = "[계좌 생성] " + filter1[0] + " : " + filter1[1] + " : "+ filter1[2];
                Mainform1.printLogMessage(sendmessage);
                //==========================================
                //저장
                string pack;
                if (InsertAccount(name, balance, acctype, DateTime.Now))
                {
                    pack = Packet.InsertAccountResult(name, true);

                }
                else
                {
                    pack = Packet.InsertAccountResult(name, false);
                }
                //===================================================
                server.SendMessage(sock, msg);
            }
            //SelectAllAccount
            else if(filter[0].Equals("PACK _SELECTACCOUNT"))
            {
                

                string name = filter[1];

                //==========================================
                //저장
                string pack;
                string str = SelectAllAccount();

                pack = Packet.SelectAllAccountResult(str);
                
                //===================================================
                server.SendMessage(sock, msg);
            }
            //DeleteAccount
            else if(filter[0].Equals("PACK _DELETEACCOUNT"))
            {
                int accid = int.Parse(filter[1]);
                string pack;

                String sendmessage = "[계좌 삭제] " + filter[1];
                Mainform1.printLogMessage(sendmessage);

                if (DeleteAccount(accid) == false)
                {
                    pack = Packet.DeleteAccount(accid, false);
                }
                else
                {
                    pack = Packet.DeleteAccount(accid, true);
                }
                //===================================================
                server.SendMessage(sock, msg);
            }
            //InputAccount
            else if (filter[0].Equals("PACK _INPUTACCOUNT"))
            {
                string[] filter1 = filter[1].Split('#');

                int accid = int.Parse(filter1[0]);
                int input = int.Parse(filter1[1]);

                string pack;

                String sendmessage = "[계좌 입금] " + filter1[0];
                Mainform1.printLogMessage(sendmessage);

                if (InputAccount(accid, input) == false)
                {
                    pack = Packet.InputAccount(accid,false);
                }
                else
                {
                    pack = Packet.InputAccount(accid, true);
                }
                //===================================================
                server.SendMessage(sock, msg);
            }
            //OutAccount
            else if (filter[0].Equals("PACK _OUTPUTACCOUNT"))
            {
                string[] filter1 = filter[1].Split('#');

                int accid = int.Parse(filter1[0]);
                int output = int.Parse(filter1[1]);

                string pack;

                String sendmessage = "[계좌 출금] " + filter1[0];
                Mainform1.printLogMessage(sendmessage);

                if (OutputAccount(accid, output) == false)
                {
                    pack = Packet.OutputAccount(accid, false);
                }
                else
                {
                    pack = Packet.OutputAccount(accid, true);
                }
                //===================================================
                server.SendMessage(sock, msg);
            }


            #region temp

            //else if (filter[0].Equals("NICKNAMECHECK"))
            //{
            //    //"NICKNAMECHECK@NICKNAME
            //    string pack;
            //    if (CheckNickanme(filter[1]) == true)
            //    {
            //        pack = Packet.NickNameCheckResult(filter[1], true);
            //    }
            //    else
            //    {
            //        pack = Packet.NickNameCheckResult(filter[1], false);
            //    }
            //    server.SendMessage(sock, pack);
            //}
            //else if (filter[0].Equals("IDCHECK"))
            //{
            //    //IDCHECK@아이디
            //    string pack;
            //    if (CheckID(filter[1]) == true)
            //    {
            //        pack = Packet.IDCheckResult(filter[1], true);
            //    }
            //    else
            //    {
            //        pack = Packet.IDCheckResult(filter[1], false);
            //    }
            //    server.SendMessage(sock, pack);
            //}
            //else if (filter[0].Equals("NEWMEMBER"))
            //{
            //    //NEWMEMBER@아이디#패스워드#닉네임
            //    string[] filter1 = filter[1].Split('#');
            //    string pack = "";
            //    try
            //    {
            //        memlist.Add(new Member(filter1[0], filter1[1], filter1[2]));
            //        pack = Packet.NewMember(filter1[0], true);
            //    }
            //    catch (Exception)
            //    {
            //        pack = Packet.NewMember(filter1[0], false);
            //    }
            //    finally
            //    {
            //        server.SendMessage(sock, pack);
            //    }
            //}
            //Console.WriteLine(">> " + msg);        
            #endregion

        }
        #endregion

        #region DB Code
        //테스트용 메소드
        public void DBAccess(int flag)
        {
            //계좌생성
            if (flag == 1)
            {
                if (InsertAccount("장정호", 1000, 1, DateTime.Now))
                {
                    MessageBox.Show("성공");

                }
                else
                {
                    MessageBox.Show("실패");
                }

            }
            //모든 계좌 검색
            else if (flag == 2)
            {
                string str = SelectAllAccount();
                if (str == "")
                {
                    MessageBox.Show("실패");
                }
                else
                {
                    MessageBox.Show(str);
                }

            }
            //계좌삭제
            else if (flag == 3)
            {

                if (DeleteAccount(83010) == false)
                {
                    MessageBox.Show("실패");
                }
                else
                {
                    MessageBox.Show("성공");
                }

            }
            //계좌입금
            else if (flag == 4)
            {

                if (InputAccount(84010, 1000) == false)
                {
                    MessageBox.Show("실패");
                }
                else
                {
                    MessageBox.Show("성공");
                }

            }
            //계좌출금
            else if (flag == 5)
            {
                if (OutputAccount(84010, 1000) == false)
                {
                    MessageBox.Show("실패");
                }
                else
                {
                    MessageBox.Show("성공");
                }

            }

        }
        #endregion
    }
}
