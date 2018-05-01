using System;
using System.Collections.Generic;
using System.ComponentModel;
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

namespace GenericDataControl_0430
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private People people = new People();

        /// <summary>
        /// c#만의 새로운 문법, 생성자가 없는 클래스를 프로퍼티만으로 초기화 하는 문법
        /// </summary>
        private Person per = new Person();

        public MainWindow()
        {
            InitializeComponent();
            //per = people[0];


            UpdateNameToUI();
            UpdatePhoneToUI();
            UpdateAgeToUI();

            UpdateListBox();

            Validation.AddErrorHandler(shortNumber, shortNumver_ValidationError);
            Validation.AddErrorHandler(shortNumber2, shortNumver_ValidationError);
            Validation.AddErrorHandler(tab2_age, shortNumver_ValidationError);
            Validation.AddErrorHandler(tab2_name, name_ValidationError);
            //Validation.AddErrorHandler(shortNumber2, );
            //
            //panel.DataContext = per;
            //
            listbox.DataContext = people;
            listbox2.ItemsSource = people;

        }
        void shortNumver_ValidationError(object sender,ValidationErrorEventArgs e)
        {
            if (e.Action == ValidationErrorEventAction.Added)
            {
                MessageBox.Show((string)e.Error.ErrorContent, "유효성 검사 실패");
            }

            shortNumber.ToolTip = (string)e.Error.ErrorContent;
        }
        void name_ValidationError(object sender, ValidationErrorEventArgs e)
        {
            if (e.Action == ValidationErrorEventAction.Added) // 오류 중복 발생 해결 법
            {
                MessageBox.Show((string)e.Error.ErrorContent, "유효성 검사 실패");
                shortNumber.ToolTip = (string)e.Error.ErrorContent;
            }
        }


        //데이터 바인딩
        private void eraseButton_Click(object sender, RoutedEventArgs e)
        {
            //cs 바인딩의 데이터를 초기화 하는 방법
            //per.Name = "";
            //per.Phone = "";
            //per.Age = null;

            //xaml에 있는 객체를 초기화 하는 코드
            //per = (Person)FindResource("per1");
            //per.Name = "";
            //per.Phone = "";
            //per.Age = null;
            //per.Male = null;
            //per.ShortNumber = null;
            ICollectionView view =CollectionViewSource.GetDefaultView(FindResource("people"));
            Person person = (Person)view.CurrentItem;
            person.ShortNumber = null;
            person.Name = "";
            person.Phone = "";
            person.Male = null;

            
            listbox2.Items.Refresh();
            


        }



        #region 데이터 => 컨트롤
        //리스트 초기화
        private void UpdateListBox()
        {
            listbox.Items.Clear();

            foreach (Person per in people)
                listbox.Items.Add(per.ToString());
        }

        //ui 변경
        private void UpdateNameToUI()
        {
            if (per == null)
                return;


            name.Text = per.Name;
            nameLabel.Content = per.Name;
        }
        //ui 변경
        private void UpdatePhoneToUI()
        {
            if (per == null)
            {
                return;
            }

            phone.Text = per.Phone;
            phoneLabel.Content = per.Phone;
        }
        //ui 변경
        private void UpdateAgeToUI()
        {
            if (per == null)
            {

                return;
            }


            age.Text = per.Age.ToString();
            ageLabel.Content = per.Age.ToString();
        }
        //이름
        private void name_TextChanged(object sender, TextChangedEventArgs e)
        {
            //per.Name = name.Text;
            //nameLabel.Content = per.Name;


        }
        //전화
        private void phone_TextChanged(object sender, TextChangedEventArgs e)
        {
            //per.Phone = phone.Text;
            //phoneLabel.Content = per.Phone;
        }
        //나이
        private void age_TextChanged(object sender, TextChangedEventArgs e)
        {
            //per.Age = int.Parse(age.Text);
            //ageLabel.Content = per.Age.ToString();
            //Title = per.Age.ToString();

        }


        #endregion

        private void listbox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (listbox.SelectedIndex >= 0)
            {
                per = people[listbox.SelectedIndex];
                UpdateNameToUI();
                UpdatePhoneToUI();
                UpdateAgeToUI();
            }

        }
        //이전
        private void Button_Click(object sender, RoutedEventArgs e)
        {
            if (listbox.SelectedIndex > 0)
            {
                listbox.SelectedIndex--;
            }
            else
            {
                listbox.SelectedIndex = listbox.Items.Count - 1;
            }

        }
        //다음
        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            if (listbox.SelectedIndex < listbox.Items.Count - 1)
            {
                listbox.SelectedIndex++;
            }
            else
            {
                listbox.SelectedIndex = 0;
            }
        }
        //추가
        private void Button_Click_2(object sender, RoutedEventArgs e)
        {
            if (name.Text == "" || phone.Text == "")
                return;

            people.Add(new Person() { Name = name.Text, Phone = phone.Text, Age = int.Parse(age.Text) });
            // 리스트 박스의 아이템을 갱신한다.
            UpdateListBox();

        }
        //삭제
        private void Button_Click_3(object sender, RoutedEventArgs e)
        {
            if (listbox.SelectedIndex >= 0)
            {
                people.RemoveAt(listbox.SelectedIndex);

                // 컬렉션에 원소가 없다면 리슽의 현재 아이템이 없도록(per =null) 한다.
                if (people.Count == 0)
                    per = null;
                else
                    per = people[0];

                // 모든 UI 컨트롤을 갱신한다.
                UpdateNameToUI();
                UpdatePhoneToUI();
                UpdateListBox();
            }

        }
        //변경
        private void Button_Click_4(object sender, RoutedEventArgs e)
        {
            if (name.Text == "" || phone.Text == "")
                return;

            per.Name = name.Text;
            per.Phone = phone.Text;

            UpdateNameToUI();
            UpdatePhoneToUI();
            UpdateListBox();

        }

        private void prev_Click(object sender, RoutedEventArgs e)
        {
            ICollectionView view =CollectionViewSource.GetDefaultView(FindResource("people"));
            view.MoveCurrentToPrevious();
            if (view.IsCurrentBeforeFirst)
            {
                view.MoveCurrentToFirst();
            }

        }

        private void next_Click(object sender, RoutedEventArgs e)
        {
            ICollectionView view = CollectionViewSource.GetDefaultView(FindResource("people"));
            view.MoveCurrentToNext();
            if (view.IsCurrentAfterLast)
            {
                view.MoveCurrentToLast();
            }

        }
    }

    [ValueConversion(/* 원본 형식 */ typeof(bool), /* 대상 형식 */ typeof(bool))]
    public class MaleToFemaleConverter : IValueConverter
    {
        // 데이터 속성을 UI 속성으로 변경할 때
        public object Convert(object value, Type targetType, object parameter,System.Globalization.CultureInfo culture)
        {
            if (targetType != typeof(bool?))
                return null;

            bool? male = (bool?)value;

            if (male == null)
                return null;
            else
                return !(bool?)value;
        }
        // UI 속성을 데이터 속성으로 변경할 때
        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if (targetType != typeof(bool?))
                return null;

            bool? male = (bool?)value;

            if (male == null)
                return null;
            else
                return !(bool?)value;
        }


    }
    //bool 값 text로 변환하기
    [ValueConversion(/* 원본 형식 */ typeof(bool), /* 대상 형식 */ typeof(String))]
    public class MaleToStringConverter : IValueConverter
    {
        // 데이터 속성을 UI 속성으로 변경할 때
        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            //if (targetType != typeof(bool?))
            //    return null;

            bool? male = (bool?)value;

            if (male == null)
                return null;
            else if(male ==true)
            {
                return "남자";
            }
            else
            {
                return "여자";
            }
              
        }
        // UI 속성을 데이터 속성으로 변경할 때
        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            //if (targetType != typeof(bool?))
            //    return null;

            string male = (string)value;

            if (male == null)
                return null;
            else if(male.Equals("남자"))
            {
                return true;
            }
            else
            {
                return false;
            }
        }


    }
}
