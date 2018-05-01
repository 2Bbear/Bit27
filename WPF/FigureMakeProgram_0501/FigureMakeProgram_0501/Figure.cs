using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Media;
using System.Windows.Data;

namespace FigureMakeProgram_0501
{
    public class Figure: INotifyPropertyChanged
    {
        private static int opUpMakeID;
        private int id;
        [Flags]
        public enum EShape {사각형,삼각형,타원 }
        //도형 형태
        private EShape shape;
        //도형 좌표
        private Point pt;
        //도형 크기
        private int size;
        //도형 색상
        private Color mycolor;

        public Figure()
        {
            id = OpUpMakeID;
            OpUpMakeID++;
        }

        static Figure()
        {
            OpUpMakeID = 0;
        }

        //인터페이스 이벤트 핸들러
        public event PropertyChangedEventHandler PropertyChanged;
        
        #region Property
        public EShape Shape
        {
            get
            {
                return shape;
            }
            set
            {
                shape = value;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("Shape"));
            }
        }
        public Point Pt
        {
            get
            {
                return pt;
            }
            set
            {
                pt = value;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("Pt"));
            }
        }
        public int Size
        {
            get
            {
                return size;
            }
            set
            {
                size = value;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("Size"));
            }
        }
        public Color MyColor
        {
            get
            {
                return mycolor;
            }
            set
            {
                mycolor = value;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("MyColor"));
            }
        }

        public int Id
        {
            get => id; set => id = value;
        }
        public static int OpUpMakeID { get => opUpMakeID; set => opUpMakeID = value; }
        #endregion

        





    }
    #region Convertor
    
    #endregion
}
