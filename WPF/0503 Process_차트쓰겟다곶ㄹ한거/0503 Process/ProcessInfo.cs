using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Diagnostics.Eventing.Reader;
using System.IO;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Timers;

namespace SampleProcess
{
    /// <summary>
    /// 
    /// </summary>
    /// 
    public delegate void SysDataCallback(SystemData sysdata);
    public delegate void TagCallback(Tag tag);

    class ProcessInfo
    {
        #region 싱글톤
        private ProcessInfo() { }
        public static ProcessInfo Singleton { get; private set; }
        static ProcessInfo()
        {
            Singleton = new ProcessInfo();
        }
        #endregion

        public SysDataCallback Sysdatacallback { get; set; }
        public TagCallback Tagcallback { get; set; }


        PerformanceCounterCategory pcg;
        PerformanceCounter cpu;
        PerformanceCounter memory;
        PerformanceCounter memory_ava;
        PerformanceCounter disk_read;
        PerformanceCounter disk_write;
        PerformanceCounter net_sent;
        PerformanceCounter net_recv;
        double mem_total;
        DriveInfo[] driveInfo;
        Process[] process;
        public List<Process> list = new List<Process>();

        Random rand = new Random();

        /// <summary>
        /// [성능카운트 열거]
        /// 현재 컴퓨터의 모든 성능 카운터를 열거
        /// 위 예제는 엄청나게 긴 출력 결과를 포함, InstaceExists의 구현이 효율적이지 않아 오랜 시간이 걸림
        /// 실제 시스템에서 카운터들에 관한 자세한 정보는 꼭 필요할 때에만 조회해야 함
        /// </summary>
        public void EnumProcess()
        {
            PerformanceCounterCategory[] pcca =
                            PerformanceCounterCategory.GetCategories();

            // 각 범주(카테고리)별로 열거
            foreach (PerformanceCounterCategory pcc in pcca)
            {
                Console.WriteLine("범주: " + pcc.CategoryName);
                string[] pccInstances = pcc.GetInstanceNames();
                // 인스턴스가 하나도 없는 경우
                // 범주 자체에 대한 카운터들을 표시
                if (pccInstances.Length == 0)
                {
                    foreach (PerformanceCounter pc in pcc.GetCounters())
                    {
                        Console.WriteLine("  카운터: " + pc.CounterName);
                    }
                }
                // 인스턴스가 하나 이상인 경우
                else
                {
                    // 각 인스턴스별로 열거
                    foreach (string pccInstance in pccInstances)
                    {
                        Console.WriteLine("  인스턴스: " + pccInstance);
                        // 인스턴스가 실제 존재하는지 확인해야함
                        // 이름은 존재하는데, 실제 내용이 없는 경우가 있음
                        if (pcc.InstanceExists(pccInstance))
                        {
                            foreach (PerformanceCounter pc in pcc.GetCounters(pccInstance))
                            {
                                Console.WriteLine("    카운터: " + pc.CounterName);
                            }
                        }
                    }
                }
            }

        }

        /// <summary>
        /// [성능 카운터 자료 읽기]
        /// * 생성자 - 범주 이름, 카운터 이름, 인스턴스 지정
        /// NextValue: float
        /// NextSample: ConuterSample (좀 더 자세한 정보)
        /// </summary>
        public void PerformanceCountRead()
        {            
            EventWaitHandle stopper = new ManualResetEvent(false);
                new Thread(() => Monitor("Processor", "% Processor Time", "_Total", stopper)).Start();
                new Thread(() => Monitor("LogicalDisk", "% Idle Time", "C:", stopper)).Start();
            
            var defaultColor = Console.ForegroundColor;
            Console.ForegroundColor = ConsoleColor.Yellow;
            Console.WriteLine("Monitoring... Press any key to exit...");
            Console.ForegroundColor = defaultColor;
            Console.ReadKey(true);
            stopper.Set();
        }

        
        static void Monitor (string category, string counter, string instance, EventWaitHandle stopper)
        {
            // 카테고리 체크
            if (!PerformanceCounterCategory.Exists (category))
            {
                throw new InvalidOperationException("해당 범주 없음");
            }
            // 카운터 체크
            if (!PerformanceCounterCategory.CounterExists(counter, category))
            {
                throw new InvalidOperationException("해당 카운터 없음");
            }
            // 인스턴스 체크
            if (instance == null)
            {
                instance = "";
            }
            if (instance != "" && !PerformanceCounterCategory.InstanceExists(instance, category))
            {
                throw new InvalidOperationException("해당 인스턴스 없음");
            }
            // 비교할 기존 값
            float lastValue = 0f;
            // 체크 반복 딜레이
            const int delay = 5000;
            using (PerformanceCounter pc = new PerformanceCounter(category, counter, instance))
            {
                // 딜레이 간격으로 실행
                while (!stopper.WaitOne (delay, false))
                {
                    float value = pc.NextValue();
                    //string labelString = $"{pc.CategoryName.PadLeft(15)} - {pc.InstanceName.PadLeft(10)} - {pc.CounterName.PadLeft(10)}";
                    string labelString = string.Format("{0}-{1}-{2}", pc.CategoryName.PadLeft(15), pc.InstanceName.PadLeft(10), pc.CounterName.PadLeft(10));
                    // 기존 값과 측정 값이 서로 다르다면 출력
                    if (value != lastValue)
                    {
                        //Console.WriteLine("{labelString}: {value}");
                        Console.WriteLine("{0}: {1}", labelString, value);
                        lastValue = value;
                    }
                }
            }
        }    
    
        public void GetProcessInfo()
        {   
            //===========================================================
            pcg = new PerformanceCounterCategory("Network Interface");
            string instance = pcg.GetInstanceNames()[1];
            cpu = new PerformanceCounter("Processor", "% Processor Time", "_Total");
            memory = new PerformanceCounter("Memory", "% Committed Bytes In Use", null);
            memory_ava = new PerformanceCounter("Memory", "Available MBytes", null);
            disk_read = new PerformanceCounter("PhysicalDisk", "Disk Read Bytes/sec", "_Total");
            disk_write = new PerformanceCounter("PhysicalDisk", "Disk Write Bytes/sec", "_Total");
            net_sent = new PerformanceCounter("Network Interface", "Bytes Sent/sec", instance);
            net_recv = new PerformanceCounter("Network Interface", "Bytes Received/sec", instance);

            //https://msdn.microsoft.com/ko-kr/library/microsoft.visualbasic.devices.computerinfo(v=vs.110).aspx
            mem_total = new Microsoft.VisualBasic.Devices.ComputerInfo().TotalPhysicalMemory;

            //==================================
            Thread thread = new Thread(GetFunction);
            thread.IsBackground = true;
            thread.Start();
            //==================================
        }

        private void GetFunction()
        {
            while (true)
            {
                try
                {
                    //Console.Clear();

                    #region SytemData set

                    driveInfo = DriveInfo.GetDrives();
                    process = Process.GetProcesses();
                    list.Clear();
                    foreach (Process p in process)
                    {
                        list.Add(p);
                    }

                    SystemData sysdata = new SystemData()
                    {
                        Computer = "PC이름",
                        RightNow = DateTime.Now,
                        Cpu = System.Math.Round(cpu.NextValue(), 2),
                        Memory = System.Math.Round(memory.NextValue(), 2),
                        Memory_total = System.Math.Round(mem_total / (1024 * 1024 * 1024), 2),
                        Memory_ava = System.Math.Round(memory_ava.NextValue() / 1024, 2),
                        NetWork_recv = System.Math.Round(net_recv.NextValue() / 1024, 2),
                        NetWork_sent = System.Math.Round(net_sent.NextValue() / 1024, 2),
                        Disk_read = System.Math.Round(disk_read.NextValue() / (1024 * 1024), 2),
                        Disk_write = System.Math.Round(disk_write.NextValue() / (1024 * 1024), 2),
                        Disk_total = System.Math.Round((double)driveInfo[0].TotalSize / (1024 * 1024 * 1024), 2),
                        Disk_ava = System.Math.Round((double)driveInfo[0].TotalFreeSpace / (1024 * 1024 * 1024), 2),
                        Process = list
                    };
                    sysdata.Disk = 100 - Math.Round(sysdata.Disk_ava / sysdata.Disk_total, 4) * 100;


                    Sysdatacallback(sysdata);//<===========================
                    
                    #endregion
                }
                catch (Exception ex)
                {
                    Console.Write(ex.Message + " M sysdata");
                }

                try
                {
                    #region TagData set

                    List<int> tags = new List<int>();
                    for (int i = 0; i < 100; i++)
                        tags.Add(rand.Next(0, 101));
                    Tag tag = new Tag(tags);
                    tag.RightNow = DateTime.Now;

                    Tagcallback(tag);   //<==============================
                    #endregion
     
                }
                catch (Exception ex)
                {
                    Console.Write(ex.Message + " M tag");

                }
                Thread.Sleep(400);
            }
        }
    }
}

/*
var anInt = 1;
var aBool = true;
var aString = "3";
var formated = string.Format("{0},{1},{2}", anInt, aBool, aString);
 * 
//======================================
var anInt = 1;
var aBool = true;
var aString = "3";
var formated = $"{anInt},{aBool},{aString}";
*/