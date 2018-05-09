using System;
using System.Collections.Generic;
using System.Data;
using System.Data.SqlClient;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ServiceApp
{
    class BankAccountDB
    {
        #region 싱글톤
        public static BankAccountDB Singletone
        {
            get;
            set;
        }

        static BankAccountDB() { Singletone = new BankAccountDB(); }
        private BankAccountDB() { }

        #endregion
        SqlConnection conn_account;
       
        #region Method
      
       
        //이름으로 account idx 찾기
        public int mySearchIdxAccount(string _name)
        {
            SqlConnection conn_searchidx;
            conn_searchidx= new SqlConnection();
            conn_searchidx.ConnectionString = @"Server=USER-PC;database=ccm;uid=ccm;pwd=ccm;";
            conn_searchidx.Open();
            String SQL = "select AccID from Account where (Name = '"+_name+"'); ";
            SqlCommand sqlComm = new SqlCommand();
            SqlDataReader sd;
            sqlComm.CommandText = SQL;

            sqlComm.Connection = conn_searchidx;
            int result=0;
            sd = sqlComm.ExecuteReader();
            while (sd.Read())
            {
                result=int.Parse(sd["AccID"].ToString());
            }

            conn_searchidx.Close();
            return result;
        }

       
        //Account 삭제
        public void myDeleteAccount(int _id)
        {
            conn_account = new SqlConnection();
            conn_account.ConnectionString = @"Server=USER-PC;database=ccm;uid=ccm;pwd=ccm;";
            conn_account.Open();
            String SQL = "DELETE FROM Account WHERE AccID = " + _id + ";";

            SqlCommand sqlComm = new SqlCommand();
            SqlDataReader sd;

            sqlComm.CommandText = SQL;

            sqlComm.Connection = conn_account;

            sd = sqlComm.ExecuteReader();
            conn_account.Close();

        }
        //Account 추가
        private void myCreateAccount(Account _acc)
        {
            conn_account = new SqlConnection();
            conn_account.ConnectionString = @"Server=USER-PC;database=ccm;uid=ccm;pwd=ccm;";
            conn_account.Open();
            String SQL = "INSERT INTO Account VALUES('" + _acc.AccountName + "'," + _acc.Balance.ToString() + ", GETDATE(), '퉷'); ";

            SqlCommand sqlComm = new SqlCommand();
            SqlDataReader sd;

            sqlComm.CommandText = SQL;

            sqlComm.Connection = conn_account;

            sd = sqlComm.ExecuteReader();
            conn_account.Close();
        }

       string temp = @"Server=DESKTOP-3QV6Q1U;database=ccm;uid=jjh27;pwd=ccm;";

        public bool MakeAccount(Account _acc)
        {
            //Account 추가
            myCreateAccount(_acc);

            //=====================================id받아오기
            _acc.Id = mySearchIdxAccount(_acc.AccountName);

            //=====================================
           

            return true;
        }

        public bool DeleteAccount(int _id)
        {
            try
            {
                //Account 삭제
                myDeleteAccount(_id);
                return true;
            }
            catch (Exception ex)
            {
                return false;
               
            }
            finally
            {
            }

           
        }

        public int GetAccCount()
        {
            conn_account = new SqlConnection();
            conn_account.ConnectionString = @"Server=USER-PC;database=ccm;uid=ccm;pwd=ccm;";
            conn_account.Open();
            String SQL = "SELECT COUNT(AccID) FROM Account; ";

            SqlCommand sqlComm = new SqlCommand();
            SqlDataReader sd;

            sqlComm.CommandText = SQL;

            sqlComm.Connection = conn_account;
            int count = 0;

            sd = sqlComm.ExecuteReader();
            while(sd.Read())
            {
                count = int.Parse(sd[0].ToString());
            }

            conn_account.Close();

            return count;
        }

        public int GetBalance(int _id)
        {
            int result = 0;
            try
            {
                conn_account = new SqlConnection();
                conn_account.ConnectionString = @"Server=USER-PC;database=ccm;uid=ccm;pwd=ccm;";
                conn_account.Open();
                String SQL = "SELECT Balance FROM Account WHERE AccID = "+_id+"; ";

                SqlCommand sqlComm = new SqlCommand();
                SqlDataReader sd;

                sqlComm.CommandText = SQL;

                sqlComm.Connection = conn_account;

                
                sd = sqlComm.ExecuteReader();
                while(sd.Read())
                {
                    result = int.Parse(sd["Balance"].ToString());
                }
                conn_account.Close();
                return result;
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                return result;
            }
            finally
            {
            }
        }

        public bool InputMoney(int _id, int _money)
        {
            try
            {
                conn_account = new SqlConnection();
                conn_account.ConnectionString = @"Server=USER-PC;database=ccm;uid=ccm;pwd=ccm;";
                conn_account.Open();
                String SQL = "UPDATE Account SET Balance = "+ _money + " + (SELECT Balance FROM Account WHERE AccID = "+_id+"), Date = GETDATE() WHERE AccID = "+_id+"; ";

                SqlCommand sqlComm = new SqlCommand();
                SqlDataReader sd;

                sqlComm.CommandText = SQL;

                sqlComm.Connection = conn_account;
       

                sd = sqlComm.ExecuteReader();
                conn_account.Close();
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
        public bool OutputMoney(int _id, int _money)
        {
            try
            {
                conn_account = new SqlConnection();
                conn_account.ConnectionString = @"Server=USER-PC;database=ccm;uid=ccm;pwd=ccm;";
                conn_account.Open();
                String SQL = "UPDATE Account SET Balance = " + _money + " - (SELECT Balance FROM Account WHERE AccID = " + _id + "), Date = GETDATE() WHERE AccID = " + _id + "; ";

                SqlCommand sqlComm = new SqlCommand();
                SqlDataReader sd;

                sqlComm.CommandText = SQL;

                sqlComm.Connection = conn_account;


                sd = sqlComm.ExecuteReader();
                conn_account.Close();
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

        public Account SelectAccount(int _id)
        {
            try
            {
                conn_account = new SqlConnection();
                conn_account.ConnectionString = @"Server=USER-PC;database=ccm;uid=ccm;pwd=ccm;";
                conn_account.Open();
                String SQL = "SELECT * FROM Account WHERE AccID = "+ _id + "; ";

                SqlCommand sqlComm = new SqlCommand();
                SqlDataReader sd;

                sqlComm.CommandText = SQL;

                sqlComm.Connection = conn_account;

                Account result = new Account();

                sd = sqlComm.ExecuteReader();
                while(sd.Read())
                {
                    result.Id = int.Parse(sd["AccID"].ToString());
                    result.AccountName=sd["Name"].ToString();
                    result.Balance = int.Parse(sd["Balance"].ToString());
                    result.CreateDate = DateTime.Parse(sd["Date"].ToString());
                    
                }
                conn_account.Close();
                return result;
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

        public List<Account> selectAllAccount()
        {
            List<Account> result = new List<Account>();

            conn_account = new SqlConnection();
            conn_account.ConnectionString = @"Server=USER-PC;database=ccm;uid=ccm;pwd=ccm;";
            conn_account.Open();
            String SQL = "SELECT * FROM Account; ";

            SqlCommand sqlComm = new SqlCommand();
            SqlDataReader sd;

            sqlComm.CommandText = SQL;

            sqlComm.Connection = conn_account;


            Account temp;
            sd = sqlComm.ExecuteReader();
            while (sd.Read())
            {
                temp = new Account();
                temp.Id = int.Parse(sd["AccID"].ToString());
                temp.AccountName = sd["Name"].ToString();
                temp.Balance = int.Parse(sd["Balance"].ToString());
                temp.CreateDate = DateTime.Parse(sd["Date"].ToString());
                result.Add(temp);
            }
            conn_account.Close();


            return result;
        }

        public DataTable SelectAllAccount1()
        {
            return null;
        }

        #endregion

    }
}
