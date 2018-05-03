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

namespace _0501
{
    /// <summary>
    /// MainWindow.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class MainWindow : Window
    {
        public Shape currentShape = new Shape();//셋팅 옵션을 위한
        public Shape currentShape2 = new Shape();//현재 아이템을 위한
        public ShapeCollection shaplist = new ShapeCollection();

        public MainWindow()
        {
            InitializeComponent();
            combocolor1.ItemsSource = typeof(Colors).GetProperties();
            combocolor2.ItemsSource = typeof(Colors).GetProperties();
            combocolor3.ItemsSource = typeof(Colors).GetProperties();
            currentShape.Color = Colors.AliceBlue;
            currentShape.PointX = 10;
            currentShape.PointY = 10;
            currentShape.Size = 50;
            currentShape.Type = false;

            //================== 깊은 복사....시발...눈물...
            currentShape2.Type = shaplist[0].Type;
            currentShape2.Size = shaplist[0].Size;
            currentShape2.PointX = shaplist[0].PointX;
            currentShape2.PointY = shaplist[0].PointY;
            currentShape2.Color = shaplist[0].Color;
            //리스트 바인딩
            Win_StackPenel.DataContext = shaplist;
            //현재 아이템 바인딩
            Win_CurrentItemSection.DataContext = currentShape2;
            //설정 옵션 바인딩
            Win_OptionSection.DataContext = currentShape;

            //유효성 검사===================
            Validation.AddErrorHandler(pointx2, shortNumver_ValidationError);
            Validation.AddErrorHandler(pointy2, shortNumver_ValidationError);
        }
       

        void shortNumver_ValidationError(object sender, ValidationErrorEventArgs e)
        {
            MessageBox.Show((string)e.Error.ErrorContent, "유효성 검사 실패");

        }

        private void canvas_MouseUp(object sender, MouseButtonEventArgs e)
        {
            
            if (currentShape.Type)
            {
                Rectangle rt = new Rectangle();
                rt.Width = currentShape.Size;
                rt.Height = currentShape.Size;
                rt.Stroke = new SolidColorBrush(Colors.Black);
                rt.Fill = new SolidColorBrush(currentShape.Color);
                //rt.MouseLeftButtonUp += rt_MouseLeftButtonUp;
                string temp = string.Format("{0}\r\n{1}", (int)e.GetPosition(canvas).X, (int)e.GetPosition(canvas).Y);
                rt.ToolTip = temp;
                currentShape.PointX = (int)e.GetPosition(canvas).X;
                currentShape.PointY = (int)e.GetPosition(canvas).Y;
                Canvas.SetLeft(rt, e.GetPosition(canvas).X);
                Canvas.SetTop(rt, e.GetPosition(canvas).Y);

                canvas.Children.Add(rt);
                
            }
            else
            {
                Ellipse rt = new Ellipse();
                rt.Width = currentShape.Size;
                rt.Height = currentShape.Size;
                rt.Stroke = new SolidColorBrush(Colors.Black);
                rt.Fill = new SolidColorBrush(currentShape.Color);
                //rt.MouseLeftButtonUp += rt_MouseLeftButtonUp;
                string temp = string.Format("{0}\r\n{1}", (int)e.GetPosition(canvas).X, (int)e.GetPosition(canvas).Y);
                rt.ToolTip = temp;
                currentShape.PointX = (int)e.GetPosition(canvas).X;
                currentShape.PointY = (int)e.GetPosition(canvas).Y;
                Canvas.SetLeft(rt, e.GetPosition(canvas).X);
                Canvas.SetTop(rt, e.GetPosition(canvas).Y);

                

                canvas.Children.Add(rt);
            }

            Save_ElementInList();

            Wid_ListBox.Items.Refresh();

        }
        private void Save_ElementInList()
        {
            Shape t = new Shape();
            t.Type = currentShape.Type;
            t.PointX = currentShape.PointX;
            t.PointY = currentShape.PointY;
            t.Size = currentShape.Size;
            t.Color = currentShape.Color;

            shaplist.Add(t);

        }
        private void Button_Click(object sender, RoutedEventArgs e)
        {
            
        }
        private void AllDrawInCanvas()
        {
            canvas.Children.Clear();

            foreach(Shape t in shaplist)
            {
                if (t.Type)
                {
                    Rectangle rt = new Rectangle();
                    rt.Width = t.Size;
                    rt.Height = t.Size;
                    rt.Stroke = new SolidColorBrush(Colors.Black);
                    rt.Fill = new SolidColorBrush(t.Color);
                    //rt.MouseLeftButtonUp += rt_MouseLeftButtonUp;
                    string temp = string.Format("{0}\r\n{1}", t.PointX, t.PointY);
                    rt.ToolTip = temp;
                    currentShape.PointX = t.PointX;
                    currentShape.PointY = t.PointY;
                    Canvas.SetLeft(rt, t.PointX);
                    Canvas.SetTop(rt, t.PointY);

                    canvas.Children.Add(rt);

                }
                else
                {
                    Ellipse rt = new Ellipse();
                    rt.Width = t.Size;
                    rt.Height = t.Size;
                    rt.Stroke = new SolidColorBrush(Colors.Black);
                    rt.Fill = new SolidColorBrush(t.Color);
                    //rt.MouseLeftButtonUp += rt_MouseLeftButtonUp;
                    string temp = string.Format("{0}\r\n{1}", t.PointX, t.PointY);
                    rt.ToolTip = temp;
                    currentShape.PointX = t.PointX;
                    currentShape.PointY = t.PointY;
                    Canvas.SetLeft(rt, t.PointX);
                    Canvas.SetTop(rt, t.PointY);

                    canvas.Children.Add(rt);
                }
            }
        }
        private void Change_CurrentSectionInfo()
        {
            currentShape2 = new Shape();
            currentShape2.Type = shaplist[Wid_ListBox.SelectedIndex].Type;
            currentShape2.Size = shaplist[Wid_ListBox.SelectedIndex].Size;
            currentShape2.PointX = shaplist[Wid_ListBox.SelectedIndex].PointX;
            currentShape2.PointY = shaplist[Wid_ListBox.SelectedIndex].PointY;
            currentShape2.Color = shaplist[Wid_ListBox.SelectedIndex].Color;

            Win_CurrentItemSection.DataContext = currentShape2;
        }

        private void Search_Button_Click(object sender, RoutedEventArgs e)
        {
            int targetIdx = int.Parse(Win_SearchTextBox.Text);
            Wid_ListBox.SelectedIndex=targetIdx;

            Change_CurrentSectionInfo();

        }

        private void AddFigure_Button_Click(object sender, RoutedEventArgs e)
        {
            Shape t = new Shape();
            if(radiorect3.IsChecked==true)
            {
                t.Type = true;
            }
            else
            {
                t.Type = false;

            }

            t.PointX = int.Parse(pointx3.Text);
            t.PointY = int.Parse(pointy3.Text);
            String []sizestr = comborect3.SelectedItem.ToString().Split(' ');
            t.Size = int.Parse(sizestr[1]);
            String []colorstr = combocolor3.SelectedItem.ToString().Split(' ');
            t.Color =(Color)typeof(Colors).GetProperty(colorstr[1]).GetValue(null);

            shaplist.Add(t);

            if (t.Type)
            {
                Rectangle rt = new Rectangle();
                rt.Width = t.Size;
                rt.Height = t.Size;
                rt.Stroke = new SolidColorBrush(Colors.Black);
                rt.Fill = new SolidColorBrush(t.Color);
                //rt.MouseLeftButtonUp += rt_MouseLeftButtonUp;
                string temp = string.Format("{0}\r\n{1}", t.PointX, t.PointY);
                rt.ToolTip = temp;
                currentShape.PointX = t.PointX;
                currentShape.PointY = t.PointY;
                Canvas.SetLeft(rt, t.PointX);
                Canvas.SetTop(rt, t.PointY);

                canvas.Children.Add(rt);

            }
            else
            {
                Ellipse rt = new Ellipse();
                rt.Width = t.Size;
                rt.Height = t.Size;
                rt.Stroke = new SolidColorBrush(Colors.Black);
                rt.Fill = new SolidColorBrush(t.Color);
                //rt.MouseLeftButtonUp += rt_MouseLeftButtonUp;
                string temp = string.Format("{0}\r\n{1}", t.PointX, t.PointY);
                rt.ToolTip = temp;
                currentShape.PointX = t.PointX;
                currentShape.PointY = t.PointY;
                Canvas.SetLeft(rt, t.PointX);
                Canvas.SetTop(rt, t.PointY);

                canvas.Children.Add(rt);
            }

            Wid_ListBox.Items.Refresh();
        }

        private void Wid_ListBox_MouseUp(object sender, MouseButtonEventArgs e)
        {
            Change_CurrentSectionInfo();
        }
        //수정
        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            try
            {
                shaplist[Wid_ListBox.SelectedIndex].Type = currentShape2.Type;
                shaplist[Wid_ListBox.SelectedIndex].Size = currentShape2.Size;
                shaplist[Wid_ListBox.SelectedIndex].PointX = currentShape2.PointX;
                shaplist[Wid_ListBox.SelectedIndex].PointY = currentShape2.PointY;
                shaplist[Wid_ListBox.SelectedIndex].Color = currentShape2.Color;
                currentShape2 = null;

                Wid_ListBox.Items.Refresh();
                AllDrawInCanvas();
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
            finally
            {
            }
            
        }
        //삭제
        private void Button_Click_2(object sender, RoutedEventArgs e)
        {
            try
            {
                shaplist.RemoveAt(Wid_ListBox.SelectedIndex);
                Wid_ListBox.Items.Refresh();
                currentShape2 = null;

                AllDrawInCanvas();
                Wid_ListBox.SelectedIndex = 0;
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
            finally
            {
            }
           
            

        }
    }
}
