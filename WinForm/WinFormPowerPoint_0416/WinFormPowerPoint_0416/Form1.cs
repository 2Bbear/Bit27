using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using PowoerPoint_0413;

namespace WinFormPowerPoint_0416
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            textBox1.Invalidate();
        }

        string msg = "";

        private void 프로그램종료ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void 파일열기ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FileOpenForm fof = new FileOpenForm();
            if(fof.ShowDialog()==DialogResult.OK)
            {
                PowoerPoint_0413.Control con = PowoerPoint_0413.Control.SingleTone;
                if(con.OpenFile(fof.FileName))
                {
                    this.Text = fof.FileName;

                    msg="파일을 선택했습니다.";
                }
                else
                {
                    msg="파일을 선택하지 못했습니다.";
                }

               
                this.Invalidate();
            }
            
        }

        private void 다른이름으로저장ToolStripMenuItem_Click(object sender, EventArgs e)
        {

            //Data 패키징
            PowoerPoint_0413.Control con = PowoerPoint_0413.Control.SingleTone;

            //저장
            FileIOControl.SavePPT(con.Ppt);
            this.Invalidate();
        }

        private void 새파일ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            NewFileForm nff = new NewFileForm();
            if(nff.ShowDialog()==DialogResult.OK)
            {
                //Get Value on Edit
                PowoerPoint_0413.Control con = PowoerPoint_0413.Control.SingleTone;
                
                if (con.Createppt(nff.FileName, nff.PageSize1))
                {
                    listBox1.Items.Add(nff.FileName);
                    msg = "파일을 생성했습니다.";
                }
                else
                {
                    msg = "파일 생성에 실패했습니다.";
                }
                this.Invalidate();
            }
        }
        //
        private void 편집ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            EditPPTForm epptf = new EditPPTForm();
            if(epptf.ShowDialog()==DialogResult.OK)
            {
                
                PowoerPoint_0413.Control con = PowoerPoint_0413.Control.SingleTone;
                con.Editppt(con.Ppt.CurPage, epptf.str);
            }
            else
            {

            }
            this.Invalidate();
        }

        private void 페이지이동ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            PowoerPoint_0413.Control con = PowoerPoint_0413.Control.SingleTone;
            con.NextPage();
            this.Invalidate();
        }

        private void 프레젠테이션실행ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            PowoerPoint_0413.Control con = PowoerPoint_0413.Control.SingleTone;
            con.Runppt();
            this.Invalidate();
        }

        private void 프레젠테이션종료ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Invalidate();
        }

        protected override void OnPrint(PaintEventArgs e)
        {
           


        }
        protected override void OnPaint(PaintEventArgs e)
        {
            PowoerPoint_0413.Control con = PowoerPoint_0413.Control.SingleTone;
            msg = con.PrintPPT();

            textBox1.Text = msg;
        }

        private void 이전페이지ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            PowoerPoint_0413.Control con = PowoerPoint_0413.Control.SingleTone;
            con.PrevPage();
            this.Invalidate();
        }
    }
}
