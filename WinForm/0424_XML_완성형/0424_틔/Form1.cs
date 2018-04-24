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

namespace _0424_틔
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            comboBox1.Text = "http://rss.joins.com/joins_news_list.xml";
        }

        //xmlwriteer
        private void button1_Click(object sender, EventArgs e)
        {
            wbXml.Writer("data.xml");
        }

        //xmlreadder
        private void button2_Click(object sender, EventArgs e)
        {
            StringBuilder br = wbXml.Reader("data.xml");
            textBox1.Text = br.ToString();
        }


        private void button4_Click(object sender, EventArgs e)
        {
            wbXml.Writer2("data2.xml");
        }

        private void button3_Click(object sender, EventArgs e)
        {
            StringBuilder br = wbXml.Reader2("data2.xml");
            textBox2.Text = br.ToString();
        }

        //rssreader
        private void button5_Click(object sender, EventArgs e)
        {
            string path = comboBox1.SelectedItem.ToString();
            textBox3.Text = wbXml.RssReader(path).ToString();
        }

        //노드형식알아내시
        private void button6_Click(object sender, EventArgs e)
        {
            string path = comboBox1.SelectedItem.ToString();
            List<NodeType> info = wbXml.LoadInfo(path);
            listBox1.Items.Clear();
            
            foreach(NodeType a in info)
            {
                listBox1.Items.Add(a);
            }
        }

        private void button7_Click(object sender, EventArgs e)
        {
            string path = comboBox1.SelectedItem.ToString();
            List<Item> info = wbXml.NodeElementParse(path);
            listBox2.Items.Clear();

            foreach (Item a in info)
            {
                listBox2.Items.Add(a);
            }
        }
    }
}
