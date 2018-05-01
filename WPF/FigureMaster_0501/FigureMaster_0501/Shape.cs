using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Data;
using System.Windows.Media;

namespace FigureMaster_0501
{
    class Shape : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;

        private bool type;
        public bool Type {
            get => type; set
            {
                type = value;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("Type"));
            }
        }

        private int pointx;
        public int Pointx
        {
            get => pointx; set
            {
                pointx = value;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("Pointx"));
            }
        }

        private int pointy;
        public int Pointy
        {
            get => pointy; set
            {
                pointy = value;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("Pointy"));
            }
        }

        private int size;
        public int Size
        {
            get => size; set
            {
                size = value;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("Size"));
            }
        }

        private Color color;
        public Color Color
        {
            get => color; set
            {
                color = value;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("Color"));
            }
        }

        public override string ToString()
        {
            return String.Format("[{0}] {1} : {2} ",Type?"사각형":"타원",Pointx,Pointy);
        }
    }

    //Type To 반전 변환기
    [ValueConversion(/* 원본 형식 */ typeof(bool), /* 대상 형식 */ typeof(bool))]
    public class ShapeToReversConverter : IValueConverter
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

            bool male = (bool)value;

            if (male==false)
                return true;
            else
                return false;
        }


    }
}
