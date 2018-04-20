using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WinForm_0420
{
    
    public partial class Form1 : Form
    {
        private DataTable member = new DataTable("member");

        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            UserBulidTable.DesingTable(member);
            string t_name;
            int c_count;
            List<String> list =UserBulidTable.ViewAll(member, out t_name, out c_count);

            foreach(string temp in list)
            {
                listBox1.Items.Add(temp);
            }

            //UserBulidTable.AddTableColum2(member);
            dataGridView1.DataSource = member;

        }
        private bool nullcheck=false;
        private bool pribarykeycheck = false;
        private bool autoincreamentcheck = false;

        private void button2_Click(object sender, EventArgs e)
        {
            
            
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            if(nullcheck==true)
            {
                nullcheck = false;
            }
            else
            {
                nullcheck = true;
            }

            
        }

        private void checkBox2_CheckedChanged(object sender, EventArgs e)
        {
            if (pribarykeycheck == true)
            {
                pribarykeycheck = false;
            }
            else
            {
                pribarykeycheck = true;
            }
        }

        private void checkBox3_CheckedChanged(object sender, EventArgs e)
        {
            if (autoincreamentcheck == true)
            {
                autoincreamentcheck = false;
            }
            else
            {
                autoincreamentcheck = true;
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            //UserBulidTable.AddTableColum2(member,"응",1,2,3,4,5);
            //dataGridView1.DataSource = member;
            try
            {
                String tableName = textBox1.Text;
                String columName = textBox2.Text;
                String columType = comboBox1.Text;



                UserBulidTable.AddTableColum(member, tableName, columName, columType,
                    nullcheck, pribarykeycheck, autoincreamentcheck);

                string t_name;
                int c_count;

                List<String> list = UserBulidTable.ViewAll(member, out t_name, out c_count);

                foreach (string temp in list)
                {
                    listBox2.Items.Add(temp);
                }


            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
            finally
            {
            }
        }
        //xml write
        private void button4_Click(object sender, EventArgs e)
        {
            member.WriteXml("member.xml");
        }
        //xml read
        private void button5_Click(object sender, EventArgs e)
        {
            member.ReadXml("member.xml");
        }
    }
}
