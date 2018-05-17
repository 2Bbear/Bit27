using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
//추가
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Microsoft.Speech.Recognition;
using System.ComponentModel;


namespace Team5project
{
    /// <summary>
    /// MainWindow.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class MainWindow : Window
    {
        //아이콘 객체
        public System.Windows.Forms.NotifyIcon notify;
        public void Init()
        {
            Register.AutoRegist();
            try
            {
                SetIcon();
                //this.Hide();
                // msdn예시 buttonMenu.Show(Button1, new System.Drawing.Point(20, 20));
                //menu.Show(Cursor, new System.Drawing.Point(20, 20));
            }
            catch (Exception ee)
            {
            }
        }
        private void Listen()
        {
            Listener listener = new Listener(this);
            listener.initRS();
            listener.initTTS();

        }
        private void End()
        {

        }

        public MainWindow()
        {
            InitializeComponent();
            Init();
            Listen();
 
        }


        //아이콘설정
        private void SetIcon()
        {
            ////아이콘 생성
            //System.Windows.Forms.NotifyIcon notify;
            //Context메뉴 생성
            System.Windows.Forms.ContextMenu menu = new System.Windows.Forms.ContextMenu();

            #region 아이콘 구성
            notify = new System.Windows.Forms.NotifyIcon();
            notify.Icon = new System.Drawing.Icon("Mic.ico");
            notify.Visible = true;
            notify.DoubleClick +=
                delegate(object senders, EventArgs args)
                {
                    this.Show();
                    this.WindowState = WindowState.Normal;
                };
            notify.ContextMenu = menu;
            notify.Text = "Test";
            #endregion

            #region Context메뉴 구성
            System.Windows.Forms.MenuItem item1 = new System.Windows.Forms.MenuItem();
            System.Windows.Forms.MenuItem item2 = new System.Windows.Forms.MenuItem();
            System.Windows.Forms.MenuItem item3 = new System.Windows.Forms.MenuItem();
            System.Windows.Forms.MenuItem item4 = new System.Windows.Forms.MenuItem();
            System.Windows.Forms.MenuItem item5 = new System.Windows.Forms.MenuItem();
            System.Windows.Forms.MenuItem item6 = new System.Windows.Forms.MenuItem();

            menu.MenuItems.Add(item1);
            menu.MenuItems.Add(item2);
            menu.MenuItems.Add(item3);
            menu.MenuItems.Add(item4);
            menu.MenuItems.Add(item5);
            menu.MenuItems.Add(item6);


            item1.Index = 0;
            item1.Text = "프로그램 종료";
            item1.Click += delegate(object click, EventArgs eClick)
            {
                Application.Current.Shutdown();
                notify.Dispose();
            };
            item2.Index = 0;
            item2.Text = "레지스트리 삭제";
            item2.Click += delegate(object click, EventArgs eClick)
            {

                this.Close();       //나중에 다른셋팅으로 변경
            };
            item3.Index = 0;
            item3.Text = "레지스트리 등록";
            item3.Click += delegate(object click, EventArgs eClick)
            {

                this.Close();       //나중에 다른셋팅으로 변경
            };
            item4.Index = 0;
            item4.Text = "볼륨 다운";
            item4.Click += delegate(object click, EventArgs eClick)
            {

                this.Close();       //나중에 다른셋팅으로 변경
            };
            item5.Index = 0;
            item5.Text = "볼륨 업";
            item5.Click += delegate(object click, EventArgs eClick)
            {

                this.Close();       //나중에 다른셋팅으로 변경
            };
            item6.Index = 0;
            item6.Text = "도움말";
            item6.Click += delegate(object click, EventArgs eClick)
            {

                this.Close();       //나중에 다른셋팅으로 변경
            };
            #endregion

        }

       
        //최소화 => 트레이로
        protected override void OnStateChanged(EventArgs e)
        {
            if (WindowState.Minimized.Equals(WindowState))
            {
                this.Hide();
            }
            base.OnStateChanged(e);
        }
        //닫기버튼 => 트레이로
        protected override void OnClosing(CancelEventArgs e)
        {
            base.OnClosed(e);

            this.Hide();
            e.Cancel = true;
        }
    
    }
}
