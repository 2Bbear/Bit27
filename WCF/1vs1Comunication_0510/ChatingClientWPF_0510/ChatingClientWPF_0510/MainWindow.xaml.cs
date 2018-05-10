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
using System.IO;
using Microsoft.Win32;

namespace ChatingClientWPF_0510
{
    /// <summary>
    /// MainWindow.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class MainWindow : Window, IChatCallback
    {
        int idx;
        private IChat chat;

        public MainWindow()
        {
            InitializeComponent();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            //2 ===================================================
            InstanceContext site = new InstanceContext(this);
            chat = new ChatingClientWPF_0510.ServiceReference1.ChatClient(site);
        }

        #region IChatCallback 인터페이스 함수 생성
        public void Receive(int idx, string message)
        {
            string msgtemp = string.Format("{0}", message);
            chatlist.Items.Add(msgtemp);
        }


        public void UserEnter(int idx)
        {
            string msgtemp = string.Format("{0}님이 로그인하셨습니다.", idx);
            chatlist.Items.Add(msgtemp);
        }
        #endregion


        #region 로그인/로그아웃 핸들러
        private void btnJoin_Click(object sender, RoutedEventArgs e)
        {
            if ((string)btnJoin.Content == "로그인") this.Connect();
            else this.DisConnect();
        }

        private void Connect()
        {
            try
            {
                idx = int.Parse(seatbox.Text);

                //서버 접속
                if (chat.Join(idx))
                {
                    MessageBox.Show("접속 성공");
                }
                else
                    MessageBox.Show("접속 실패");



                btnJoin.Content = "로그아웃";
                string login = string.Format("{0}님이 로그인하셨습니다.", seatbox.Text);
            }
            catch (Exception ex)
            {
                MessageBox.Show("접속 오류 :{0}", ex.Message);
            }
        }

        private void DisConnect()
        {
            try
            {
                chat.Leave(idx);

                btnJoin.Content = "로그인";

                string logout = string.Format("{0}님이 로그아웃하셨습니다.", seatbox.Text);
                chatlist.Items.Add(logout);
            }
            catch (Exception ex)
            {
                MessageBox.Show("나가기 오류 :{0}", ex.Message);
            }
        }
        #endregion

        // 메시지 전송
        private void btnSend_Click(object sender, RoutedEventArgs e)
        {
            if (btnJoin.Content.Equals("로그아웃"))
            {
                string msg = msgbox.Text;

                string temp = string.Format("[{0}]", msg);

                chat.Say(idx, msg);

                msgbox.Clear();
            }
            else
                MessageBox.Show("로그인을 하시오");
        }



    }
}
