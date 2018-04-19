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
namespace SQL_Form_0419
{
    public partial class Form1 : Form
    {
        public bool IsLogin { get;private  set; }

        public WbDB my_db=new WbDB();

        List<String> namelist = null;
        public Form1()
        {
            InitializeComponent();
            IsLogin = false;
        }

        //서버 접속
        private void button1_Click(object sender, EventArgs e)
        {
            
            if(my_db.Open())
            {
                button1.Enabled = false;
                button2.Enabled = true;
                IsLogin = true;
                MessageBox.Show("서버 열림");
            }
            else
            {
                MessageBox.Show("서버 안열림");
            }
        }
        //서버 접속 해제
        private void button2_Click(object sender, EventArgs e)
        {
            my_db.Close();
            button1.Enabled = true;
            button2.Enabled = false;
            IsLogin = false;
        }

        private void label3_Click(object sender, EventArgs e)
        {

        }
        
        //선수 등록
        private void button3_Click(object sender, EventArgs e)
        {
            if (my_db.MemberJoin(textBox1.Text, true) == true)
            {
                MessageBox.Show("등록 성공");
            }
            else
            {
                MessageBox.Show("등록 실패");
            }
        }
        //선수 삭제
        private void button4_Click(object sender, EventArgs e)
        {
            if (my_db.MemberJoin(textBox1.Text, false) == true)
            {
                MessageBox.Show("삭제 성공");
            }
            else
            {
                MessageBox.Show("삭제 실패");
            }
        }
       
        //불러오기
        private void button5_Click(object sender, EventArgs e)
        {
            int count =my_db.MemberCount();
            
            if (count<0)
            {
                return;
            }
            else
            {

                //총원 출력
                label6.Text = count.ToString();
                label3.Text = count.ToString()+"명";
                //이름리스트 출력
                listBox1.Items.Clear();//리스트 초기화
                namelist = my_db.MemberNameList();
                foreach(String name in namelist)
                {
                    listBox1.Items.Add(name);
                }
            }
        }
        //시뮬레이션 
        private void button6_Click(object sender, EventArgs e)
        {
            Random r = new Random();
            int mem_count = int.Parse(label6.Text);
           
            

            for (int i =0;i<mem_count ;i++)
            {
                String name = namelist[i].ToString();
                int result = -1;

                int value = r.Next(0, 20);
                if (value == 8)//홈런
                {
                    result = 1;
                }
                else if (value == 3)//3루타
                {
                    result = 2;
                }
                else if (value == 2 || value == 6)//2타
                {
                    result = 3;
                }
                else if (value == 1 || value == 7 || value == 9)//1루타
                {
                    result = 4;
                }
                else//아웃
                {
                    result = 5;
                }

                if(my_db.InsertData(name, result) == true)
                {

                }
            }
            

        }
    }
}
