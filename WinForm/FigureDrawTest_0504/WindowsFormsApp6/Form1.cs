using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp6
{
    public partial class Form1 : Form
    {
        List<Ddata> typelist = new List<Ddata>();

        //현재 정보
        public Ddata curType;//현재 도형의 정보가 담긴
        //추가 현재 정보 
        public Color curColor = Color.Red;
        public DrawSize curm_ds= DrawSize.RECT25;
        public DrawType curm_dt= DrawType.RECT;

        //
        public Form1()
        {
            InitializeComponent();
        }
        public void PrintTitleBar()
        {
            this.Text = "도형의 개수 : "+typelist.Count.ToString()+"개";
        }
        public void PrintAllFigure()
        {

            foreach (Ddata t in typelist)
            {
                if(t.m_dt==DrawType.RECT)
                {
                    //Rectangle rect = new Rectangle(t.pt.X,t.pt.Y,50, 50);
                    //formGraphics.DrawRectangle(new Pen(new SolidBrush(t.m_color)), rect);
                    System.Drawing.SolidBrush myBrush = new System.Drawing.SolidBrush(t.m_color);
                    System.Drawing.Graphics formGraphics;
                    formGraphics = this.CreateGraphics();
                    formGraphics.FillRectangle(myBrush, new Rectangle(t.pt.X, t.pt.Y, (int)t.m_ds, (int)t.m_ds));
                    myBrush.Dispose();
                    formGraphics.Dispose();

                }
                else if(t.m_dt == DrawType.ELLIPSE)
                {
                    System.Drawing.SolidBrush myBrush = new System.Drawing.SolidBrush(t.m_color);
                    System.Drawing.Graphics formGraphics;
                    formGraphics = this.CreateGraphics();
                    formGraphics.FillEllipse(myBrush, new Rectangle(t.pt.X, t.pt.Y, (int)t.m_ds, (int)t.m_ds));
                    myBrush.Dispose();
                    formGraphics.Dispose();
                }
            }
           
        }


        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            PrintAllFigure();
        }

        private void 빨간색RToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curColor = Color.Red;
        }

        private void 녹색GToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curColor = Color.Green;
        }

        private void 파란색BToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curColor = Color.Blue;
        }

        private void Form1_MouseClick(object sender, MouseEventArgs e)
        {
            

        }

        private void Form1_MouseUp(object sender, MouseEventArgs e)
        {
           // MessageBox.Show("그림");
            curType = new Ddata();

            curType.pt.X = e.X;
            curType.pt.Y = e.Y;
            curType.m_color = curColor;
            curType.m_dt = curm_dt;
            curType.m_ds = curm_ds;
            typelist.Add(curType);

            PrintTitleBar();
            this.Invalidate(true);

        }

        private void 색상다이얼로그ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ColorDialog cd = new ColorDialog();
            if (cd.ShowDialog() == DialogResult.OK)
            {
                curColor = cd.Color;
                this.Invalidate(true);
            }
        }

        private void 사각형ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //curType = new Ddata();
            curm_ds = DrawSize.RECT25;
        }

        private void 타원ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //curType = new Ddata();
            curm_ds = DrawSize.RECT50;
        }

        private void 모달MToolStripMenuItem_Click(object sender, EventArgs e)
        {
            EditForm modal = new EditForm(this);
            

           if (modal.ShowDialog()==DialogResult.OK)
            {

            }


        }

        private void 종료XToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void 모달리스ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            EditModalessForm emodal = new EditModalessForm(this);

            emodal.Show();
        }
    }
}
