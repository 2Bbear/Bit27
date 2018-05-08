using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ServiceModel;
using System.ServiceModel.Description;

namespace ServiceApp
{
    class Program
    {
        static void Main(string[] args)
        {
            BasicHost1();
            //BasicHost();
        }
        static void BasicHost1()
        {
            ServiceHost host = new ServiceHost(typeof(Bank));
            //이후 자동으로 config파일을 뒤져서 엔드포인트를 추가한다.
            host.Open();
            Console.WriteLine("Press Any key to stop the service");
            Console.ReadKey();
            host.Close();

        }

        static void BasicHost()
        {
            // 다음 코드가 정상적으로 작동하기 위해서는 app.config 파일의
            // <services> 요소를 comment 로 막아 두어야 한다.
            ServiceHost host = new ServiceHost(typeof(Bank),
                new Uri("http://192.168.0.33/wcf/example/cal"));

            //엔드포인트 추가
            host.AddServiceEndpoint(
                typeof(IBank),        // service contract
                new BasicHttpBinding(), // service binding
                "");            // relative address


            // ServiceMetadataBehavior 설정  wsdl을 외부로 노출할 것이냐 아니냐. 보안성의 문제
            // http://192.168.0.33/wcf/example/cal  WSDL문서 획득
            ServiceMetadataBehavior behavior = host.Description.Behaviors.Find<ServiceMetadataBehavior>();
            if (behavior == null)
            {
                behavior = new ServiceMetadataBehavior();
                host.Description.Behaviors.Add(behavior);
            }
            behavior.HttpGetEnabled = true;

            host.Open();
            Console.WriteLine("Press Any key to stop the service");
            Console.ReadKey(true);
            host.Close();
        }
    }
}
