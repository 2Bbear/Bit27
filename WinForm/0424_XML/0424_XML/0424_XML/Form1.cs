using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Xml;

namespace _0424_XML
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        //Writer
        private void button1_Click(object sender, EventArgs e)
        {
            wbXml.Writer("data.xml");
        }

        //Leader
        private void button2_Click(object sender, EventArgs e)
        {
            StringBuilder br = wbXml.Reader("data.xml");
            textBox1.Text = br.ToString();
        }

        //특성추가 Writer
        private void button3_Click(object sender, EventArgs e)
        {
            wbXml.WriterAttribute("data1.xml");
        }

        //특성추가 Reader
        private void button4_Click(object sender, EventArgs e)
        {
            StringBuilder br = wbXml.ReaderAttribute("data1.xml");
            textBox2.Text = br.ToString();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            string path = comboBox1.SelectedItem.ToString();
            textBox3.Text =  wbXml.RssReader(path).ToString();
        }

        //노드형식 알아내기
        private void button6_Click(object sender, EventArgs e)
        {
            string path = comboBox1.SelectedItem.ToString();
            wbXml.NodeInfo(path);

            List<NodeTypeInfo> info = wbXml.NodeInfo(path);
            listBox1.Items.Clear();

            foreach(NodeTypeInfo temp in info)
            {
                listBox1.Items.Add(temp);
            }
        }

        //요소 읽기
        private void button7_Click(object sender, EventArgs e)
        {
            string path = comboBox1.SelectedItem.ToString();

            List<Item> info = wbXml.NodeElementParse(path);
            listBox2.Items.Clear();

            foreach (Item temp in info)
            {
                listBox2.Items.Add(temp);
            }
        }
    }
}
