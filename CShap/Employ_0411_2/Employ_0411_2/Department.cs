
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;


public class Department
{
    #region Attribute
    public int emp_id;
    public string dept_name;
    public string dept_local;

    #endregion

    #region Constructor
    public Department(int emp_id, string dept_name, string dept_local)
    {
        this.emp_id = emp_id;
        this.dept_name = dept_name;
        this.dept_local = dept_local;
    }


    #endregion

    #region Override
    public override string ToString()
    {
        String result="";

        result += String.Format("[부서 번호]:{0} [부서명]:{1} [지역]:{2}",emp_id,dept_name, dept_local);

        return result;
    }
    #endregion


}

