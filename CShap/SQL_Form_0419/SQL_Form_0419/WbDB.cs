using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Data;
using System.Data.SqlClient;
namespace wb.lib
{
    public class WbDB
    {
        private SqlConnection conn = new SqlConnection();
        public WbDB()
        {
          
        }

        #region Method
        //선수추가/ t삭제
        public bool MemberJoin(String _str,bool _b)
        {
            SqlCommand command=null;
            if (_b)
            {
                string comtext = "insert into Member values (@Name, 0,0,0,0,0,0,0,0);";
                //string comtext = "insert into wm27 values (@Name, @HOMERUN,@HIT3,@HIT2,@HIT1,@OUT,@AVERAGE,@HITCOUNT,@TOTALCOUNT);";

                command = new SqlCommand(comtext, conn);


                SqlParameter param_name = new SqlParameter("@Name", _str);
                command.Parameters.Add(param_name);

                #region name
                //SqlParameter param_homerun = new SqlParameter("@HOMERUN", 0);
                //param_homerun.SqlDbType = System.Data.SqlDbType.Int;
                //command.Parameters.Add(param_homerun);

                //SqlParameter param_hit3 = new SqlParameter("@HIT3", 0);
                //param_hit3.SqlDbType = System.Data.SqlDbType.Int;
                //command.Parameters.Add(param_hit3);

                //SqlParameter param_hit2 = new SqlParameter("@HIT2", 0);
                //param_hit2.SqlDbType = System.Data.SqlDbType.Int;
                //command.Parameters.Add(param_hit2);

                //SqlParameter param_hit1 = new SqlParameter("@HIT1", 0);
                //param_hit1.SqlDbType = System.Data.SqlDbType.Int;
                //command.Parameters.Add(param_hit1);

                //SqlParameter param_out = new SqlParameter("@OUT", 0);
                //param_out.SqlDbType = System.Data.SqlDbType.Int;
                //command.Parameters.Add(param_out);

                //SqlParameter param_average = new SqlParameter("@AVERAGE", 0);
                //param_average.SqlDbType = System.Data.SqlDbType.Float;
                //command.Parameters.Add(param_average);

                //SqlParameter param_hitcount = new SqlParameter("@HITCOUNT", 0);
                //param_hitcount.SqlDbType = System.Data.SqlDbType.Int;
                //command.Parameters.Add(param_hitcount);

                //SqlParameter param_totalcount = new SqlParameter("@TOTALCOUNT", 0);
                //param_totalcount.SqlDbType = System.Data.SqlDbType.Int;
                //command.Parameters.Add(param_totalcount);
                #endregion

            }
            else
            {
                string comtext = "DELETE Member WHERE (Name = @Name)";

                command = new SqlCommand(comtext, conn);

                SqlParameter param_title = new SqlParameter("@Name", _str);
                command.Parameters.Add(param_title);

            }
            


            if (command.ExecuteNonQuery() == 1)
            {
                
                return true;
            }
            else
            {
               
                return false;
            }
        }

        //불러오기
        public int MemberCount()
        {
            int result = 0;

            string comtext = "Select count(Name) from Member;";

            SqlCommand command = new SqlCommand(comtext, conn);

            result = (int)command.ExecuteScalar();
            

            return result;
        }
        //이름 리스트 받아오기
        public List<String> MemberNameList()
        {
            List<String> result = new List<String>();
            string comtext = "select Name from Member;";
            SqlCommand command = new SqlCommand(comtext, conn);
            SqlDataReader reader = command.ExecuteReader();
            while (reader.Read())
            {
                result.Add(String.Format("{0}",reader["Name"]));
            }


            return result;
        }
        //DB에 결과 저장하기
        public bool InsertData(String _name,int _reuslt)
        {
            string comtext = "Select MemberID from Member where Name=@Name;";
            SqlCommand command = new SqlCommand(comtext, conn);

            SqlParameter param_name = new SqlParameter("@Name", _name);
            command.Parameters.Add(param_name);

            String targetID = (String)command.ExecuteScalar();
            //================================================================================
            string comtext2 = "insert into BaseBall values(@MEMID,@TYPEID);";
            SqlCommand command2 = new SqlCommand(comtext2, conn);

            SqlParameter param_memid = new SqlParameter("@MEMID", targetID);
            param_memid.SqlDbType = System.Data.SqlDbType.Int;
            command2.Parameters.Add(param_name);


            SqlParameter param_typeid = new SqlParameter("@TYPEID", targetID);
            param_typeid.SqlDbType = System.Data.SqlDbType.Int;
            command2.Parameters.Add(param_typeid);



            return true;


        }

        public bool MemberUpdate(string name, int result)
        {
            string comtext="";
            if(result == 1)
            {
                comtext = "UPDATE Member SET HOMERUN=HOMERUN +VALUE @VALUE WHERE(Name=@Name)";
            }
            else if(result==2)
            {
                comtext = "UPDATE Member SET HIT3=HIT3+@VALUE WHERE(Name=@Name)";
            }
            else if (result == 3)
            {
                comtext = "UPDATE Member SET HIT2=HIT2+@VALUE WHERE(Name=@Name)";
            }
            else if (result == 4)
            {
                comtext = "UPDATE Member SET HIT1=HIT1+@VALUE WHERE(Name=@Name)";
            }
            else if (result == 5)
            {
                comtext = "UPDATE Member SET OUT=OUT+@VALUE WHERE(Name=@Name)";
            }
           

            SqlCommand command = new SqlCommand(comtext, conn);

            SqlParameter param_price = new SqlParameter("@VALUE", 1);
            param_price.SqlDbType = System.Data.SqlDbType.Int;
            command.Parameters.Add(param_price);


            SqlParameter param_title = new SqlParameter("@Name", name);
            command.Parameters.Add(param_title);


            if (command.ExecuteNonQuery() == 1)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        public bool Open()
        {
            try
            {
                conn.ConnectionString = @"Server=192.168.0.52;database=
                                   wb27;uid=ccm;pwd=ccm;";
                conn.Open();

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

        public bool Close()
        {
            if (conn != null)
            {
                conn.Close();       //  연결 해제
                Console.WriteLine("데이터베이스 연결 해제");
                return true;
            }
            return false;
        }
        #endregion

    }
}
