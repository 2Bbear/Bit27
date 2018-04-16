using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WinFormPowerPoint_0416
{
    public partial class FileOpenForm : Form
    {
        
        public FileOpenForm()
        {
            InitializeComponent();
        }

        private string fileName;
        public string FileName { get { return textBox1.Text; } set => fileName = value; }

        private void button1_Click(object sender, EventArgs e)
        {


            //종료
            this.DialogResult = DialogResult.OK;
            this.Close();
        }
    }
}
