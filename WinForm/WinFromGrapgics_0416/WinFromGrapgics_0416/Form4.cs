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
    public partial class Form4 : Form
    {
        public Form4()
        {
            InitializeComponent();
        }

        private void Form4_MouseDown(object sender, MouseEventArgs e)
        {
            ////Client의 그래픽스 얻어오기
            //Graphics grfx = this.CreateGraphics();
            //grfx.DrawRectangle(new Pen(new SolidBrush(Color.Aqua)), e.X, e.Y, 50, 50);

            ////그래픽스 강제 해제
            //grfx.Dispose();


            //using은 자동적으로 dipose를 호출한다
            //Client의 그래픽스 얻어오기
            using (Graphics grfx = this.CreateGraphics())
            {
                grfx.DrawRectangle(new Pen(new SolidBrush(Color.Aqua)), e.X, e.Y, 50, 50);
            }
            //===================================================
           
            using (Graphics grfx2 = label1.CreateGraphics())
            {
                grfx2.FillRectangle(new SolidBrush(Color.Pink), label1.ClientRectangle);
            }


        }
    }
}
