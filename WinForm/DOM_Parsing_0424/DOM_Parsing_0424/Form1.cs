using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DOM_Parsing_0424
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            InitDialog();
        }
        private void PrintXmlFileData(String str)
        {
            textBox1.Text = str;
        }
        //Dialog초기화
        private void InitDialog()
        {
            comboBox2.SelectedIndex = 0;
        }
        //XML 불러오기
        private void button1_Click(object sender, EventArgs e)
        {
            try
            {

                MyDOMParser.LoadXmlDocument( comboBox2.SelectedItem.ToString());
                PrintXmlFileData(MyDOMParser.PrintCurrentXmlDocument());
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
            finally
            {
            }


        }
        //XML 생성하기
        private void button2_Click(object sender, EventArgs e)
        {
            try
            {
                MyDOMParser.MakeXmlDocument(comboBox2.SelectedItem.ToString());
                

            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
            finally
            {
            }
        }
        //XML 파일 삭제하기
        private void button7_Click(object sender, EventArgs e)
        {
            try
            {
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
            finally
            {
            }
        }
        //XML Node 추가하기
        private void button3_Click(object sender, EventArgs e)
        {
            try
            {
                MyDOMParser.AddNode(comboBox2.SelectedItem.ToString(), textBox3.Text,textBox5.Text);
                
                PrintXmlFileData(MyDOMParser.PrintCurrentXmlDocument());
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
            finally
            {
            }
        }
        //xML Node  삭제하기
        private void button5_Click(object sender, EventArgs e)
        {
            try
            {
                MyDOMParser.DeleteNode(comboBox2.SelectedItem.ToString(), textBox3.Text);
               
                PrintXmlFileData(MyDOMParser.PrintCurrentXmlDocument());
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
            finally
            {
            }
        }
        //특성값 변경하기
        private void button4_Click(object sender, EventArgs e)
        {
            try
            {
                
                MyDOMParser.ChangeNodeAttribute(comboBox2.SelectedItem.ToString(), textBox4.Text, textBox2.Text);

                PrintXmlFileData(MyDOMParser.PrintCurrentXmlDocument());
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
            finally
            {
            }
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
