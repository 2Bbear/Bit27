using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace GoogleMapOpenAPI_0425
{
    public partial class Form1 : Form
    {
        Thread t;
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                t = new Thread(Search_Map);
                t.Start();

            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
            finally
            {
            }
            
        }
        private void Search_Map(object obj)
        {
            this.Invoke(new MethodInvoker(delegate () {
                //MessageBox.Show(APIExamTranslate.SearchKeyWordMap(textBox1.Text));
                String temp = (APIExamTranslate.SearchKeyWordMap(textBox1.Text));
                textBox2.Text = temp;

                Parser.SaveXml("data.xml", temp);
                Parser.LoadXml("data.xml");
                Parser.MakeItemList2();
                

                webBrowser1.Refresh(WebBrowserRefreshOption.Completely);
                webBrowser1.Url =new Uri("file:///C:/Users/User/Desktop/NaverMapOpenAPI.html/?X="+
                    Item.itemlist[0].x + "&Y=" + Item.itemlist[0].y+ "&X1="+ Item.itemlist[1].x + "&Y1="+ Item.itemlist[1].y + "&X2="+ Item.itemlist[2].x + "&Y2="+ Item.itemlist[2].y
                    + "&X3=" + Item.itemlist[3].x + "&Y3=" + Item.itemlist[3].y
                    + "&X4=" + Item.itemlist[4].x + "&Y4=" + Item.itemlist[4].y
                    + "&X5=" + Item.itemlist[5].x + "&Y5=" + Item.itemlist[5].y
                    + "&X6=" + Item.itemlist[6].x + "&Y6=" + Item.itemlist[6].y
                    + "&X7=" + Item.itemlist[7].x + "&Y7=" + Item.itemlist[7].y
                    + "&X8=" + Item.itemlist[8].x + "&Y8=" + Item.itemlist[8].y
                    + "&X9=" + Item.itemlist[9].x + "&Y9=" + Item.itemlist[9].y);


                
               

                //MessageBox.Show(APIExamTranslate.Start(textBox1.Text));
                //textBox2.Text = (APIExamTranslate.Start(textBox1.Text));
            }));
            
        }
    }
}
