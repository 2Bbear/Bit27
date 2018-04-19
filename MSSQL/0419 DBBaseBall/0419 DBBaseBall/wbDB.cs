using System;
using System.Collections.Generic;
using System.Data.SqlClient;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using _0419_DBBaseBall;
using System.Windows.Forms;
namespace wb.lib
{
    public class wbDB
    {
        Form1 form;
        private SqlConnection conn = new SqlConnection();

        public wbDB()
        {
            //Open();
        }

        public bool Open()
        {
            try
            {
                conn.ConnectionString = @"Server=USER-PC;database=
                                   wb27;uid=ccm;pwd=ccm;";
                conn.Open();    //  데이터베이스 연결
                return true;
            }
            catch (Exception)
            {
                return false;
            }
        }

        public void Close()
        {
            if (conn != null)
                conn.Close();
        }

        public bool MemberJoin(string name, bool check)
        {
            if (check)
            {
                string comtext = "insert into Member values (@Name, 0,0,0,0,0,0,0,0)";

                SqlCommand command = new SqlCommand(comtext, conn);

                SqlParameter param_name = new SqlParameter("@Name", name);
                command.Parameters.Add(param_name);

                return ExcuteCommand(command);
            }
            else
            {
                string comtext = "delete from Member where (Name = @Name)";

                SqlCommand command = new SqlCommand(comtext, conn);

                SqlParameter param_name = new SqlParameter("@Name", name);
                command.Parameters.Add(param_name);

                return ExcuteCommand(command);
            }
        }


        public void ListViewPrint(String _str, Form1 _form)
        {
            String str = _str.ToString();
            
            MessageBox.Show(str);
            form = _form;
            List<string> list = new List<string>();
            string comtext;
            SqlParameter param_name;
            try
            {
                
                if (_str.Equals("HOMERUN"))
                {
                    MessageBox.Show("dad6");
                    comtext = "Select * from Member order by HOMERUN DESC ;";
                    param_name = new SqlParameter("@STR", str);

                }
                else if (str.Equals("HIT3"))
                {
                    comtext = "Select * from Member order by HIT3 DESC ;";
                    param_name = new SqlParameter("@STR", str);
                }
                else if (str.Equals("HIT2"))
                {
                    comtext = "Select * from Member order by HIT2 DESC ;";
                    param_name = new SqlParameter("@STR", str);
                }
                else if (str.Equals("HIT1"))
                {
                    comtext = "Select * from Member order by HIT1 DESC ;";
                    param_name = new SqlParameter("@STR", str);
                }
                else
                {
                    
                    comtext = "Select * from Member order by @STR DESC ;";
                    param_name = new SqlParameter("@STR", str);
                }
                //comtext = "Select * from Member order by HIT3 DESC ;";
                SqlCommand command = new SqlCommand(comtext, conn);
                command.Parameters.Add(param_name);

                
                SqlDataReader reader = command.ExecuteReader();
                int i = 0;
                while (reader.Read())
                {
                    //list.Add(reader[0].ToString());
                    //string[] sentence = reader[0].ToString().Split(' ');
                    
                    ListViewItem item = new ListViewItem(reader[1].ToString());
                    item.SubItems.Add(reader[2].ToString());
                    item.SubItems.Add(reader[3].ToString());
                    item.SubItems.Add(reader[4].ToString());
                    item.SubItems.Add(reader[5].ToString());
                    item.SubItems.Add(reader[6].ToString());
                    item.SubItems.Add(reader[7].ToString());
                    
                    form.listView1.Items.Add(item);
                    //form.listView1.Items[i].SubItems[0].Text = reader[1].ToString();
                    //form.listView1.Items[i].SubItems[1].Text = reader[2].ToString();
                    //form.listView1.Items[i].SubItems[2].Text = reader[3].ToString();
                    //form.listView1.Items[i].SubItems[3].Text = reader[4].ToString();
                    //form.listView1.Items[i].SubItems[4].Text = reader[5].ToString();
                    //form.listView1.Items[i].SubItems[5].Text = reader[6].ToString();
                    //form.listView1.Items[i].SubItems[6].Text = reader[7].ToString();
                    i++;
                  

                   
                }
                reader.Close();
                MessageBox.Show("고오오류");
            }
            catch (Exception)
            {
                MessageBox.Show("멍청이");
                return;
            }
        }
        public int MemberCount()
        {
            try
            {
                string comtext = "Select  count(*)  from Member;";

                SqlCommand command = new SqlCommand(comtext, conn);
                int count = (int)command.ExecuteScalar();
                return count;
            }
            catch (Exception)
            {
                return -1;
            }
        }

        public List<string> MemberNameList()
        {
            try
            {
                List<string> namelist = new List<string>();

                string comtext = "Select Name From Member";
                SqlCommand command = new SqlCommand(comtext, conn);

                SqlDataReader reader = command.ExecuteReader();
                while (reader.Read())
                {
                    namelist.Add(reader[0].ToString());
                }
                reader.Close();

                return namelist;
            }
            catch (Exception)
            {
                return null;
            }
        }

        public bool InsertData(string name, int result)
        {
            try
            {
                string comtext = "select MemberID from Member where Name=@Name";

                SqlCommand command = new SqlCommand(comtext, conn);

                SqlParameter param_name = new SqlParameter("@Name", name);
                command.Parameters.Add(param_name);

                int mem_id = (int)command.ExecuteScalar();
                //=============================================

                string comtext1 = "insert into BaseBall values (@MEMID, @TYPEID)";

                SqlCommand command1 = new SqlCommand(comtext1, conn);

                SqlParameter param_memid = new SqlParameter("@MEMID", mem_id);
                param_memid.SqlDbType = System.Data.SqlDbType.Int;
                command1.Parameters.Add(param_memid);

                SqlParameter param_typeid = new SqlParameter("@TYPEID", result);
                param_typeid.SqlDbType = System.Data.SqlDbType.Int;
                command1.Parameters.Add(param_typeid);

                return ExcuteCommand(command);

            }
            catch (Exception)
            {
                return false;
            }
        }

        public bool MemberUpdate(string name, int result)
        {
            try
            {
                string comtext = "";
                if (result == 1)
                    comtext = "update Member set HOMERUN = HOMERUN + @VALUE WHERE (Name = @Name)";
                else if (result == 2)
                    comtext = "update Member set HIT3 = HIT3 + @VALUE WHERE (Name = @Name)";
                else if (result == 3)
                    comtext = "update Member set HIT2 = HIT2 + @VALUE WHERE (Name = @Name)";
                else if (result == 4)
                    comtext = "update Member set HIT1 = HIT1 + @VALUE WHERE (Name = @Name)";
                else
                    comtext = "update Member set OUT = OUT + @VALUE WHERE (Name = @Name)";


                SqlCommand command = new SqlCommand(comtext, conn);

                SqlParameter param_price = new SqlParameter("@VALUE", 1);
                param_price.SqlDbType = System.Data.SqlDbType.Int;
                command.Parameters.Add(param_price);

                SqlParameter param_name = new SqlParameter("@Name", name);
                command.Parameters.Add(param_name);

                return ExcuteCommand(command);

            }
            catch (Exception)
            {
                return false;
            }
        }

        private bool ExcuteCommand(SqlCommand command)
        {
            try
            {
                if (command.ExecuteNonQuery() == 1)
                    return true;
                else
                    return false;
            }
            catch (Exception)
            {
                return false;
            }
        }



    }
}
