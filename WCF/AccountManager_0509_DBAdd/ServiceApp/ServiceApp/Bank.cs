using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ServiceModel;
using System.Data.SqlClient;
using System.Data;
using System.Runtime.Serialization;

namespace ServiceApp
{


    // 1. 서비스 계약 선언
    [ServiceContract]
    public interface IBank
    {
        //DB 연결 확인
        [OperationContract]
        string ConnectDB();
        //=======================================================================
        ////계좌 생성
        //[OperationContract]
        //Account GetProduct(int balance, string _name);

        //계좌 생성
        [OperationContract]
        bool MakeAccount(Account _account);
        //계좌 삭제
        [OperationContract]
        bool DeleteAccount(int _id);
        //현재 계정의 수를 얻는 함수
        [OperationContract]
        int GetAccCount();
        //입금
        [OperationContract]
        bool InputMoney(int _id, int _money);
        //출금
        [OperationContract]
        bool OutputMoney(int _id, int _money);
        //accid로 계정 검색하기
        [OperationContract]
        Account SelectAccount(int _id);
        //모든 계정 가져오기
        [OperationContract]
        List<Account> SelectAllAccount();
        //모든 계정 가져오기 2
        [OperationContract]
        DataTable SelectAllAccount1();
        //AccID로 계좌 내역 가져오기
        [OperationContract]
        List<AccList> SelectAccountList(int _id);
        //AccID로 계좌 내역 가져오기2
        [OperationContract]
        DataTable SelectAccountList1(int _id);






        ////입금
        //[OperationContract]
        //bool AddMoney(Account _account, int _money);
        ////출금
        //[OperationContract]
        //bool MinMoney(Account _account, int _money);

    }

    class Bank : IBank
    {
        BankAccountDB accDB = BankAccountDB.Singletone;
        BankAccListDB acclistDB = BankAccListDB.Singletone;
        //계정 생성
        public bool MakeAccount(Account _account)
        {
            try
            {
                //계좌 생성
                if(accDB.MakeAccount(_account)==false)
                {
                    return false;
                }
                
                //계좌 내역 생성
                if(acclistDB.InsertAccList(new AccList { accListID=0, accID=_account.Id, balance=_account.Balance, inputMoney=0, outputMoney=0, date= _account.CreateDate })==false)
                {
                    return false;
                }
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
        //계정 삭제
        public bool DeleteAccount(int _id)
        {
            try
            {
                if (acclistDB.DeleteAllAccList(_id) == false)
                {
                    return false;
                }

                if (accDB.DeleteAccount(_id)==false)
                {
                    return false;
                }
               

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

        //id로 계정 찾기
        public Account SelectAccount(int _id)
        {
            try
            {

                return accDB.SelectAccount(_id);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                return null;
            }
            finally
            {
            }
           
        }

        //DB 접속
        public string ConnectDB()
        {
            SqlConnection conn;

            conn = new SqlConnection();
            conn.ConnectionString = @"Server=USER-PC;database=ccm;uid=ccm;pwd=ccm;";

            try
            {
                conn.Open();    //  데이터베이스 연결
                conn.Close();
                return ("데이터베이스 연결 성공...");
                //===============================================================
                //===============================================================
            }
            catch (Exception)
            {
                conn.Close();
                return ("데이터베이스 연결 실패...");
            }

        }

        //계좌 저장 개수 얻기
        public int GetAccCount()
        {
            return accDB.GetAccCount();
        }

        //입금
        public bool InputMoney(int _id, int _money)
        {
            try
            {
                //현재 잔액 획득
                int currentbalance = accDB.GetBalance(_id);
                if(acclistDB.InsertAccList(new AccList { accListID = 0, accID = _id, balance = currentbalance, inputMoney = _money, date = DateTime.Now, outputMoney=0 })==false)
                {
                    return false;

                }
                //입금
                if (accDB.InputMoney(_id, _money)==false)
                {
                    return false;
                }
                //

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
        //출금
        public bool OutputMoney(int _id, int _money)
        {
            try
            {
                //현재 잔액 획득
                int currentbalance = accDB.GetBalance(_id);
                if (acclistDB.InsertAccList(new AccList { accListID = 0, accID = _id, balance = currentbalance, inputMoney = 0, date = DateTime.Now, outputMoney = _money }) == false)
                {
                    return false;

                }
                //출금
                if (accDB.OutputMoney(_id, _money) == false)
                {
                    return false;
                }
                //

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

       

        public List<AccList> SelectAccountList(int _id)
        {
            return acclistDB.SelectAccountList(_id);
        }

        public DataTable SelectAccountList1(int _id)
        {
            throw new NotImplementedException();
        }
        
        public List<Account> SelectAllAccount()
        {

           return accDB.selectAllAccount();
        }

        public DataTable SelectAllAccount1()
        {
            
            throw new NotImplementedException();
        }

        ////사용자 정의 데이터 형태
        //public Account GetProduct(int balance ,string _name)
        //{
        //    Account p = new Account();

        //    p.Balance = balance;
        //    p.AccountName = _name;
        //    p.CreateDate = DateTime.Now;

        //    BankAccountDB.Singletone.MakeAccount(p);
        //    BankAccListDB.Singletone.InsertAccList(p);

        //    return p;
        //}

        //public bool AddMoney(Account _account, int _money)
        //{

        //    try
        //    {
        //        //입금액이 마이너스이거나 0 일때
        //        if(_money<=0)
        //        {
        //            return false;
        //        }

        //       // _account.Balance += _money;
        //        return true;

        //    }
        //    catch (Exception ex)
        //    {
        //        Console.WriteLine(ex.Message);
        //        return false;
        //    }
        //    finally
        //    {

        //    }


        //}
        //public bool MinMoney(Account _account, int _money)
        //{
        //    try
        //    {
        //        //입금액이 플러스이거나 0 일때
        //        if (_money <= 0)
        //        {
        //            return false;
        //        }
        //        //잔액이 0일때
        //        if(_account.Balance<=0)
        //        {
        //            return false;
        //        }
        //        //잔액보다 큰 금액을 출금할때
        //        if(_account.Balance<_money)
        //        {
        //            return false;

        //        }
        //        //_account.Balance += _money;
        //        return true;
        //    }
        //    catch (Exception ex)
        //    {
        //        Console.WriteLine(ex.Message);
        //        return false;
        //    }
        //    finally
        //    {
        //    }
        //}

    }
}
