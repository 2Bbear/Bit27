using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using BasicWCF_0508.ServiceReference1;


namespace BasicWCF_0508
{
    public partial class Form1 : Form
    {
        CalClient mycal = new CalClient();
        public Form1()
        {
            InitializeComponent();
        }
        //add
        private void button1_Click(object sender, EventArgs e)
        {
            textBox3.Text = mycal.Add(int.Parse(textBox1.Text), int.Parse(textBox2.Text)).ToString();
        }
        //sub
        private void button2_Click(object sender, EventArgs e)
        {
            textBox3.Text = mycal.Sub(int.Parse(textBox1.Text), int.Parse(textBox2.Text)).ToString();
        }
        //mul
        private void button3_Click(object sender, EventArgs e)
        {
            textBox3.Text = mycal.Mul(int.Parse(textBox1.Text), int.Parse(textBox2.Text)).ToString();
        }
        //div
        private void button4_Click(object sender, EventArgs e)
        {
            textBox3.Text = mycal.Div(int.Parse(textBox1.Text), int.Parse(textBox2.Text)).ToString();
        }
    }
}
