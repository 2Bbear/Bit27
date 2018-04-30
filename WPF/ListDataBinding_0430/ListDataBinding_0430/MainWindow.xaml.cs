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

namespace ListDataBinding_0430
{

    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        People group1 = new People();
        public MainWindow()
        {
            InitializeComponent();
            group1.Add(new Person("홍길동",20,"상암동",true));
            group1.Add(new Person("고수경", 44, "가리봉동", false));
            group1.Add(new Person("조세호", 36, "상암동", true));

            listContent.ItemsSource = group1;

            
            Validation.AddErrorHandler(Age, shortNumver_ValidationError);
        }
        void shortNumver_ValidationError(object sender, ValidationErrorEventArgs e)
        {
            MessageBox.Show((string)e.Error.ErrorContent, "유효성 검사 실패");

            //shortNumber.ToolTip = (string)e.Error.ErrorContent;
        }
        private void Button_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                group1.RemoveAt(listContent.SelectedIndex);
                listContent.SelectedIndex = 0;
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
            finally
            {
                listContent.Items.Refresh();
            }
            
        }
    }


}
