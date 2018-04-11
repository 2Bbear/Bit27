using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;


public class Emp_Salary : Emp_General
{
    #region Attribute
    public double incentive;
    #endregion

    #region Constructor
    public Emp_Salary(string name, string date, int dept_id, double _salary, double _incentive) : base(name, date, dept_id, _salary)
    {
        incentive = _incentive;
    }
    #endregion


    

    
}

