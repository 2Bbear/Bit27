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
    public partial class EditModalessForm : Form
    {
        Form1 parent;
        public EditModalessForm(Form1 _parent)
        {
            InitializeComponent();
            parent = _parent;
            //컴포넌트 초기화
            //좌표
            textBox1.Text = parent.curType.pt.X.ToString();
            textBox2.Text = parent.curType.pt.Y.ToString();


            //타입
            comboBox1.Items.Add("사각형");
            comboBox1.Items.Add("타원");
            if (parent.curType.m_dt == DrawType.RECT)
            {
                comboBox1.SelectedIndex = 0;
            }
            else
            {
                comboBox1.SelectedIndex = 1;
            }
            //색상
            comboBox2.Items.Add("빨간색");
            comboBox2.Items.Add("녹  색");
            comboBox2.Items.Add("파란색");
            if (parent.curType.m_color == Color.Red)
            {
                comboBox2.SelectedIndex = 0;
            }
            else if (parent.curType.m_color == Color.Green)
            {
                comboBox2.SelectedIndex = 1;
            }
            else if (parent.curType.m_color == Color.Blue)
            {
                comboBox2.SelectedIndex = 2;
            }
            //크기
            comboBox3.Items.Add("25");
            comboBox3.Items.Add("50");
            if (parent.curType.m_ds == DrawSize.RECT25)
            {
                comboBox3.SelectedIndex = 0;
            }
            else if (parent.curType.m_ds == DrawSize.RECT50)
            {
                comboBox3.SelectedIndex = 1;
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            //좌표
            parent.curType.pt.X = int.Parse(textBox1.Text);
            parent.curType.pt.Y = int.Parse(textBox2.Text);

            //타입
            if (comboBox1.SelectedIndex == 0)
            {
                parent.curm_dt = DrawType.RECT;
                parent.curType.m_dt = DrawType.RECT;
            }
            else
            {
                parent.curm_dt = DrawType.ELLIPSE;
                parent.curType.m_dt = DrawType.ELLIPSE;
            }
            //색상
            if (comboBox2.SelectedIndex == 0)
            {
                parent.curColor = Color.Red;
                parent.curType.m_color= Color.Red;
            }
            else if (comboBox2.SelectedIndex == 1)
            {
                parent.curColor = Color.Green;
                parent.curType.m_color = Color.Green;
            }
            else if (comboBox2.SelectedIndex == 2)
            {
                parent.curColor = Color.Blue;
                parent.curType.m_color = Color.Blue;
            }
            //크기
            if (comboBox3.SelectedIndex == 0)
            {
                parent.curm_ds = DrawSize.RECT25;
                parent.curType.m_ds = DrawSize.RECT25;
            }
            else
            {
                parent.curm_ds = DrawSize.RECT50;
                parent.curType.m_ds = DrawSize.RECT50;

            }
            parent.Invalidate(true);

        }
    }
}
