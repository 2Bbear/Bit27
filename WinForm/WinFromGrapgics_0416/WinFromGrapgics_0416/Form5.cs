using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WinFromGrapgics_0416
{
    public partial class Form5 : Form
    {
        public Form5()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            //리스트에 아이템 추가하기
            listBox1.Items.Add(textBox1.Text);
        }

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            label1.Text = listBox1.SelectedItem.ToString();
        }

        private void listBox1_DrawItem(object sender, DrawItemEventArgs e)
        {
            Graphics grfx = listBox1.CreateGraphics();
            Brush brush = Brushes.Black;
            switch(e.Index)
            {
                case 0: { brush = Brushes.Red; break; }
                case 1: { brush = Brushes.Violet; break; }
                case 2: { brush = Brushes.Green;  break; }

            }
            grfx.DrawString(listBox1.Items[e.Index].ToString(),e.Font,brush,e.Bounds,StringFormat.GenericDefault);

        }
    }
}
