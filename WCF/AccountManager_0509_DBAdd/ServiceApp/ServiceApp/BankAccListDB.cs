using System;
using System.Collections.Generic;
using System.Data;
using System.Data.SqlClient;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ServiceApp
{
    class BankAccListDB
    {
        #region 싱글톤
        public static BankAccListDB Singletone
        {
            get;
            set;
        }
        SqlConnection conn_account;
        static BankAccListDB() { Singletone = new BankAccListDB(); }
        private BankAccListDB() { }

        #endregion
       
        #region Method
        public bool InsertAccList(AccList _acclist)
        {
            try
            {
                conn_account = new SqlConnection();
                conn_account.ConnectionString = @"Server=USER-PC;database=ccm;uid=ccm;pwd=ccm;";
                conn_account.Open();
                String SQL2 = "INSERT INTO AccList VALUES(" + _acclist.accID + ","+ _acclist.inputMoney + ","+ _acclist .outputMoney+ "," + _acclist.balance + ",GETDATE()); ";
                //String SQL2 = "INSERT INTO AccList VALUES(" + _acclist.accID + "," + _acclist.inputMoney + "," + _acclist.outputMoney + "," + _acclist.balance + ","+_acclist.date.ToString() +"); ";
                SqlCommand sqlComm2 = new SqlCommand();
                SqlDataReader sd2;

                sqlComm2.CommandText = SQL2;

                sqlComm2.Connection = conn_account;

                sd2 = sqlComm2.ExecuteReader();
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
        public bool DeleteAllAccList(int _id)
        {
            try
            {
                conn_account = new SqlConnection();
                conn_account.ConnectionString = @"Server=USER-PC;database=ccm;uid=ccm;pwd=ccm;";
                conn_account.Open();
                String SQL = "DELETE FROM AccList WHERE AccID = " + _id + "; ";

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
        public List<AccList> SelectAccountList(int _id)
        {
            List<AccList> result = new List<AccList>();
            try
            {
                conn_account = new SqlConnection();
                conn_account.ConnectionString = @"Server=USER-PC;database=ccm;uid=ccm;pwd=ccm;";
                conn_account.Open();
                String SQL = "SELECT * FROM AccList WHERE AccID="+_id+";";

                SqlCommand sqlComm = new SqlCommand();
                SqlDataReader sd;

                sqlComm.CommandText = SQL;

                sqlComm.Connection = conn_account;

                sd = sqlComm.ExecuteReader();
                while(sd.Read())
                {
                    result.Add(new AccList
                    {
                        accListID = int.Parse(sd["AccListID"].ToString()),
                        accID = int.Parse(sd["AccID"].ToString()),
                        balance = int.Parse(sd["Balance"].ToString()),
                        date = DateTime.Parse(sd["Date"].ToString()),
                        inputMoney = int.Parse(sd["IntputMoney"].ToString()),
                        outputMoney = int.Parse(sd["OutputMoney"].ToString())
                    });

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
        public DataTable SelectAccountList1(int _id)
        {
            return null;
        }
        #endregion

    }
}
