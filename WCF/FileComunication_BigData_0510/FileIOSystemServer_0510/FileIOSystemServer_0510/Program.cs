using System;
using System.Collections.Generic;
using System.Configuration;
using System.Linq;
using System.ServiceModel;
using System.Text;
using System.Threading.Tasks;

namespace FileIOSystemServer_0510
{
    class Program
    {
        static void Main(string[] args)
        {
            //Address
            Uri uri = new Uri(ConfigurationManager.AppSettings["addr"]);
            //Contract-> Setting
            //Binding -> App.Config
            ServiceHost host = new ServiceHost(typeof(FileIOSystemServer_0510.CFile), uri);

            //오픈
            host.Open();
            Console.WriteLine("파일 서비스를 시작합니다 {0}", uri.ToString());
            Console.WriteLine("http://192.168.0.33:8080/GetService");
            Console.WriteLine("멈추시려면 엔터를 눌러주세요..");
            Console.ReadLine();
            //서비스
            host.Abort();
            host.Close();

        }
    }
}
