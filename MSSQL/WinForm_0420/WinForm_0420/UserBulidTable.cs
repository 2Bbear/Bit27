using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WinForm_0420
{
    public class UserBulidTable
    {
        #region SingleTone
        public static UserBulidTable singleTone;
        public static UserBulidTable SingleTone { get => singleTone; private set => singleTone = value; }
        static UserBulidTable()
        {
            SingleTone = new UserBulidTable();
        }
        private UserBulidTable()
        {

        }
        #endregion


        #region Method

        public static void DesingTable(DataTable dt)
        {
            try
            {
                //Member ID
                DataColumn dc_MemberID = new DataColumn("MemberID", typeof(int));
                dc_MemberID.AutoIncrement = true;
                //dc_MemberID.Unique = true;
                dc_MemberID.AllowDBNull = false;
                dt.Columns.Add(dc_MemberID);
                //Name_string
                DataColumn dc_Name = new DataColumn();
                dc_Name.ColumnName = "Name";
                dc_Name.DataType = typeof(string);
                dc_Name.AllowDBNull = false;
                dt.Columns.Add(dc_Name);

                //HOMERUN
                DataColumn dc_HomeRune = new DataColumn("HOMERUN", typeof(int));
                dc_HomeRune.Unique = false;
                dc_HomeRune.AllowDBNull = false;
                dt.Columns.Add(dc_HomeRune);
                //Hit3
                DataColumn dc_Hit3 = new DataColumn("HIT3", typeof(int));
                dc_Hit3.Unique = false;
                dc_Hit3.AllowDBNull = false;
                dt.Columns.Add(dc_Hit3);
                //Hit2
                DataColumn dc_Hit2 = new DataColumn("HIT2", typeof(int));
                dc_Hit2.Unique = false;
                dc_Hit2.AllowDBNull = false;
                dt.Columns.Add(dc_Hit2);
                //Hit1
                DataColumn dc_Hit1 = new DataColumn("HIT1", typeof(int));
                dc_Hit1.Unique = false;
                dc_Hit1.AllowDBNull = false;
                dt.Columns.Add(dc_Hit1);
                //OUT
                DataColumn dc_Out = new DataColumn("OUT", typeof(int));
                dc_Out.Unique = false;
                dc_Out.AllowDBNull = false;
                dt.Columns.Add(dc_Out);
                //Average_float
                DataColumn dc_Average = new DataColumn("AVERAGE", typeof(float));
                dc_Average.Unique = false;
                dc_Average.AllowDBNull = false;
                dt.Columns.Add(dc_Average);
                //Hitcount
                DataColumn dc_HitCount = new DataColumn("HITCOUNT", typeof(int));
                dc_HitCount.Unique = false;
                dc_HitCount.AllowDBNull = false;
                dt.Columns.Add(dc_HitCount);
                //Totalcount
                DataColumn dc_TotalCount = new DataColumn("TOTALCOUNT", typeof(int));
                dc_TotalCount.Unique = false;
                dc_TotalCount.AllowDBNull = false;
                dt.Columns.Add(dc_TotalCount);

                DataColumn[] pkeys = new DataColumn[1];
                pkeys[0] = dc_MemberID;
                dt.PrimaryKey = pkeys;
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
            finally
            {
            }
            
        }
        public static void AddTableColum2(DataTable dt,String _name,int homerun,int hit3,int hit2,int hit1,
            int outnum)
        {
            try
            {
                DataRow dr = dt.NewRow();
                dr["Name"] = _name;
                dr["HOMERUN"] = homerun;
                dr["HIT3"] = hit3;
                dr["HIT2"] = hit2;
                dr["HIT1"] = hit1;
                dr["OUT"] = outnum;
                dr["AVERAGE"] = (hit1+hit2+hit3+homerun)/ (hit1 + hit2 + hit3 + homerun+outnum*1.0f);
                dr["HITCOUNT"] = (hit1 + hit2 + hit3 + homerun);
                dr["TOTALCOUNT"] = (hit1 + hit2 + hit3 + homerun + outnum);

                dt.Rows.Add(dr);
            }
            catch (Exception e)
            {
               
            }
        }

        public static void AddTableColum(DataTable dt, String _tablename,String _columname,String _columtype,bool isnull,bool ispramarykey,bool isautoinreament)
        {
            //Add new Colum
            DataColumn dc_newcolum=null;
            if(_columtype.Equals("string"))
            {
                dc_newcolum = new DataColumn(_columname, typeof(string));
            }
            else if (_columtype.Equals("int"))
            {
                dc_newcolum = new DataColumn(_columname, typeof(int));
            }
            else if (_columtype.Equals("float"))
            {
                dc_newcolum = new DataColumn(_columname, typeof(float));
            }

            dc_newcolum.AutoIncrement = isautoinreament;
            dc_newcolum.Unique = ispramarykey;
            dc_newcolum.AllowDBNull = isnull;
            dt.Columns.Add(dc_newcolum);

            if(ispramarykey)
            {
                DataColumn[] pkeys = new DataColumn[1];
                pkeys[0] = dc_newcolum;
                dt.PrimaryKey = pkeys;

            }
        }
        public static List<String> ViewAll(DataTable dt,out string t_name,out int ccount)
        {
            List<String> list = new List<string>();

            t_name = dt.TableName;
            ccount = dt.Columns.Count;

            foreach(DataColumn dc in dt.Columns)
            {
                string temp = dc.ColumnName + ":" + dc.DataType;
                list.Add(temp);
            }

            return list;
        }

        

        #endregion


    }
}
