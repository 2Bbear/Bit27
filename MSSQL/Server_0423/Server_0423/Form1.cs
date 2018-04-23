using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Configuration;

namespace Server_0423
{
    public partial class Form1 : Form
    {
        //Control con;
        public Form1()
        {
            InitializeComponent();
            Control.Instance.Mainform1 = this;
        }

        //Insert Account
        private void button1_Click(object sender, EventArgs e)
        {
            Control.Instance.DBAccess(1);
        }
        //select All Account
        private void button2_Click(object sender, EventArgs e)
        {
            Control.Instance.DBAccess(2);
        }
        //DeleteAccount
        private void button3_Click(object sender, EventArgs e)
        {
            Control.Instance.DBAccess(3);
        }
        //InputAccount
        private void button4_Click(object sender, EventArgs e)
        {
            Control.Instance.DBAccess(4);
        }
        //OutputAccount
        private void button5_Click(object sender, EventArgs e)
        {
            Control.Instance.DBAccess(5);
        }

        public void printLogMessage(String str)
        {
            //크로스 쓰레드 문제 해결
            this.Invoke(new MethodInvoker(delegate () { textBox1.Text += str + "\r\n"; }));   
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            // TODO: This line of code loads data into the 'wb271DataSet.Account' table. You can move, or remove it, as needed.
            this.accountTableAdapter.Fill(this.wb271DataSet.Account);

        }

        private void button1_Click_1(object sender, EventArgs e)
        {
            Control.Instance.DBAccess(1);

            //con = new Control(this);
            //string serverport = ConfigurationManager.AppSettings["wbServerPort"];
            //con.Serverconnect(int.Parse(serverport))


        }
    }
}
