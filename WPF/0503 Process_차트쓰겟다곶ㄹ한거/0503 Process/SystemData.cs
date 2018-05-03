using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SampleProcess
{
    public class SystemData : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;

        public string Computer {get; set;}
        public DateTime RightNow{get; set;}

        private double cpu;
        public double Cpu
        {
            get { return cpu; }
            set
            {
                cpu = value;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("Cpu"));
            }
        }
        public double memory;
        public double Memory
        {
            get { return memory; }
            set
            {
                memory = value;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("Memory"));
            }
        }
        public double memory_total;
        public double Memory_total
        {
            get { return memory_total; }
            set
            {
                memory_total = value;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("Memory_total"));
            }
        }
        public double memory_ava;
        public double Memory_ava
        {
            get { return memory_ava; }
            set
            {
                memory_ava = value;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("Memory_ava"));
            }
        }
        public double netWork_recv;
        public double NetWork_recv
        {
            get { return netWork_recv; }
            set
            {
                netWork_recv = value;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("NetWork_recv"));
            }
        }
        public double netWork_sent;
        public double NetWork_sent
        {
            get { return netWork_sent; }
            set
            {
                netWork_sent = value;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("NetWork_sent"));
            }
        }

        public double disk_read;
        public double Disk_read
        {
            get { return disk_read; }
            set
            {
                disk_read = value;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("Disk_read"));
            }
        }
        public double disk_write;
        public double Disk_write
        {
            get { return disk_write; }
            set
            {
                disk_write = value;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("Disk_write"));
            }
        }
        public double disk_total;
        public double Disk_total
        {
            get { return disk_total; }
            set
            {
                disk_total = value;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("Disk_total"));
            }
        }
        public double disk_ava;
        public double Disk_ava
        {
            get { return disk_ava; }
            set
            {
                disk_ava = value;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("Disk_ava"));
            }
        }
        public List<Process> Process { get; set; }
        public double disk;
        public double Disk
        {
            get { return disk; }
            set
            {
                disk = value;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("Disk"));
            }
        }   
    }
}
