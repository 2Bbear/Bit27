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
    public interface IBank
    {
        [OperationContract]
        Account GetProduct(int _id, string _name);
        [OperationContract]
        bool AddMoney(Account _account, int _money);
        [OperationContract]
        bool MinMoney(Account _account, int _money);
    }

    class Bank : IBank
    {
        //사용자 정의 데이터 형태
        public Account GetProduct(int _id, string _name)
        {
            Account p = new Account();
            p.Id = _id;
            p.Balance = 1000;
            p.AccountName = _name;
            p.CreateDate = DateTime.Now;

            return p;
        }

        public bool AddMoney(Account _account, int _money)
        {
            
            try
            {
                //입금액이 마이너스이거나 0 일때
                if(_money<=0)
                {
                    return false;
                }

               // _account.Balance += _money;
                return true;

            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                return false;
            }
            finally
            {
               
            }
            
            
        }
        public bool MinMoney(Account _account, int _money)
        {
            try
            {
                //입금액이 플러스이거나 0 일때
                if (_money <= 0)
                {
                    return false;
                }
                //잔액이 0일때
                if(_account.Balance<=0)
                {
                    return false;
                }
                //잔액보다 큰 금액을 출금할때
                if(_account.Balance<_money)
                {
                    return false;

                }
                //_account.Balance += _money;
                return true;
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                return false;
            }
            finally
            {
            }
        }
    }
}
