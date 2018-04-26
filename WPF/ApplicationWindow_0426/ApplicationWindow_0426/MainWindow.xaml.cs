﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
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


namespace ApplicationWindow_0426
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        
        public MainWindow()
        {
            InitializeComponent();

            //this.Background = MakeRadialGradientBrush();

        }
       
        private RadialGradientBrush MakeRadialGradientBrush()
        {
            RadialGradientBrush brush;
            brush = new RadialGradientBrush(Colors.White, Colors.Red);
            brush.RadiusX = brush.RadiusY = 0.01f;
            brush.SpreadMethod = GradientSpreadMethod.Repeat;
            Background = brush;

            return brush;

        }
        private LinearGradientBrush MakeGradientBrush1()
        {
            //LinearGradientBrush 객체 선언
            LinearGradientBrush brush;
            //메모리 생성
            brush = new LinearGradientBrush();
            //시작점 설정
            brush.StartPoint = new Point(0, 0);
            //끝점 설정
            brush.EndPoint = new Point(0, 1);
            //첫번째 색상
            brush.GradientStops.Add(new GradientStop(Colors.LightSeaGreen, 0));
            //두번째 색상
            brush.GradientStops.Add(new GradientStop(Colors.Violet, 1));

            return brush;
        }
        private LinearGradientBrush MakeGradientBrush2()
        {
            LinearGradientBrush brush;
            //새롭게 LinearGradientBrush 설정
            brush = new LinearGradientBrush(Colors.OrangeRed, Colors.DarkRed, 90);


            return brush;
        }
        private LinearGradientBrush MakeGradientBrush3()
        {
            LinearGradientBrush brush;
            //새롭게 LinearGradientBrush 설정
            brush = new LinearGradientBrush(Colors.DarkViolet, Colors.White, new Point(0, 0), new Point(0, 1));


            return brush;
        }
        private LinearGradientBrush MakeGradientBrush4()
        {
            LinearGradientBrush brush;
            //새롭게 LinearGradientBrush 설정
            GradientStopCollection stopCollection = new GradientStopCollection();
            stopCollection.Add(new GradientStop(Colors.OrangeRed, 0));
            stopCollection.Add(new GradientStop(Colors.LightYellow, 1));
            brush = new LinearGradientBrush(stopCollection);
            brush.StartPoint = new Point(0, 0);
            brush.EndPoint = new Point(0, 1);
            brush = new LinearGradientBrush(stopCollection, 90);
            brush = new LinearGradientBrush(stopCollection, new Point(0, 0), new Point(0, 1));
            brush = new LinearGradientBrush(stopCollection);

            return brush;
        }
     


        private void Window_KeyDown(object sender, KeyEventArgs e)
        {
            
        }

       

        private void Window_MouseDown(object sender, MouseButtonEventArgs e)
        {
            RadialGradientBrush brush;
            brush = new RadialGradientBrush(Colors.White, Colors.Red);
            double width = ActualWidth - 2 * SystemParameters.ResizeFrameVerticalBorderWidth;
            double height = ActualHeight - 2 * SystemParameters.ResizeFrameHorizontalBorderHeight - SystemParameters.CaptionHeight;

            Point ptMouse = e.GetPosition(this);
            ptMouse.X /= width;
            ptMouse.Y /= height;

            if (e.ChangedButton == MouseButton.Left)
            {
                brush.Center = ptMouse;
                brush.GradientOrigin = ptMouse;
            }

            else if (e.ChangedButton == MouseButton.Right)
            {
                brush.GradientOrigin = ptMouse;
            }
            this.Background = brush;
        }
    }
}
