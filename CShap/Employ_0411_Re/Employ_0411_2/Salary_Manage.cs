
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;



public class Salary_Manage {


    #region Attribute
    public static Salary_Manage me;
    private List<SalaryGrade> salary_list;
    #endregion

    #region Property
    public List<SalaryGrade> Salary_list { get => salary_list; private set => salary_list = value; }
    #endregion

    #region Constructor
    private Salary_Manage()
    {
        salary_list = new List<SalaryGrade>();
    }

    
    #endregion

    #region Method
    public static Salary_Manage GetInstance()
    {
        if (me == null)
        {
            me = new Salary_Manage();
            me.Initdata();
        }
        return me;
    }
    public void Initdata()
    {
        // TODO implement here
        salary_list.Add(new SalaryGrade(0, 200000, 999999999));
        salary_list.Add(new SalaryGrade(1,200000,250000));
        salary_list.Add(new SalaryGrade(2, 100000, 200000));
        salary_list.Add(new SalaryGrade(3, 0, 100000));

    }
    #endregion













}