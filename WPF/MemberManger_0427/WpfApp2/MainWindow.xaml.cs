using System;
using System.Collections.Generic;
using System.Linq;
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

namespace WpfApp2
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        double tab1superWindowWidth;
        private Color d = new Color();
        Member currentuserInfo;
        bool gender=true;

        List<Member> member = new List<Member>();

        public MainWindow()
        {
            InitializeComponent();
            tab1superWindowWidth = SuperWindow.Width;
            d.ScA = 1.0f;
        }
        //R Slider
        private void Slider_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            d.ScR =(float)e.NewValue;
            Palet.Fill = new SolidColorBrush(d);
        }
        //G Slider
        private void Slider_ValueChanged_1(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            d.ScG = (float)e.NewValue;
            Palet.Fill = new SolidColorBrush(d);
        }
        //B Slider
        private void Slider_ValueChanged_2(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            d.ScB = (float)e.NewValue;
            Palet.Fill = new SolidColorBrush(d);
        }
        //Button Click
        private void Button_Click(object sender, RoutedEventArgs e)
        {
            currentuserInfo = new Member(Member.Ehooby.Default, Colors.AliceBlue, null, null, null, null, true);
            //name
            currentuserInfo.Name = UserName.Text;
            //phone
            currentuserInfo.Phonenum = UserPhoneNum.Text;
            //id
            currentuserInfo.Id = UserID.Text;
            //pw
            currentuserInfo.Password = UserPassWord.Text;
            //    //hobby
            if (UserHobbyReadBook.IsChecked==true)
            {
                currentuserInfo.Myhoby = currentuserInfo.Myhoby | Member.Ehooby.ReadBook;
            }
            if (UserHobbyWatchingMovie.IsChecked == true)
            {
                currentuserInfo.Myhoby = currentuserInfo.Myhoby | Member.Ehooby.WatchingMovie;
            }
            if (UserHobbyTour.IsChecked == true)
            {
                currentuserInfo.Myhoby = currentuserInfo.Myhoby | Member.Ehooby.Tour;
            }
            //color
            currentuserInfo.Mycolor = d;
            //gender
            currentuserInfo.Gender = gender;

            member.Add(currentuserInfo);
            //foreach(Member t in member)
            //{
            //    MessageBox.Show(t.Name);
            //}
            //listview.Items.Clear();
            listview.ItemsSource = member;
            listview.Items.Refresh();

            MessageBox.Show("저장 성공");
        }
        //Radio Button 남성
        private void RadioButton_Checked(object sender, RoutedEventArgs e)
        {
            gender = true;
           //MessageBox.Show(gender.ToString());
        }
        //Radio Button 여성
        private void RadioButton_Checked_1(object sender, RoutedEventArgs e)
        {
           
            gender = false;
           // MessageBox.Show(gender.ToString());
        }

        private void TabItem_MouseUp(object sender, MouseButtonEventArgs e)
        {
            SuperWindow.Width = listview.Width+40;
        }

        private void TabItem_MouseUp_1(object sender, MouseButtonEventArgs e)
        {
            SuperWindow.Width = tab1superWindowWidth;
           // listview.ItemsSource = null;
            
        }

        private void TabItem_MouseUp_2(object sender, MouseButtonEventArgs e)
        {
            SuperWindow.Width=Content3.Width;
            int idx;
            try
            {
                idx = listview.SelectedIndex;
            }
            catch (Exception ex)
            {
                idx = 0;
            }
            finally
            {
            }

            try
            {
                //name
                Content3Name.Text = member[idx].Name;
                //phone
                Content3Phone.Text = member[idx].Phonenum;
                //id
                Content3ID.Text = member[idx].Id;
                //pw
                Content3PW.Text = member[idx].Password;
                //gender
                Content3Gender.Text = member[idx].Gender.ToString();
                //hobby
                Content3Hobby.Text = member[idx].Myhoby.ToString();
                //color
                Content3Color.Text = member[idx].Mycolor.ToString();
            }
            catch (Exception ex)
            {
                //name

                Content3Name.Text = "none";
                //phone
                Content3Phone.Text = "none";
                //id
                Content3ID.Text = "none";
                //pw
                Content3PW.Text = "none";
                //gender
                Content3Gender.Text = "none";
                //hobby
                Content3Hobby.Text = "none";
                //color
                Content3Color.Text = "none";
            }
            finally
            {
            }
            


        }
    }
}
