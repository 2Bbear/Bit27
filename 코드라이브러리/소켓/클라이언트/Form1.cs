using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using wb.lib;

namespace _0417_FormClient
{
    public partial class Form1 : Form
    {
        private wbClient client;
        NewMemberForm form = new NewMemberForm();
        LogInForm logInForm ;
        UpdateNickNameForm temp;


        public String currentID;
        public String currentNickName;

        public Form1()
        {
            InitializeComponent();
            logInForm = new LogInForm(this);
            SetNickNameBox("");


        }
        public void SetNickNameBox(string nickName)
        {
            textBox3.Text = nickName;
        }
        public void Run(string ip, int port)
        {
            client = new wbClient(ip, port, LogMessage, DataMessage);

            //while (true)
            //{
            //    try
            //    {
            //        string str = Console.ReadLine();

            //        client.SendMessage(client.Server, str);
            //    }
            //    catch (Exception ex)
            //    {
            //        Console.WriteLine(ex.Message);
            //    }
            //}
        }

        public void LogMessage(LogType ltype, string msg)
        {
            string str;
            if (ltype == LogType.Connect)
            {
                string[] temp = msg.Split('#');
                str = string.Format("[서버 접속] {0}:{1}",
                    temp[0], temp[1]);
            }
            else if (ltype == LogType.DisConnect)
            {
                string[] temp = msg.Split('#');
                str = string.Format("[서버 접속 해제] {0}:{1}",
                    temp[0], temp[1]);
            }
            else
            {
                str = string.Format(msg);
            }
            CheckForIllegalCrossThreadCalls = false;        //<++++++++++++++++++++++++++++++++++++++

            textBox1.Text += str + "\r\n";
        }

        public void DataMessage(Socket sock, string msg)
        {   
            string[] filter = msg.Split('@');
            if (filter[0].Equals("SENDMESSAGE"))
            {
                string[] filter1 = filter[1].Split('#');
                string nickname = filter1[0];
                string message = filter1[1];
                //출력
                string print = string.Format("[{0}] {1}",
                    nickname, message);
                textBox1.Text += print + "\r\n";
            }
            else if (filter[0].Equals("ACK_NICKNAMECHECK"))
            {
                
                //ACK_NICKNAMECHECK@닉네임#TRUE
                //ACK_NICKNAMECHECK@닉네임#FALSE
                string[] filter1 = filter[1].Split('#');
                if( filter1[1].Equals("TRUE"))
                {
                    form.CheckNicknameResult(true);
                  }
                else
                {
                    form.CheckNicknameResult(false);
                }
            }
            else if (filter[0].Equals("ACK_IDCHECK"))
            {
                
                //ACK_IDCHECK@아이디#TRUE
                //ACK_IDCHECK@아이디#FALSE
                string[] filter1 = filter[1].Split('#');
                if (filter1[1].Equals("TRUE"))
                {
                    form.CheckIDResult(true);
                    
                }
                else
                {
                    form.CheckIDResult(false);
                    
                }
            }
            else if (filter[0].Equals("ACK_NEWMEMBER"))
            {
                //ACK_NEWMEMBER@아이디#TRUE
                //ACK_NEWMEMBER@아이디#FALSE
                string[] filter1 = filter[1].Split('#');
                if (filter1[1].Equals("TRUE"))
                {
                    NewMember(filter1[0], true);
                }
                else
                {
                    NewMember(filter1[0], false);
                }
            }
            //Login Message
            else if(filter[0].Equals("ACK_LOGIN"))
            {
                //ACK_LOGIN @닉네임#TRUE
                //ACK_LOGIN @닉네임#FALSE
                
                string[] filter1 = filter[1].Split('#');
                if (filter1[1].Equals("TRUE"))
                {
                    currentNickName = filter1[0];
                    logInForm.CheckLogidId(true);
                    SetNickNameBox(currentNickName);

                    // form.CheckIDResult(true);

                }
                else if(filter1[1].Equals("FALSE"))
                {
                    
                   
                    logInForm.CheckLogidId(false);
                   
                    
                    //form.CheckIDResult(false);
                }
            }
            //DelMeber Message
            else if(filter[0].Equals("ACK_DELMEMBER"))
            {
                //ACK_DELMEMBER @아이디#TRUE
                //ACK_DELMEMBER @아이디#FALSE
                string[] filter1 = filter[1].Split('#');
                if (filter1[1].Equals("TRUE"))
                {
                    textBox1.Text += String.Format("{0}이 삭제 되었습니다.", filter1[0]);
                    logInForm.CheckLogidId(false);
                    회원탈퇴ToolStripMenuItem.Enabled = false;
                    회원가입ToolStripMenuItem.Enabled = true;
                    로그인ToolStripMenuItem.Enabled = true;
                    회원정보수정ToolStripMenuItem.Enabled = false;
                    로그아웃ToolStripMenuItem.Enabled = false;
                }
                else if (filter1[1].Equals("FALSE"))
                {
                    textBox1.Text += String.Format("{0}의 삭제에 실패 했습니다..", filter1[0]);
                }
            }
            //회원 닉네임 수정
            else if(filter[0].Equals("ACK_UPDATENICKNAME"))
            {
                //ACK_UPDATENICKNAME @수정할닉네임#TRUE
                // ACK_UPDATENICKNAME @수정할닉네임#FALSE
                string[] filter1 = filter[1].Split('#');
                if (filter1[1].Equals("TRUE"))
                {
                    currentNickName = filter1[0];
                    textBox1.Text += String.Format("{0} 닉네임 변경 성공", currentNickName) + "\r\n";
                    SetNickNameBox(currentNickName);
                }
                else if (filter1[1].Equals("FALSE"))
                {
                    textBox1.Text += "닉네임 변경 실패" + "\r\n";
                }
            }
            //로그아웃

            //전체 회원리스트 얻기
        }
        private void LogIn(string _nickname, bool b)
        {
            if (b)
            {
                string print = "[알림]" + _nickname + "님이 로그인 하셨습니다.";
                textBox1.Text += print + "\r\n";
            }
            else
            {
                string print = "[알림]" + _nickname + "님이 로그인에 실패하셨습니다.";
                textBox1.Text += print + "\r\n";
            }
        }

        private void NewMember(string nickname, bool b)
        {
            if( b )
            {
                string print = "[알림]" + nickname + "님의 회원가입 성공";
                textBox1.Text += print + "\r\n";
            }
            else
            {
                string print = "[알림]" + nickname + "님의 회원가입 실패";
                textBox1.Text += print + "\r\n";
            }
        }


        private void 서버연결ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ServerConnectForm dlg = new ServerConnectForm();
            if(dlg.ShowDialog() == DialogResult.OK)
            {
                Run(dlg.Ip, dlg.Port);

                서버연결ToolStripMenuItem.Enabled = false;
                서버연결해제ToolStripMenuItem.Enabled = true;
                button1.Enabled = true;
            }
        }

        private void 서버연결해제ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            client.DisConnect();

            서버연결ToolStripMenuItem.Enabled = true;
            서버연결해제ToolStripMenuItem.Enabled = false;
            button1.Enabled = false;
        }

        private void 프로그램종료ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
             //   string str = Packet.SendMessage(textBox3.Text, textBox2.Text);
              //  client.SendMessage(client.Server, str);
            //    textBox1.Text += "[ME]" + str + "\r\n";
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }


        private void 회원가입ToolStripMenuItem_Click(object sender, EventArgs e)
        {            
            form.Net = client;

            if( form.ShowDialog() == DialogResult.OK)
            {
                try
                {
                    string str = Packet.NewMember(form.NickName, form.Id, form.Password);
                    client.SendMessage(client.Server, str);
                }
                catch (Exception ex)
                {
                    Console.WriteLine(ex.Message);
                }
            }
        }

        private void 로그인ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            logInForm.Net = client;
            if (logInForm.ShowDialog()==DialogResult.OK)
            {
                try
                {
                    회원탈퇴ToolStripMenuItem.Enabled = true;
                    회원가입ToolStripMenuItem.Enabled = false;
                    로그인ToolStripMenuItem.Enabled = false;
                    회원정보수정ToolStripMenuItem.Enabled = true;
                    로그아웃ToolStripMenuItem.Enabled = true;
                    textBox1.Text += "로그인에 성공했습니다.";
                    //String str=Packet.LogIn()

                }
                catch (Exception ex)
                {
                    Console.WriteLine(ex.Message);
                }
                finally
                {
                }
            }
        }

        private void 회원탈퇴ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            try
            {
                string str = Packet.DelMember(currentID);
                client.SendMessage(client.Server, str);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        private void 회원정보수정ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            temp = new UpdateNickNameForm(this);
            if(temp.ShowDialog()==DialogResult.OK)
            {
                try
                {
                    string str = Packet.UpdateNickName(currentNickName, temp.newNickName);
                    client.SendMessage(client.Server, str);
                }
                catch (Exception ex)
                {
                    Console.WriteLine(ex.Message);
                }
            }
           
        }
    }
}
