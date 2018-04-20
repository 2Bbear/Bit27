using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp3
{
    public partial class SettingOptionForm : Form
    {
        Form1 parants;
        //좌표
        public int x = 0;
        public int y = 0;
        //색상
        public Color currentColor;
        //문자열
        public String str;
        //글자크기
        public int fontSize;

        public SettingOptionForm(Form1 _parants)
        {
            InitializeComponent();
            parants = _parants;

            //초기화
            //x
            textBox1.Text = parants.target.X.ToString();
            x = parants.target.X;
            //y
            textBox2.Text = parants.target.Y.ToString();
            y = parants.target.Y;
            //color
            if (parants.target.CurrentColor==Color.Red)
            {
                comboBox1.SelectedIndex = 0;
                currentColor = Color.Red;
            }
            else if (parants.target.CurrentColor == Color.Green)
            {
                comboBox1.SelectedIndex = 1;
                currentColor = Color.Green;
            }
            else if (parants.target.CurrentColor == Color.Blue)
            {
                comboBox1.SelectedIndex = 2;
                currentColor = Color.Blue;
            }
            else
            {
                comboBox1.SelectedIndex = 0;
            }
            //string

            textBox3.Text = parants.target.Str;
            
        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.OK;

            str = textBox3.Text;

            this.Close();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (comboBox1.SelectedIndex == 0)
            {
             
                currentColor = Color.Red;
            }
            else if (comboBox1.SelectedIndex == 1)
            {
               
                currentColor = Color.Green;
            }
            else if (comboBox1.SelectedIndex == 2)
            {
                
                currentColor = Color.Blue;
            }
        }
    }
}
