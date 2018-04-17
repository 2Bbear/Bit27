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
using System.Net;
using System.Net.Sockets;

using System.Threading;

namespace Winform_0417
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
            try
            {
                client = new wbClient(ip, port, LogMessage, DataMessage);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                textBox1.Text +="[에러]"+ ex.ToString()+"\r\n";
            }
            finally
            {
            }
        }

        public void LogMessage(LogType ltype, string msg)
        {
            if (ltype == LogType.Connect)
            {
                string[] temp = msg.Split('#');
                Console.WriteLine("[서버 접속] {0}:{1}",
                    temp[0], temp[1]);
            }
            else if (ltype == LogType.DisConnect)
            {
                string[] temp = msg.Split('#');
                Console.WriteLine("[서버 접속 해제] {0}:{1}",
                    temp[0], temp[1]);
            }
            else
            {
                Console.WriteLine(msg);
            }
        }

        public void DataMessage(Socket sock, string msg)
        {
            Console.WriteLine(msg);
        }

        private void serverConnetToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ServerConnectForm dlg = new ServerConnectForm();
            if(dlg.ShowDialog()==DialogResult.OK)
            {
                Run(dlg.ip, dlg.Port);
            }
        }

        private void serverDisConnectToolStripMenuItem_Click(object sender, EventArgs e)
        {
            client.DistConnect();
        }

        private void programExitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
