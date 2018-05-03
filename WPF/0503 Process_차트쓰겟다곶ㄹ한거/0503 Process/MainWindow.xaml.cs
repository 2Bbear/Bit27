using SampleProcess;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.DataVisualization.Charting;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;
using Xceed.Wpf.Toolkit.Chart;
namespace _0503_Process
{
    /// <summary>
    /// MainWindow.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class MainWindow : Window
    {
        private SystemData sysdata = new SystemData();
        private List<My_Process> tempprocesslist = new List<My_Process>();
        

        public void SystemDataCallback(SystemData sysdata)
        {
            this.sysdata = sysdata;
            this.Cpu_Index_1.Dispatcher.Invoke(DispatcherPriority.Normal,
               new Action(() => { this.sysdata.Process = sysdata.Process;
                   Cpu_Chart.DataContext = sysdata;
               }));
           
           
            this.Cpu_Index_1.Dispatcher.Invoke(DispatcherPriority.Normal,
                       new Action(() => { Cpu_Index_1.Text = sysdata.Cpu.ToString(); }));

            this.Cpu_Index_1.Dispatcher.Invoke(DispatcherPriority.Normal,
                      new Action(() => { Memmory_Index_2.Text = sysdata.Memory.ToString(); }));


            this.Cpu_Index_1.Dispatcher.Invoke(DispatcherPriority.Normal,
                      new Action(() => { Memory_total_Index_3.Text = sysdata.Memory_total.ToString(); }));


            this.Cpu_Index_1.Dispatcher.Invoke(DispatcherPriority.Normal,
                      new Action(() => { Memory_ava_Index_4.Text = sysdata.Memory_ava.ToString(); }));


            this.Cpu_Index_1.Dispatcher.Invoke(DispatcherPriority.Normal,
                      new Action(() => { NetWork_recv_Index_5.Text = sysdata.NetWork_recv.ToString(); }));


            this.Cpu_Index_1.Dispatcher.Invoke(DispatcherPriority.Normal,
                      new Action(() => { NetWork_sent_Index_6.Text = sysdata.NetWork_sent.ToString(); }));


            this.Cpu_Index_1.Dispatcher.Invoke(DispatcherPriority.Normal,
                      new Action(() => { Disk_read_Index_7.Text = sysdata.Disk_read.ToString(); }));


            this.Cpu_Index_1.Dispatcher.Invoke(DispatcherPriority.Normal,
                      new Action(() => { Disk_write_Index_8.Text = sysdata.Disk_write.ToString(); }));


            this.Cpu_Index_1.Dispatcher.Invoke(DispatcherPriority.Normal,
                      new Action(() => { Disk_total_Index_9.Text = sysdata.Disk_total.ToString(); }));


            this.Cpu_Index_1.Dispatcher.Invoke(DispatcherPriority.Normal,
                      new Action(() => { Disk_ava_Index_10.Text = sysdata.Disk_ava.ToString(); }));

            

            //for (int i = 0; i < sysdata.Process.Count; i++)
            //{
            //    this.Cpu_Index_1.Dispatcher.Invoke(DispatcherPriority.Normal,
            //    new Action(() => { Win_ListBox1.Items.Add(sysdata.Process[i].ProcessName.ToString()); }));

            //}

            //Console.Clear();
            //Console.WriteLine("[데이터 생성 시간" + sysdata.RightNow + "]");
            //Console.WriteLine("--------------- 시스템 데이터 정보 -----------------------");
            //Console.WriteLine("1) Cpu    : " + sysdata.Cpu);
            //Console.WriteLine("2) Ram    : " + sysdata.Memory);
            //Console.WriteLine("3) Disk_R : " + sysdata.Disk_read);
            //Console.WriteLine("4) Net_R  : " + sysdata.NetWork_recv);
            //Console.WriteLine("5) Net_S  : " + sysdata.NetWork_sent);

            //Console.WriteLine("6) mem_t  : " + sysdata.Memory_total);
            //Console.WriteLine("6) mem_a  : " + sysdata.Memory_ava);

            //Console.WriteLine("7) Process 실행 개수 : {0}", sysdata.Process.Count);
            
            //foreach (Process p in sysdata.Process)
            //{

            //    this.EventViewer_Listview.Dispatcher.Invoke(DispatcherPriority.Normal,new Action(() => {
            //        tempprocesslist.Add(new My_Process(p.BasePriority, p.ProcessName));
            //        EventViewer_Listview.Items.Refresh();
            //    }));

            //}
           
            //Console.WriteLine();
        }

        public void TagCallback(Tag tag)
        {
            //Console.WriteLine("--------------- 렌덤 발생한 태그 정보 시뮬레이션 -----------------------");
            //Console.WriteLine(tag.RightNow + " Tag 데이터 \n");
            //Console.WriteLine(tag.tags[0] + "," + tag.tags[1]);
            //Console.WriteLine("-------------------------------------------------------------------");
            this.Tag_NG.Dispatcher.Invoke(DispatcherPriority.Normal,
                        new Action(() => { Tag_NG.Content = tag.tags[0]; }));
            this.Tag_G.Dispatcher.Invoke(DispatcherPriority.Normal,
                        new Action(() => { Tag_G.Content = tag.tags[1]; }));
        }


        public MainWindow()
        {
            InitializeComponent();

            Grid_Label.DataContext = sysdata;

            ProcessInfo pinfo = ProcessInfo.Singleton;
            pinfo.Sysdatacallback = SystemDataCallback;
            pinfo.Tagcallback = TagCallback;
            pinfo.GetProcessInfo();

            tempprocesslist.Add(new My_Process(1,"d"));
            //EventViewer_Listview.ItemsSource = d;
            //EventViewer_Listview.ItemsSource = sysdata.Process;
            //EventViewer_Listview.ItemsSource = tempprocesslist;
            EventViewer_Listview.ItemsSource = ProcessInfo.Singleton.list;

            //((LineSeries)myChart.Series[0]).ItemsSource = new KeyValuePair<int, int>[] { new KeyValuePair<int, int>(0, 100), new KeyValuePair<int, int>(1, 130), new KeyValuePair<int, int>(2, 150), };

           
        }
    }
}
