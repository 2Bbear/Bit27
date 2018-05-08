using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using WindowsFormsApp7;
using WindowsFormsApp7.WebReference;

namespace WindowsFormsApp7
{
    public partial class Form1 : Form
    {

        Image picImage;


        Picture pic = new Picture();
        
        public Form1()
        {
            InitializeComponent();
            
            
        }

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
           
            picImage = Image.FromStream(new MemoryStream(pic.GetPicture(listBox1.SelectedItem.ToString())));
           
            pictureBox1.Image = picImage;
            Invalidate();   // 화면을 갱신한다.

        }

        private void 그림목록보기ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            foreach (string t in pic.GetPictureList())
            {
                listBox1.Items.Add(t);
            }
        }

        private void 그림업로드하기ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            // 읽어오는 스트림클래스를 선언
            Stream readStream;

            // 파일열기	대화상자를 생성
            OpenFileDialog dlg = new OpenFileDialog();

            // 확장자를 제한한다.
            //dlg.Filter = "그림파일 (.bmp;.jpg;.gif;.jpeg;.png;.tiff)|.bmp;.jpg;.gif;.jpeg;.png;.tiff)";
            dlg.RestoreDirectory = true;    // 현재 디렉토리를 저장해놓는다.

            // OK 버튼을 누르면
            if (dlg.ShowDialog() == DialogResult.OK)
            {
                if ((readStream = dlg.OpenFile()) != null)
                {
                    byte[] bytePic;
                    BinaryReader picReader = new BinaryReader(readStream);
                    bytePic = picReader.ReadBytes(Convert.ToInt32(readStream.Length));
                    FileInfo fi = new FileInfo(dlg.FileName);

                    // 업로드 서비스 요청
                    if (pic.UploadPicture(fi.Name, bytePic))
                    {
                        MessageBox.Show("업로드 성공");
                    }
                    else
                    {
                        MessageBox.Show("업로드 실패");
                    }
                    readStream.Close();
                }
            }
        }
    }
}
