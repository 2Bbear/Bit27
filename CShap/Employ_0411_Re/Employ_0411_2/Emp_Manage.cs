
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
    //생성 메소드
    public void AddListAttribute(Employee _attri)
    {
        emp_list.Add(_attri);
    }
    //삭제 메소드
    public void DeleteListAttribute(int _idx)
    {
        emp_list.RemoveAt(_idx);
    }
    //수정 메소드
    public void ModifyListAttribute(int _idx,Employee _change)
    {
        emp_list[_idx] = _change;
    }
    //검색 메소드 return instance
    public Employee SearchListAttribute_instance(int _employeeId)
    {
        foreach(Employee t in emp_list)
        {
            if(t.Emp_id== _employeeId)
            {
                return t;
            }
        }
        return null;
    }
    //검색 메소드 return idx
    public int SearchListAttribute_int(int _employeeId)
    {
        for(int i =0;i<emp_list.Count ;i++)
        { 
            if (emp_list[i].Emp_id == _employeeId)
            {
                return i;
            }
        }
        return -1;
    }
    //출력 메소드 return string
    public String GetListAttributeInfo(int _idx)
    {
        string result = "";
        result += emp_list[_idx].ToString();
        return result;
    }
    public static Emp_Manage GetInstance()
    {
        if(me==null)
        {
            me = new Emp_Manage();
            me.Initdata();
        }
        return me;
    }
    //초기화 메소드
    public void Initdata()
    {
        // TODO implement here
        emp_list.Add(new Emp_Parttime("jjh", "2018/04/11", 1, 7530));
        emp_list.Add(new Emp_General("ddf", "2018/03/11", 2, 300000));
        emp_list.Add(new Emp_Salary("kgf", "2018/01/11", 3,30000,0.4));
    }

    #endregion

}