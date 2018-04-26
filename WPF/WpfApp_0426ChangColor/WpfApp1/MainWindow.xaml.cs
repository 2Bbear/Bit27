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

namespace WpfApp1
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
           
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            
        }

        private void Canvas_MouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        {
            Rectangle rt = new Rectangle();
            rt.Name = "myrec";
            rt.Width = 50;
            rt.Height = 50;
            rt.Stroke = new SolidColorBrush(Colors.Blue);
            rt.Fill = new SolidColorBrush(Colors.DarkOrange);
            rt.MouseLeftButtonDown += Rt_MouseLeftButtonDown;
            rt.MouseLeftButtonUp += Rt_MouseLeftButtonUp;
            //사각형을 Canvas 어디에 배치할 것인지 지정한다.
            Canvas.SetLeft(rt, e.GetPosition(canvas).X-25);
            Canvas.SetTop(rt, e.GetPosition(canvas).Y-25);
            // 사각형을 위치시킨다.(그린다.)
            canvas.Children.Add(rt);
        }

        private void Rt_MouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        {
            if (Keyboard.IsKeyDown(Key.LeftCtrl))
            {
                Rectangle r = (Rectangle)sender;
                canvas.Children.Remove(r);
                e.Handled = true;//버블릭을 막는 코드 부모를 호출하지 말라는 의미
                return;
            }
            throw new NotImplementedException();
        }

        private void Rt_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
           
            
            //throw new NotImplementedException();
        }
    }
}
