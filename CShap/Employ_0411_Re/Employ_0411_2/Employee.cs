
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;


public abstract class Employee
{

    #region Attribute
    private string name;
    private string date;
    private int dept_id;
    private static int id;
    private  int emp_id;
    #endregion

    #region Property
    public string Name { get => name; set => name = value; }
    public string Date { get => date; set => date = value; }
    public int Dept_id { get => dept_id; set => dept_id = value; }
    public int Emp_id { get => emp_id; set => emp_id = value; }
    #endregion

    #region Constructor
    public Employee(string name, string date, int dept_id)
    {
        this.Name = name;
        this.Date = date;
        this.Dept_id = dept_id;
        emp_id = id;
        id += 1;
    }
    static Employee()
    {
        id = 1000;
    }


    #endregion

    #region Override
    public override string ToString()
    {
        String result="";
        result = String.Format("[id]{0}\t[이름]{1}\t[부서id]{2}\t[입사일]{3}", emp_id, name, dept_id, date);
        return result;
    }
    #endregion



}