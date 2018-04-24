using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _0424_XML
{
    public partial class Form2 : Form
    {
        List<Item> info = null;

        public Form2()
        {
            InitializeComponent();
        }

        //읽기
        private void button5_Click(object sender, EventArgs e)
        {
            string path = comboBox1.SelectedItem.ToString();
            textBox3.Text = wbXml.RssReader(path).ToString();
        }

        //요소 읽기
        private void button7_Click(object sender, EventArgs e)
        {
            string path = comboBox1.SelectedItem.ToString();
            info = wbXml.NodeElementParse(path);

            if (info == null)
            {
                MessageBox.Show("파서 먼저 실행");
                return;
            }

            listBox2.Items.Clear();

            foreach (Item temp in info)
            {
                listBox2.Items.Add(temp);
            }
        }

        private void listBox2_SelectedIndexChanged(object sender, EventArgs e)
        {
            
            Item item = info[listBox2.SelectedIndex];
            label3.Text = item.Title;
            label4.Text = item.link;
            if(item.link.IndexOf("html")!=-1)
            {
                Bitmap bitmap = WebImageView(item.link);
                pictureBox1.Image = bitmap;
            }
            
           

        }
        public Bitmap WebImageView(string URL)
        {
            try
            {
                WebClient Downloader = new WebClient();
                Stream ImageStream = Downloader.OpenRead(URL);
                Bitmap DownloadImage = Bitmap.FromStream(ImageStream) as Bitmap;
                return DownloadImage;
            }
            catch (Exception)
            {
                return null;
            }
        }

    }
}
