
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;


public class Emp_Manage
{

    #region Attribute
    private static Emp_Manage me;
    private List<Employee> emp_list;

    #endregion

    #region Property
    public List<Employee> Emp_list { get => emp_list; set => emp_list = value; }
    #endregion

    #region Constructor
    public Emp_Manage()
    {
        emp_list = new List<Employee>();
    }

    
    #endregion

    #region Method
  
    public static Emp_Manage GetInstance()
    {
        if(me==null)
        {
            me = new Emp_Manage();
            me.Initdata();
        }
        return me;
    }
    public void Initdata()
    {
        // TODO implement here
        emp_list.Add(new Emp_Parttime("jjh", "2018/04/11", 1, 7530));
        emp_list.Add(new Emp_General("ddf", "2018/03/11", 2, 300000));
        emp_list.Add(new Emp_Salary("kgf", "2018/01/11", 3,30000,0.4));
    }

    #endregion

}