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

namespace DrawFigure_0502
{
    public enum sss {d,f };
    /// <summary>
    /// Interaction logic for SettingFigure.xaml
    /// </summary>
    public partial class SettingFigure : Window
    {
        Figure pa_target;
        public SettingFigure( Figure t)
        {
            InitializeComponent();
            pa_target = t;
            Setting();

         

        }
        private void Setting()
        {
            //색상
            modal_color.SelectedIndex = 0;
            if(pa_target.Color.Equals(Colors.Red))
            {
                modal_color.SelectedIndex = 0;
            }
            else if (pa_target.Color.Equals(Colors.Green))
            {
                modal_color.SelectedIndex = 1;
            }
            else if (pa_target.Color.Equals(Colors.Blue))
            {
                modal_color.SelectedIndex = 2;
            }

            //크기
            modal_figuresize.SelectedIndex = 0;
            if(pa_target.Ds==DrawSize.RECT25)
            {
                modal_figuresize.SelectedIndex = 0;
            }
            else if (pa_target.Ds == DrawSize.RECT50)
            {
                modal_figuresize.SelectedIndex = 1;
            }

            //형태
            modal_figuretype.SelectedIndex = 0;
            if(pa_target.Dt==DrawType.RECT)
            {
                modal_figuretype.SelectedIndex = 0;
            }
            else if(pa_target.Dt == DrawType.ELLIPSE)
            {
                modal_figuretype.SelectedIndex = 1;
            }

        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            //색상 세팅
            if(modal_color.SelectedIndex==0)
            {
                pa_target.Color = Colors.Red;
            }
            else if (modal_color.SelectedIndex == 1)
            {
                pa_target.Color = Colors.Green;
            }
            else if (modal_color.SelectedIndex == 2)
            {
                pa_target.Color = Colors.Blue;
            }
            //크기 세팅
            if (modal_figuresize.SelectedIndex ==0)
            {
                pa_target.Ds = DrawSize.RECT25;
            }
            else if (modal_figuresize.SelectedIndex == 1)
            {
                pa_target.Ds = DrawSize.RECT50;
            }

            //타입 세팅
            if(modal_figuretype.SelectedIndex==0)
            {
                pa_target.Dt =DrawType.RECT;
            }
            else if (modal_figuretype.SelectedIndex == 1)
            {
                pa_target.Dt = DrawType.ELLIPSE;
            }


            DialogResult = true;
            this.Close();
        }
    }
}
