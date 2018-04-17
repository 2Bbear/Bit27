using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Winform_0417
{
    public partial class ServerConnectForm : Form
    {
        public string ip
        {
            get { return textBox1.Text; }

        }
        public int Port
        {
            get { return int.Parse(textBox2.Text); }
        }

        public ServerConnectForm()
        {
            InitializeComponent();
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.OK;
            this.Close();
        }
    }
}
