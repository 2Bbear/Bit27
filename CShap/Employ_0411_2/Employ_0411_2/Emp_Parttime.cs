
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;


public class Emp_Parttime : Employee
{

    #region Attribute
    public int w_time;
    public int t_salary;
    #endregion

    #region Constructor
    public Emp_Parttime(string name, string date, int dept_id,int _t_salary) : base(name, date, dept_id)
    {
        w_time = 1;
        t_salary = _t_salary;
    }
    #endregion

    

   
}

