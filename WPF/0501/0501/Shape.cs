using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Media;

namespace _0501
{
    public class Shape : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;

        private bool type;
        public bool Type
        {
            get { return type; }
            set
            {
                type = value;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("Type"));
            }
        }


        private int pointx;
        public int PointX
        {
            get { return pointx; }
            set
            {
                pointx = value;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("PointX"));
            }
        }

        private int pointy;

        public int PointY
        {
            get { return pointy; }
            set
            {
                pointy = value;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("PointY"));
            }
        }

        private int size;
        public int Size
        {
            get { return size; }
            set
            {
                size = value;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("Size"));
            }
        }
       
        private Color color;
        public Color Color
        {
            get { return color; }
            set
            {
                
                color = value;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("Color"));
            }
        }
                    
        public override string ToString()
        {           
            return string.Format("[{0}] {1}:{2}",
                Type?"사각형":"타원", PointX, PointY );
        }
    }


    [ValueConversion(/* 원본 형식 */ typeof(bool), /* 대상 형식 */ typeof(bool))]
    public class TypeToToggleConverter : IValueConverter
    {
        // 데이터 속성을 UI 속성으로 변경할 때
        public object Convert(object value, Type targetType, object parameter,
                System.Globalization.CultureInfo culture)
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
        public object ConvertBack(object value, Type targetType, object
                parameter, System.Globalization.CultureInfo culture)
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


    [ValueConversion(/* 원본 형식 */ typeof(int), /* 대상 형식 */ typeof(int))]
    public class SizeConverter : IValueConverter
    {
        // 데이터 속성을 UI 속성으로 변경할 때
        public object Convert(object value, Type targetType, object parameter,
                System.Globalization.CultureInfo culture)
        {
            // if (targetType != typeof(bool?))
            //    return null;

            int size = (int)value;

            if (size == 50)
                return 0;
            else if (size == 100)
                return 1;
            else
                return 2;
        }

        // UI 속성을 데이터 속성으로 변경할 때
        public object ConvertBack(object value, Type targetType, object
                parameter, System.Globalization.CultureInfo culture)
        {
            //   if (targetType != typeof(bool?))
            //       return null;

            int index = (int)value;
            if (index == 0)
                return 50;
            else if (index == 1)
                return 100;
            else
                return 150;
        }
    }

    [ValueConversion(/* 원본 형식 */ typeof(Color), /* 대상 형식 */ typeof(int))]
    public class ColorConverter : IValueConverter
    {
        static string GetColorName(Color col)
        {
            PropertyInfo colorProperty = typeof(Colors).GetProperties().FirstOrDefault(p => Color.AreClose((Color)p.GetValue(null), col));
            return colorProperty != null ? colorProperty.Name : "unnamed color";
        }

        // 데이터 속성을 UI 속성으로 변경할 때
        public object Convert(object value, Type targetType, object parameter,
                System.Globalization.CultureInfo culture)
        {
            // if (targetType != typeof(bool?))
            //    return null;

            Color colorvalue = (Color)value;
           System.Reflection.PropertyInfo[] info=typeof(Colors).GetProperties();

           for(int i=0; i< info.Length;i++)
            {
                System.Reflection.PropertyInfo d2 = info[i];
                if (d2.Name.Equals(GetColorName(colorvalue)))
                {
                    return i;
                }
            }
           // d[target]
            //if (size == 50)
            //    return 0;
            //else if (size == 100)
            //    return 1;
            //else
            //    return 2;
            return null;
        }

        // UI 속성을 데이터 속성으로 변경할 때
        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            //   if (targetType != typeof(bool?))
            //       return null;

            int index = (int)value;

            System.Reflection.PropertyInfo[] info = typeof(Colors).GetProperties();
            //int => Color
            String s = info[index].ToString();
            String[] d = s.Split(' ');
            String taa = d[1];
           // string str = com.SelectedItem as string;
           return(Color)typeof(Colors).GetProperty(taa).GetValue(null);
           
        }
    }

    public class ShortNumberValidationRule : ValidationRule
    {
        int min;
        public int Min
        {
            get { return min; }
            set { min = value; }
        }
        int max;
        public int Max
        {
            get { return max; }
            set { max = value; }
        }
        public override ValidationResult Validate(object value,
        System.Globalization.CultureInfo cultureInfo)
        {
            int number;
            if (!int.TryParse((string)value, out number))
            {
                return new ValidationResult(false, "정수를 입력하세요.");
            }
            if (min <= number && number <= max)
            {
                // new ValidationResult(true, null) 같다
                return ValidationResult.ValidResult;
            }
            else
            {
                string msg =
                string.Format("단축 번호는 {0}에서 {1}까지 입력 가능합니다.", min, max);
                return new ValidationResult(false, msg);
            }
        }
    }

    //정수값 입력시 오류
    //문자열 개수 2~5 이외 오류
    public class nameValidationRule : ValidationRule
    {
        public int Min { get; set; }
        public int Max { get; set; }

        public override ValidationResult Validate(object value,
        System.Globalization.CultureInfo cultureInfo)
        {
            int number;
            if (int.TryParse((string)value, out number))
            {
                return new ValidationResult(false, "문자를 입력하세요.");
            }
            float fnumber;
            if (float.TryParse((string)value, out fnumber))
            {
                return new ValidationResult(false, "문자를 입력하세요.");
            }

            string namevalue = (string)value;

            if (Min <= namevalue.Length && namevalue.Length <= Max)
            {
                // new ValidationResult(true, null) 같다
                return ValidationResult.ValidResult;
            }
            else
            {
                string msg =
                string.Format("이름의 문자 개수는 {0}에서 {1}까지 입력 가능합니다.", Min, Max);
                return new ValidationResult(false, msg);
            }
        }
    }
}
