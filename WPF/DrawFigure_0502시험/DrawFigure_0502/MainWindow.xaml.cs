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
using System.Windows.Forms;
using System.ComponentModel;
using System.Collections.Specialized;

namespace DrawFigure_0502
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        //도형 리스트
        public List<Figure> typelist = new List<Figure>();
        public Figure currentfigure = new Figure();
        public MainWindow()
        {
            InitializeComponent();

            typelist.Add(new Figure());

            ListBox1.ItemsSource = typelist;
            ICollectionView view = CollectionViewSource.GetDefaultView(ListBox1.ItemsSource);
            view.GroupDescriptions.Add(new PropertyGroupDescription("Dt"));

            view.SortDescriptions.Add(new SortDescription("Dt", ListSortDirection.Ascending));


            


            AllDrawInCanvas();

        }
        //타이틀바 출력
        public void PrintTitleBar()
        {
            this.Title = "도형의 개수 : " + typelist.Count.ToString() + "개";
        }
        //화면에 모든 도형 출력
        private void AllDrawInCanvas()
        {
            canvas.Children.Clear();

            foreach(Figure t in typelist)
            {
                //사각형 일때
                if(t.Dt==DrawType.RECT)
                {
                    Rectangle rt = new Rectangle();
                    rt.Width = (double)t.Ds;
                    rt.Height = (double)t.Ds;
                    rt.Stroke = new SolidColorBrush(Colors.Black);
                    rt.Fill = new SolidColorBrush(t.Color);
                    //rt.MouseLeftButtonUp += rt_MouseLeftButtonUp;
                    string temp = string.Format("{0}\r\n{1}", t.Pt.X, t.Pt.Y);
                    rt.ToolTip = temp;
                   
                    Canvas.SetLeft(rt, t.Pt.X);
                    Canvas.SetTop(rt, t.Pt.Y);

                    canvas.Children.Add(rt);
                }
                //타원 일때
                else
                {
                    Ellipse rt = new Ellipse();
                    rt.Width = (double)t.Ds;
                    rt.Height = (double)t.Ds;
                    rt.Stroke = new SolidColorBrush(Colors.Black);
                    rt.Fill = new SolidColorBrush(t.Color);
                    //rt.MouseLeftButtonUp += rt_MouseLeftButtonUp;
                    string temp = string.Format("{0}\r\n{1}", t.Pt.X, t.Pt.Y);
                    rt.ToolTip = temp;

                    Canvas.SetLeft(rt, t.Pt.X);
                    Canvas.SetTop(rt, t.Pt.Y);

                    canvas.Children.Add(rt);
                }
            }
            //타이틀바 그리기
            PrintTitleBar();

        }

        #region Menu Item
        //종료
        private void MenuItem_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        private void MenuItem_Click_ColorRed(object sender, RoutedEventArgs e)
        {
            currentfigure.Color = Colors.Red;
        }

        private void MenuItem_Click_ColorGreen(object sender, RoutedEventArgs e)
        {
            currentfigure.Color = Colors.Green;
        }
        //파란거
        private void MenuItem_Click_1(object sender, RoutedEventArgs e)
        {
            currentfigure.Color = Colors.Blue;
        }
        
        private void MenuItem_Click_FigureSize25(object sender, RoutedEventArgs e)
        {
            currentfigure.Ds =DrawSize.RECT25;
        }

        private void MenuItem_Click_FigureSize50(object sender, RoutedEventArgs e)
        {
            currentfigure.Ds =DrawSize.RECT50;
        }

        //모달 메뉴버튼
        private void MenuItem_Click_2(object sender, RoutedEventArgs e)
        {
            Figure temp = new Figure();
            temp.Color = currentfigure.Color;
            temp.Ds = currentfigure.Ds;
            temp.Dt = currentfigure.Dt;
            temp.X = currentfigure.X;
            temp.Y = currentfigure.Y;

            // 모달 다이얼로그 띄우기
            SettingFigure settingWindow = new SettingFigure(currentfigure);
            settingWindow.modal_grid.DataContext = currentfigure;
            String s = settingWindow.tager.Text;
            if (settingWindow.ShowDialog() == false)
            {
                currentfigure = temp;
            }

        }
        //색상 다이얼로그
        private void MenuItem_Click_ColorDialog(object sender, RoutedEventArgs e)
        {
            ColorDialog cd = new ColorDialog();

            if (cd.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                currentfigure.Color = System.Windows.Media.Color.FromRgb(cd.Color.R, cd.Color.G, cd.Color.B);
            }
        }


        #endregion



        private void canvas_MouseDown(object sender, MouseButtonEventArgs e)
        {
            Figure target = new Figure();

            target.Color = currentfigure.Color;
            target.Ds = currentfigure.Ds;
            target.Dt = currentfigure.Dt;
            currentfigure.X = e.GetPosition(canvas).X;
            currentfigure.Y = e.GetPosition(canvas).Y;
            target.Pt = new Point(e.GetPosition(canvas).X, e.GetPosition(canvas).Y);

            typelist.Add(target);

            ICollectionView view = CollectionViewSource.GetDefaultView(ListBox1.ItemsSource);
            view.Refresh();
         
            ListBox1.Items.Refresh();
            AllDrawInCanvas();

            ListBox1.SelectedIndex = ListBox1.Items.Count - 1;
            ListBox1.Items.MoveCurrentToLast();
            ListBox1.ScrollIntoView(ListBox1.Items.CurrentItem);
        }
       
    }

    /// <summary>
    /// This class contains a few useful extenders for the ListBox
    /// </summary>
    public class ListBoxExtenders : DependencyObject
    {
        public static readonly DependencyProperty AutoScrollToEndProperty = DependencyProperty.RegisterAttached("AutoScrollToEnd", typeof(bool), typeof(ListBoxExtenders), new UIPropertyMetadata(default(bool), OnAutoScrollToEndChanged));

        /// <summary>
        /// Returns the value of the AutoScrollToEndProperty
        /// </summary>
        /// <param name="obj">The dependency-object whichs value should be returned</param>
        /// <returns>The value of the given property</returns>
        public static bool GetAutoScrollToEnd(DependencyObject obj)
        {
            return (bool)obj.GetValue(AutoScrollToEndProperty);
        }

        /// <summary>
        /// Sets the value of the AutoScrollToEndProperty
        /// </summary>
        /// <param name="obj">The dependency-object whichs value should be set</param>
        /// <param name="value">The value which should be assigned to the AutoScrollToEndProperty</param>
        public static void SetAutoScrollToEnd(DependencyObject obj, bool value)
        {
            obj.SetValue(AutoScrollToEndProperty, value);
        }

        /// <summary>
        /// This method will be called when the AutoScrollToEnd
        /// property was changed
        /// </summary>
        /// <param name="s">The sender (the ListBox)</param>
        /// <param name="e">Some additional information</param>
        public static void OnAutoScrollToEndChanged(DependencyObject s, DependencyPropertyChangedEventArgs e)
        {
            var listBox = s as System.Windows.Controls.ListBox;
            var listBoxItems = listBox.Items;
            var data = listBoxItems.SourceCollection as INotifyCollectionChanged;

            var scrollToEndHandler = new System.Collections.Specialized.NotifyCollectionChangedEventHandler(
                (s1, e1) =>
                {
                    if (listBox.Items.Count > 0)
                    {
                        object lastItem = listBox.Items[listBox.Items.Count - 1];
                        listBoxItems.MoveCurrentTo(lastItem);
                        listBox.ScrollIntoView(lastItem);
                    }
                });

            if ((bool)e.NewValue)
                data.CollectionChanged += scrollToEndHandler;
            else
                data.CollectionChanged -= scrollToEndHandler;
        }
    }
}
