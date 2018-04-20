using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Timers;
using System.Threading;
namespace WindowsFormsApp3
{
    public partial class Form1 : Form
    {
        internal TextData target = new TextData();

        

        public Form1()
        {
            InitializeComponent();

            Thread t = new Thread(Time);
            t.Start();
           

        }
        public void DrawString()
        {
            System.Drawing.Graphics formGraphics = this.CreateGraphics();
            string drawString = target.Str;
            System.Drawing.Font drawFont = new System.Drawing.Font("Arial", target.FontSize);
            System.Drawing.SolidBrush drawBrush = new System.Drawing.SolidBrush(target.CurrentColor);
            float x = target.X;
            float y = target.Y;
            System.Drawing.StringFormat drawFormat = new System.Drawing.StringFormat();
            formGraphics.DrawString(drawString, drawFont, drawBrush, x, y, drawFormat);
            drawFont.Dispose();
            drawBrush.Dispose();
            formGraphics.Dispose();
        }
  
        private void Form1_MouseClick_1(object sender, MouseEventArgs e)
        {
            target.X = e.X;
            target.Y = e.Y;
            this.Invalidate(true);
        }

        private void Form1_KeyDown_1(object sender, KeyEventArgs e)
        {
            switch (e.KeyData)
            {
                case Keys.Up:
                    {
                        target.FontSize += 2;
                        break;
                    }
                case Keys.Down:
                    {
                        target.FontSize-= 2;
                        break;
                    }

            }
            this.Invalidate(true);
        }

        private void 종료XToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }
        //빨간색
        private void toolStripMenuItem3_Click(object sender, EventArgs e)
        {
            target.CurrentColor = Color.Red;
            this.Invalidate(true);
        }
        //녹색
        private void toolStripMenuItem4_Click(object sender, EventArgs e)
        {
            target.CurrentColor = Color.Green;
            this.Invalidate(true);
        }
        //파란색
        private void toolStripMenuItem5_Click(object sender, EventArgs e)
        {
            target.CurrentColor = Color.Blue;
            this.Invalidate(true);
        }
        //색상표
        private void toolStripMenuItem6_Click(object sender, EventArgs e)
        {
            ColorDialog cd = new ColorDialog();
            if (cd.ShowDialog() == DialogResult.OK)
            {
                target.CurrentColor = cd.Color;
                this.Invalidate(true);
            }
        }

        private void toolStripMenuItem8_Click(object sender, EventArgs e)
        {
            SettingOptionForm sof = new SettingOptionForm(this);
            if(sof.ShowDialog()==DialogResult.OK)
            {
                target.X = sof.x;
                target.Y = sof.y;
                target.CurrentColor = sof.currentColor;
                target.Str = sof.str;


            }
            this.Invalidate(true);
        }

        private void Form1_Paint_1(object sender, PaintEventArgs e)
        {
            DrawString();
            
        }

        public void Time(object obj)
        {

            while(true)
            {
                this.Text = System.DateTime.Now.ToString("yyyy/MM/dd hh:mm:ss");
            }
            
        }
       

        private void Form1_MouseMove(object sender, MouseEventArgs e)
        {
           // this.Text = System.DateTime.Now.ToString("yyyy/MM/dd hh:mm:ss");
        }
    }
}