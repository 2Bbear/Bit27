using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WMP_RemoteControl
{
    public partial class Form1 : Form
    {
        




        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
        }
      

        private void AddAllProcessName(ListBox output)
        {
            output.Items.Clear();
            foreach (Process t in Process.GetProcesses())
            {
                output.Items.Add(t.ProcessName);
            }
        }
        #region Controll
        private void button1_Click(object sender, EventArgs e)
        {
            NotePadProcess test = new NotePadProcess();
            //StartProgram("Windows Media Player");
            Process t=test.StartProgram("what is love");
            textBox1.Text = t.ProcessName;
        }
        #endregion


    }
}
