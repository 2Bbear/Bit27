using System;
using System.Collections.Generic;
using System.Linq;
using System.ServiceModel;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using ChatingClientWPF_0510.ServiceReference1;
using ChatingClientWPF_0510.ServiceReference2;
using System.IO;
using Microsoft.Win32;

namespace ChatingClientWPF_0510
{
    // MainWindow.xaml에 대한 상호 작용 논리
    public partial class MainWindow : Window, IFileCallback
    {
        string name;
        int idx;

        OpenFileDialog fileDlg;
        TextBox[] textbox;

        //서버와 연결개체
        public IFile file;

        public MainWindow()
        {
            InitializeComponent();
            textbox = new TextBox[] { textbox01, textbox02 , textbox03 , textbox04 , textbox05, textbox06, textbox07, textbox08, textbox09, textbox10,
                textbox11, textbox12 , textbox13 , textbox14 , textbox15, textbox16, textbox17, textbox18, textbox19, textbox20,textbox21,textbox22
            };
        }
        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            InstanceContext site = new InstanceContext(this);
            file = new ChatingClientWPF_0510.ServiceReference2.FileClient(site);
        }
        //파일 콜백
        public void FileRecive(string name, int idx, string filename, byte[] filedata)
        {
            try
            {
                //파일 IO
                string path = @"C:\MyDown\" + filename;
                FileStream fs = new FileStream(path, FileMode.Create, FileAccess.Write);
                fs.Write(filedata, 0, filedata.Length);
                fs.Close();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
            finally
            {
            }
        }

        public void UserEnter(string name, int idx)
        {
            textbox[idx - 1].Text = name;
            textbox[idx - 1].Foreground = Brushes.White;
            textbox[idx - 1].Background = Brushes.DeepPink;
        }

        public void UserLeave(string name, int idx)
        {
            textbox[idx - 1].Text = "";
            textbox[idx - 1].Foreground = Brushes.White;
            textbox[idx - 1].Background = Brushes.White;
        }
        //=======================================================================================
        private void btnJoin_Click(object sender, RoutedEventArgs e)
        {
            if((string)btnJoin.Content=="로그인")
            {
                this.Connect();
            }
            else
            {
                this.DisConnect();
            }
        }
        private void Connect()
        {
            try
            {
                //ui처리
                string temp = string.Format("이름 : {0}\r\n 좌석 : {1}\r\n맞습니까?",namebox.Text,seatbox.Text);
                MessageBox.Show(temp,"확인",MessageBoxButton.OKCancel);

                name = namebox.Text;
                idx = int.Parse(seatbox.Text);

                //서버접속
                StudentData[] data = file.Join(name, idx);
                if(data==null)
                {
                    MessageBox.Show("로그인에러");
                    return;
                }

                //받아온 상대들의 화면 갱신
                foreach(StudentData d in data)
                {
                    textbox[d.SeatNum - 1].Text = d.Name;
                    textbox[d.SeatNum - 1].Foreground=Brushes.White;
                    textbox[d.SeatNum - 1].Background = Brushes.DeepPink;
                }

                btnJoin.Content = "로그아웃";

            }
            catch (Exception ex)
            {
                MessageBox.Show("접속 오류 : "+ex.Message);
            }
            finally
            {
            }
        }
        
        private void DisConnect()
        {
            try
            {
                file.Leave(name, idx);
                btnJoin.Content = "로그인";
                for(int i=0;i<19 ;i++)
                {
                    textbox[i].Clear();
                    textbox[i].Background = Brushes.White;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("나가기 오류 : " + ex.Message);
            }
            finally
            {
            }
        }

        private void Label_MouseDown(object sender, MouseButtonEventArgs e)
        {
            seatbox.Text = (string)((Label)sender).Content;
        }

        private void namebox_GotFocus(object sender, RoutedEventArgs e)
        {
            ((TextBox)sender).Clear();
        }
           
        private void btnOpen_Click(object sender, RoutedEventArgs e)
        {
            fileDlg = new OpenFileDialog();
            if(fileDlg.ShowDialog()==true)
            {
                txtUpLoad1.Text = fileDlg.FileName;
            }
        }

        private void btnUpload_Click(object sender, RoutedEventArgs e)
        {
            //파일 전송
            //해당 이미지 파일을 스트림 형식으로 오픈한다.
            FileStream dataFileStream = new FileStream(txtUpLoad1.Text, FileMode.Open, FileAccess.Read, FileShare.Read);

            //이미지 파일 스트림을 읽을 객체를 하나 만든다.
            BinaryReader dataReader = new BinaryReader(dataFileStream);
            //파일 바이트 배열에 넣는다.
            byte[] byteFile = { 0 };
            byteFile = dataReader.ReadBytes(Convert.ToInt32(dataFileStream.Length));
            //파일스트림을 닫는다.
            dataFileStream.Close();

            string filename = fileDlg.SafeFileName;
            file.UpLoadFile(name, idx, filename, byteFile);
            txtUpLoad1.Clear();
        }

        private void btnAllSend_Click(object sender, RoutedEventArgs e)
        {
            //파일 전송
            //해당 이미지 파일을 스트림 형식으로 오픈한다.
            FileStream dataFileStream = new FileStream(txtUpLoad1.Text, FileMode.Open, FileAccess.Read, FileShare.Read);

            //이미지 파일 스트림을 읽을 객체를 하나 만든다.
            BinaryReader dataReader = new BinaryReader(dataFileStream);
            //파일 바이트 배열에 넣는다.
            byte[] byteFile = { 0 };
            byteFile = dataReader.ReadBytes(Convert.ToInt32(dataFileStream.Length));
            //파일스트림을 닫는다.
            dataFileStream.Close();

            string filename = fileDlg.SafeFileName;
            file.UpLoadFile(name, idx, filename, byteFile);
            txtUpLoad1.Clear();

            MessageBox.Show(filename + "파일이 업로드 되었습니다.");
        }

      
    }

}
