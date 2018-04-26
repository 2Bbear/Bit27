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
using System.Windows.Shapes;
using System.Reflection;

namespace WpfApp1
{

    public class MyShape : Shape
    {
        public Object Shape;
        public double X;
        public double Y;

      

        public MyShape(double x,double y, Object shape)
        {
            X = x;
            Y = y;
            Shape = shape;
 
        }

        protected override Geometry DefiningGeometry => throw new NotImplementedException();
    }
    /// <summary            >
    /// Interaction logic for PracticePannell.xaml
    /// </summary>
    /// 
    public partial class PracticePannell : Window
    {
        public List<MyShape> figureList=new List<MyShape>();
        public Color fillingcolor;
        public PracticePannell()
        {
            InitializeComponent();
            Combo2.ItemsSource = typeof(Colors).GetProperties();

            //PointListBox.ItemsSource= typeof(Colors).GetProperties();
            //PropertyInfo[] props = typeof(Colors).GetProperties();
            //foreach (PropertyInfo prop in props)
            //{
            //    Combo2.Items.Add(prop.Name);

            //}

            fillingcolor = Colors.DarkBlue;

        }

        private void Window_Initialized(object sender, EventArgs e)
        {
            
        }

        private void Canvas_MouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        {
            Rectangle rt = new Rectangle();
            rt.Name = "myrec";
            rt.Width = 50;
            rt.Height = 50;
            rt.Stroke = new SolidColorBrush(Colors.Blue);
            
            rt.Fill = new SolidColorBrush(fillingcolor);
            //rt.MouseLeftButtonDown += Rt_MouseLeftButtonDown;
            rt.MouseLeftButtonUp += Rt_MouseLeftButtonUp;
            //사각형을 Canvas 어디에 배치할 것인지 지정한다.
            MyShape dd = new MyShape(e.GetPosition(canvas).X - 25, e.GetPosition(canvas).Y - 25, rt);
            figureList.Add(dd);
            PrintPointListInListBox(figureList);
            //figureList[figureList.Count - 1]
            Canvas.SetLeft(rt, e.GetPosition(canvas).X - 25);
            Canvas.SetTop(rt, e.GetPosition(canvas).Y - 25);
            // 사각형을 위치시킨다.(그린다.)
            canvas.Children.Add(rt);
        }
        private void PrintPointListInListBox(List<MyShape> target)
        {
            PointListBox.Items.Clear();
            foreach (MyShape t in target)
            {
                PointListBox.Items.Add("X :" + (int)(t.X) + " Y :" + (int)(t.Y));
            }
           
 
        }
        private void Rt_MouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        {
            if (Keyboard.IsKeyDown(Key.LeftCtrl))
            {
                int n = 0;
                foreach(MyShape t in figureList)
                {
                    if (((Rectangle)sender) ==t.Shape)
                    {
                        //MessageBox.Show("찾음");
                        figureList.RemoveAt(n);
                        canvas.Children.Remove((Rectangle)sender);
                        PrintPointListInListBox(figureList);
                        break;
                    }
                    n++;
                }
                
            }
            e.Handled = true;//버블릭을 막는 코드 부모를 호출하지 말라는 의미
            return;
            //throw new NotImplementedException();
        }

        private void Combo2_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            String str = Combo2.SelectedItem.ToString();
            String [] blankfilter = str.Split(' ');
            String target = blankfilter[1];
            fillingcolor = (Color)typeof(Colors).GetProperty(target).GetValue(null);
        }
    }
}
