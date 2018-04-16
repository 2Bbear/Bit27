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
    public partial class NewFileForm : Form
    {
        public NewFileForm()
        {
            InitializeComponent();
        }

        private string fileName;
        private int PageSize;

        public string FileName { get { return textBox1.Text; } set { fileName = value; } }

        public int PageSize1 { get => int.Parse(comboBox1.SelectedIndex.ToString()); set => PageSize = value; }

        private void NewFileForm_Load(object sender, EventArgs e)
        {
            //ComboBox Init 
            for(int i =0; i<51;i++)
            {
                comboBox1.Items.Add(i);
            }
            
        }
        //Button Click
        private void button1_Click(object sender, EventArgs e)
        {

            //Dialog Exit
            this.DialogResult = DialogResult.OK;
            Close();
        }
    }
}
