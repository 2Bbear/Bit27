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

        public Form1()
        {
            InitializeComponent();
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

            textBox1.Text += str + "\r\n";
        }

        public void DataMessage(Socket sock, string msg)
        {
            Console.WriteLine(msg);
            textBox1.Text += "[OTHER]" + msg + "\r\n";
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
                string str = textBox2.Text;
                client.SendMessage(client.Server, str);
                textBox1.Text += "[ME]" + str + "\r\n";
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }
    }
}
