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
    public partial class Form3 : Form
    {
        private  Color selectcolor = Color.Aqua;

        public Form3()
        {
            InitializeComponent();
        }

        protected override void OnPrint(PaintEventArgs e)
        {
            Graphics grfx = this.CreateGraphics();

            //사각형 칠하기 ? 이거 왜 안칠해
            grfx.FillRectangle(new SolidBrush(selectcolor), this.ClientRectangle);

        }

        private void button1_Click(object sender, EventArgs e)
        {
            //색상 다이얼로그 띄우기
            ColorDialog cdlg = new ColorDialog();
            if (cdlg.ShowDialog() == DialogResult.OK)
            {
                selectcolor = cdlg.Color;
               
                this.Invalidate(true);
            }

        }
    }
}
