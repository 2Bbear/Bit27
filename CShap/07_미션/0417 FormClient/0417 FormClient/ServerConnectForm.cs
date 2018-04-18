using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _0417_FormClient
{
    public partial class ServerConnectForm : Form
    {
        public string Ip
        {
            get { return textBox1.Text;  }
        }

        public int Port
        {
            get { return int.Parse(textBox2.Text); }
        }

        public ServerConnectForm()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.OK;
            this.Close();
        }
    }
}
