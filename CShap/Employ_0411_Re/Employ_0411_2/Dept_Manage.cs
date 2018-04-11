
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;


public class Dept_Manage
{


    #region Attribute
    private static Dept_Manage me;
    private  List<Department> dept_list;

    #endregion

    #region Property
    public List<Department> Dept_list { get => dept_list; private set => dept_list = value; }

    #endregion

    #region Constructor
    private Dept_Manage()
    {
        dept_list = new List<Department>();
    }


    #endregion

    #region Method
    //검색 메소드 return idx
    public int SearchListAttribute_int(int _departmentId)
    {
        for (int i = 0; i < dept_list.Count; i++)
        {
            if (dept_list[i].emp_id == _departmentId)
            {
                return i;
            }
        }
        return -1;
    }
    //출력 return string
    public String GetListAttributeInfo(int _idx)
    {
        String result="";

        result += dept_list[_idx].ToString();

        return result;
    }
    public static Dept_Manage GetInstance()
    {
        if (me == null)
        {
            me = new Dept_Manage();
            me.Initdata();


        }
        return me;
    }
 
    public void Initdata()
    {
        // TODO implement here
        dept_list.Add(new Department(1, "야놀자부", "속초"));
        dept_list.Add(new Department(2, "게임부", "서울"));
        dept_list.Add(new Department(3, "경영부", "인천"));
    }

    #endregion

    #region Override
    public override String ToString()
    {
        String result="";
        for(int i =0; i< dept_list.Count; i++)
        {
            result += dept_list[i].ToString();
            result += "\n";
        }

        return result;
    }
    #endregion
}