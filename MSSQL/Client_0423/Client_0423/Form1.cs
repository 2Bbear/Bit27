using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net.Sockets;
using wb.lib;

namespace Client_0423
{
    public partial class Form1 : Form
    {
        private wbClient client;

        public Form1()
        {
            InitializeComponent();
            client = new wbClient("192.168.0.52", 7000, LogMessage, DataMessage);
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

            textBox3.Text += str + "\r\n";
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            for(int i=0; i<100000;i++)
            {
                client.SendMessage(client.Server, "PACK_INPUTACCOUNT@179010#1000000");
            }
           
          
        }
    }
}
