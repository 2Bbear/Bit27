using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Data;
using System.Windows.Media;

namespace DrawFigure_0502
{
    

    public class Figure: INotifyPropertyChanged
    {
        [Flags]
        public enum DrawType { RECT, ELLIPSE }
        
        public enum DrawSize : int { RECT25 = 25, RECT50 = 50 }

        private DrawType dt;
        private Color color;
        private DrawSize ds;
        private Point pt;

        public event PropertyChangedEventHandler PropertyChanged;

        public DrawType Dt {
            get => dt;
            set
            {
                dt = value;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("Dt"));
            }
        }
        public Color Color {
            get => color;
            set
            {
                color = value;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("Color"));
            }
        }
        public DrawSize Ds {
            get => ds;
            set
            {
                ds = value;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("Ds"));
            }
        }
        public Point Pt {
            get => pt;
            set
            {
                pt = value;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("Pt"));
            }
        }

        public double X
        {
            get
            {
                return pt.X;
            }
            set
            {
                pt.X = value;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("X"));
            }
        }
        public double Y
        {
            get
            {
                return pt.Y;
            }
            set
            {
                pt.Y = value;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("Y"));
            }
        }
        public Figure()
        {
            this.Dt = DrawType.RECT;
            this.Color = Colors.Red;
            this.Ds = DrawSize.RECT25;
            this.pt.X = 100;
            this.pt.Y = 100;
        }

        public override string ToString()
        {
            return "형태:"+dt+" X:" + X + " Y:" + Y+" 색상:"+Color;
        }
    }


    //색상을 인덱스로 바꾸는 컨버터 미완성
    [ValueConversion(/* 원본 형식 */ typeof(Color), /* 대상 형식 */ typeof(int))]
    public class ColorToIndexConverter : IValueConverter
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
            System.Reflection.PropertyInfo[] info = typeof(Colors).GetProperties();

            for (int i = 0; i < info.Length; i++)
            {
                System.Reflection.PropertyInfo d2 = info[i];
                if (d2.Name.Equals(GetColorName(colorvalue)))
                {
                    return i;
                }
            }


            return null;
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
}
