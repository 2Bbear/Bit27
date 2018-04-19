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

namespace _0419_DBBaseBall
{
    public partial class Form1 : Form
    {
        public bool IsLogin { get; private set;  }

        wbDB db = new wbDB();

        public Form1()
        {
            InitializeComponent();
            IsLogin = false;
        }

        //서버 접속
        private void button1_Click(object sender, EventArgs e)
        {
            if( db.Open() )
            {
                button1.Enabled = false;
                button2.Enabled = true;
                IsLogin = true;
            }
        }

        //서버 접속 해제
        private void button2_Click(object sender, EventArgs e)
        {
            db.Close();

            button1.Enabled = true;
            button2.Enabled = false;
            IsLogin = false;
        }
        
        //선수등록
        private void button3_Click(object sender, EventArgs e)
        {
            if (db.MemberJoin(textBox1.Text, true) == false)
            {
                MessageBox.Show("에러");
                return;
            }
        }

        //선수삭제
        private void button4_Click(object sender, EventArgs e)
        {
            if(db.MemberJoin(textBox1.Text, false)== false)
            {
                MessageBox.Show("에러");
                return;
            }
        }

        //불러오기
        private void button5_Click(object sender, EventArgs e)
        {
            int count = db.MemberCount();
            if (count < 0)
                return;

            label3.Text = count + "명";
            label7.Text = count.ToString();
            //=========================================
            List<string> namelist = db.MemberNameList();
            if (namelist == null)
                return;

            listBox1.Items.Clear();
            foreach(string name in namelist)
            {
                listBox1.Items.Add(name);
            }
        }

        //시뮬레이션
        private void button6_Click(object sender, EventArgs e)
        {
            Random r = new Random();

            int mem_count = int.Parse(label7.Text);    
            
            for (int i = 0; i < mem_count; i++)
            {
                string name = listBox1.Items[i].ToString();
                int result = -1;
                int value = r.Next(0, 20);//0~19
                if (value == 3) //홈런
                {
                    result = 1;
                }
                else if (value == 5) //3루타
                {
                    result = 2;
                }
                else if (value == 1 || value == 18)//2루타
                {
                    result = 3;
                }
                else if (value == 8 || value == 10 || value == 15)//1루타
                {
                    result = 4;
                }
                else    //아웃
                {
                    result = 5;
                }
                //========================================
                if(db.InsertData(name, result)==true)
                {
                    db.MemberUpdate(name, result);
                }
                //========================================
            }
            
        }

        private void button7_Click(object sender, EventArgs e)
        {
            listView1.Items.Clear();
            string value= "";
            
            if(radioButton1.Checked ==true)
            {
                value = "AVERAGE";
            }
            else if (radioButton2.Checked == true)
            {
                value = "HOMERUN";
            }
            else if (radioButton3.Checked == true)
            {
                value = "HIT3";
            }
            else if (radioButton4.Checked == true)
            {
                value = "HIT2";
            }
            else if (radioButton5.Checked == true)
            {
                value = "HIT1";
            }

            
            db.ListViewPrint(value, this);
            MessageBox.Show("dad3");
        }
    }
}
