using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;
using wb.lib;

namespace _0417_FormClient
{
    public partial class LogInForm : Form
    {
        public string Id { get; private set; }
        public string Password { get; private set; }
        private Form1 Parents;
        private bool isLogIn = false;

        public  int textnum = 0;

        public wbClient Net { get; set; }

        public LogInForm(Form1 _p)
        {
            InitializeComponent();
            Parents = _p;
        }
        public void CheckLogidId(bool b)
        {
            
            if (b == true)
            {
               
                isLogIn = true;
                
                
                
            }
            else
            {
                
                isLogIn = false;

            }
        }
        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                //컨트롤에서 값 받아오기
                Id = textBox1.Text;
                Password = textBox2.Text;
                //해당 값으로 서버에 접속 가능한지 확인
                //Net.SendMessage(Net.Server,Packet.LogIn(Id, Password));
                string str = Packet.LogIn(textBox1.Text,textBox2.Text);
                Net.SendMessage(Net.Server, str);

                Thread.Sleep(500);//현재 이 스레드가 먼저 실행되기 때문에. 0.5초 기다려야함.
                if (isLogIn)
                {
                    Parents.currentID = textBox1.Text;
                    MessageBox.Show("로그인에 성공했습니다.");
                    DialogResult = DialogResult.OK;
                    this.Close();
                }
                else
                {
                    MessageBox.Show("아이디와 비밀번호가 맞지 않아 로그인에 실패했습니다.");
                }

                
                

            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }
    }
}
