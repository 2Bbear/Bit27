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
    public partial class Form3 : Form
    {
        private TextBox textBox1;
        private Button button2;
        private Button button1;
    
        public Form3()
        {
            InitializeComponent();
        }

        private void InitializeComponent()
        {
            this.button1 = new System.Windows.Forms.Button();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.button2 = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(29, 26);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(241, 23);
            this.button1.TabIndex = 0;
            this.button1.Text = "XML문서만들기";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(29, 56);
            this.textBox1.Multiline = true;
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(241, 185);
            this.textBox1.TabIndex = 1;
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(290, 26);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(75, 23);
            this.button2.TabIndex = 2;
            this.button2.Text = "전체삭제";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // Form3
            // 
            this.ClientSize = new System.Drawing.Size(785, 271);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.button1);
            this.Name = "Form3";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        //문서만들기
        private void button1_Click(object sender, EventArgs e)
        {
            XmlDocument doc = new XmlDocument(); 
            XmlDeclaration xmldecl; 
            xmldecl = doc.CreateXmlDeclaration("1.0", null, null); 
            doc.InsertBefore(xmldecl, doc.DocumentElement); 
            XmlComment comment; 
            comment = doc.CreateComment("XML 노드 삽입 "); 
            doc.AppendChild(comment); 
            XmlElement root = doc.CreateElement("books"); 
            doc.AppendChild(root); 
            //===========================================
            XmlElement elem = doc.CreateElement("book"); 
            elem.InnerText = "XML.NET"; 
            doc.DocumentElement.AppendChild(elem); 
            elem.SetAttribute("price", "12000"); 
            XmlAttribute attr = doc.CreateAttribute("count"); 
            attr.Value = "50"; 
            elem.Attributes.Append(attr); 
            //===============================
            XmlWriterSettings xws = new XmlWriterSettings();
            xws.Indent = true;
            //XmlWriter writer = new XmlWriter("dom.xml", xws);
            doc.Save("data.xml"); 
        }

        private void button2_Click(object sender, EventArgs e)
        {

        } 
    }
}
