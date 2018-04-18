using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using wb.lib;

namespace _0417_FormClient
{
    public partial class NewMemberForm : Form
    {
        private bool ischeckNickName = false;
        private bool ischeckId = false;

        public string NickName { get; private set; }
        public string Id { get; private set; }
        public string Password { get; private set;  }

        public wbClient Net { get;  set; }

        public NewMemberForm()
        {
            InitializeComponent();
        }

        public void CheckNicknameResult(bool b)
        {
            if (b == true)
            {
                ischeckNickName = true;
                label5.ForeColor = Color.Blue;
                label5.Text = "사용 가능합니다.";
            }
            else
            {
                label5.ForeColor = Color.Red;
                label5.Text = "중복된 닉네임입니다.";
            }
        }

        public void CheckIDResult(bool b)
        {
            if (b == true)
            {
                ischeckId = true;
                label6.ForeColor = Color.Blue;
                label6.Text = "사용 가능합니다.";
            }
            else
            {
                label6.ForeColor = Color.Red;
                label6.Text = "중복된 아이디입니다.";
            }
        }

        //가입
        private void button3_Click(object sender, EventArgs e)
        {
            if (ischeckId && ischeckNickName)
            {
                NickName = textBox1.Text;
                Id = textBox2.Text;
                Password = textBox3.Text;
                DialogResult = DialogResult.OK;
                this.Close();
            }
            else
            {
                MessageBox.Show("중복 체크 여부 확인 요망");
            }
        }

        //NickName 중복
        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                string str = Packet.NickNameCheck(textBox1.Text);
                Net.SendMessage(Net.Server, str);
  
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        //ID 중복
        private void button2_Click(object sender, EventArgs e)
        {
            try
            {
                string str = Packet.IDCheck(textBox2.Text);
                Net.SendMessage(Net.Server, str);
  
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }


        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            ischeckNickName = false;
            label5.Text = "중복 여부를 확인하세요";
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {
            ischeckId = false;
            label6.Text = "중복 여부를 확인하세요";
        }


        private void textBox3_TextChanged(object sender, EventArgs e)
        {
            if (textBox3.Text.Length > 0)
                label7.Text = "";
            else
                label7.Text = "패드워드를 입력하세요";
        }


        private void textBox4_TextChanged(object sender, EventArgs e)
        {
            if (textBox4.Text.Equals(textBox3.Text))
            {
                label8.ForeColor = Color.Blue;
                label8.Text = "사용 가능합니다.";
            }
            else
            {
                label8.ForeColor = Color.Red;
                label8.Text = "패스워드가 다릅니다.";
            }
        }
    }
}
