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
        [OperationContract]
        Product GetProduct();


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
        //사용자 정의 데이터 형태
        public Product GetProduct()
        {
            Product p = new Product();
            p.ProductId = 1234;
            p.ProductName = "ABC Chocolate";
            p.Price = 1500.0;
            p.Company = "Lotteee";
            p.CreateDate = DateTime.Parse("2010-01-22");

            return p;
        }


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
