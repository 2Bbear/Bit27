
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;


public class Emp_General : Employee
{
    #region Attribute
    public double salary;

    #endregion

    #region Constructor
    public Emp_General(string name, string date, int dept_id,double _salary) : base(name, date, dept_id)
    {
        salary = _salary;
    }
    #endregion







}