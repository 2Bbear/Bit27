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
/*
 리스트 에 컨텐츠 자동으로 생기는 것 까지 했는데, 거기에 유효성 검사 중 메세지 박스 띄우는 걸 아직 못함
     */
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

            
            //Validation.AddErrorHandler(Age, shortNumver_ValidationError);
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
        //동적 바인딩
        private void Button_Click2(object sender, RoutedEventArgs e)
        {
            group1 = new People();
            group1.Add(new Person("퉤ㅐㅅ", 20, "상암동", true));
            group1.Add(new Person("퉤에엣", 44, "가리봉동", false));
            group1.Add(new Person("퉷텟", 36, "상암동", true));
            listContent.ItemsSource = group1;
            
        }
    }


}
