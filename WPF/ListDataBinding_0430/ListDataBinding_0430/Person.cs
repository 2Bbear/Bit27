using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Data;

namespace ListDataBinding_0430
{
    public class Person : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;

        private String name;
        private int age;
        private String address;
        private bool? gender;

        public Person(string name, int age, string address, bool gender)
        {
            Name = name;
            Age = age;
            Address = address;
            Gender = gender;
        }

        public string Name
        {
            get
            {
                return name;
            }
            set
            {
                name = value;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("Name"));
            }
        }
        public int Age {
            get => age;
            set
            {
                age = value;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("Age"));
            }
        }
        public string Address {
            get => address;
            set
            {
                address = value;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("Address"));
            }
        }
        public bool? Gender {
            get => gender;
            set
            {
                gender = value;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("Gender"));
            }
        }
    }

    //성별 To String변환기
    [ValueConversion(/* 원본 형식 */ typeof(bool), /* 대상 형식 */ typeof(String))]
    public class GenderToStringConverter : IValueConverter
    {
        // 데이터 속성을 UI 속성으로 변경할 때
        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            //if (targetType != typeof(bool?))
            //    return null;

            bool? male = (bool?)value; // 들어오는 값이 bool값이냐?

            if (male == null) // null이면 반환
                return null;
            else if (male == true)
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
            if (targetType != typeof(bool?))
                return null;

            String male = (String)value;

            if (male.Equals("남자"))
                return true;
            else
                return false;
        }


    }

    //성별 반전 변환기
    [ValueConversion(/* 원본 형식 */ typeof(bool), /* 대상 형식 */ typeof(bool))]
    public class GenderToReverseConverter : IValueConverter
    {
        // 데이터 속성을 UI 속성으로 변경할 때
        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            //if (targetType != typeof(bool?))
            //    return null;

            bool? male = (bool?)value; // 들어오는 값이 bool값이냐?

            if (male == null) // null이면 반환
                return null;
            else if (male == true)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
        // UI 속성을 데이터 속성으로 변경할 때
        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            if (targetType != typeof(bool?))
                return null;

            String male = (String)value;

            if (male.Equals("남자"))
                return true;
            else if (male.Equals("여자"))
                return false;
            else
            {
                return false;
            }

        }


    }
}
