using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ServiceModel;


namespace ServiceApp
{


    // 1. 서비스 계약 선언
    [ServiceContract]
    public interface ICal
    {
        [OperationContract]// 오퍼레이션 계약
        int Add(int a, int b);
        [OperationContract]// 오퍼레이션 계약
        int Sub(int a, int b);
        [OperationContract]// 오퍼레이션 계약
        int Mul(int a, int b);
        [OperationContract]// 오퍼레이션 계약
        double Div(int a, int b);
    }

    class CCal : ICal
    {
        public int Add(int a, int b)
        {
            return a + b;
        }

        public double Div(int a, int b)
        {
            return (double)a / b;
        }

        public int Mul(int a, int b)
        {
            return a * b;
        }

        public int Sub(int a, int b)
        {
            return a - b;
        }
    }
}
