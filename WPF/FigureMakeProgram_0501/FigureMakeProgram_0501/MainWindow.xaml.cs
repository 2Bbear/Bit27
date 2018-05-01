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

namespace FigureMakeProgram_0501
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        FigureManger fm = new FigureManger();
        public MainWindow()
        {
            InitializeComponent();


            //testing==============================
            fm.Add(new Figure());
            fm[0].Shape = Figure.EShape.사각형;
            fm[0].Pt = new Point(10, 10);
            fm[0].MyColor = Colors.AliceBlue;

            fm.Add(new Figure());
            fm[1].Shape = Figure.EShape.사각형;
            fm[1].Pt = new Point(20, 10);
            fm[1].MyColor = Colors.AntiqueWhite;

            fm.Add(new Figure());
            fm[2].Shape = Figure.EShape.타원;
            fm[2].Pt = new Point(30, 10);
            fm[2].MyColor = Colors.Azure;

            //===============================


            //Contents Initialize
            Win_Grid.DataContext=fm;
            //Win_FigureList.ItemsSource = fm;

        }
    }
}
