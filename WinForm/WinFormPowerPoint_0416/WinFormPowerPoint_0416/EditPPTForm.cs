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
    public partial class EditPPTForm : Form
    {
        public String str;

        public EditPPTForm( )
        {
            InitializeComponent();
        }
        
      

        private void button1_Click(object sender, EventArgs e)
        {
            str=textBox1.Text;
            

            //종료
            this.DialogResult = DialogResult.OK;
            this.Close();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            //종료
            this.DialogResult = DialogResult.Cancel;
            this.Close();
        }
    }
}
