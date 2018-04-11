
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;


public class Control {

    public Control()
    {
    }


    public void emp_Insert() {
        // TODO implement here
        Emp_Manage em = Emp_Manage.GetInstance();
        Dept_Manage dm = Dept_Manage.GetInstance();

        string name;
        string date;
        int departmentId;

        int emp_select;
        Console.WriteLine("===================================");
        Console.Write("[이름] : ");
        name = Console.ReadLine();
        Console.Write("[입사일] : ");
        date = Console.ReadLine();
        Console.WriteLine("[부서] 부서 번호를 선택 해주세요 ");
        Console.Write(dm.ToString());
        departmentId = int.Parse(Console.ReadLine());
        Console.WriteLine("[사원종류] 1. 영업사원 2. 일반사원 3.파트타임 ");
        emp_select= int.Parse(Console.ReadLine());
        Console.WriteLine("===================================");
        //사원 저장
        switch (emp_select)
        {
            case 1:
                {
                    double sal;
                    double incentive;
                    Console.Write("[월급] : ");
                    sal = double.Parse(Console.ReadLine());
                    Console.Write("[인센티브] : ");
                    incentive = double.Parse(Console.ReadLine());
                   // em.Emp_list.Add(new Emp_Salary(name, date, departmentId, sal, incentive));
                    em.AddListAttribute(new Emp_Salary(name, date, departmentId, sal, incentive));
                    break;
                }
            case 2:
                {
                    double sal;
                    Console.Write("[월급] : ");
                    sal = double.Parse(Console.ReadLine());
                   // em.Emp_list.Add(new Emp_General(name, date, departmentId, sal));
                    em.AddListAttribute(new Emp_General(name, date, departmentId, sal));
                    break;
                }
            case 3:
                {
                    int timesal;
                    Console.Write("[시급] : ");
                    timesal = int.Parse(Console.ReadLine());
                    //em.Emp_list.Add(new Emp_Parttime(name, date, departmentId, timesal));
                    em.AddListAttribute(new Emp_Parttime(name, date, departmentId, timesal));
                    break;
                }
            default:
                {
                    break;
                } 
        }
        Console.WriteLine("사원 등록 성공");
        Console.ReadLine();

    }
    public void emp_Search()
    {
        // TODO implement here
        Emp_Manage em = Emp_Manage.GetInstance();

        Dept_Manage dm = Dept_Manage.GetInstance();

        

        int target_id;

        //입력받기
        Console.Write("찾을 사원ID를 입력해주세요");
        target_id = int.Parse(Console.ReadLine());

        //찾기
        int idx=FindIdx(target_id);

        //출력하기
        //사원 정보
        Console.WriteLine(PrintEmployeeInfo(em.Emp_list[idx]));
        //부서 정보
        Console.WriteLine(PrintDepartmentInfo(em.Emp_list[idx].Dept_id));
        //급여 등급
        Console.WriteLine(PrintGradeInfo(em.Emp_list[idx]));

        Console.ReadLine();

    }
    private String PrintEmployeeInfo(Employee _target)
    {
        string result = "";

        if(_target is Emp_Salary)//영업직
        {
            result += ((Emp_Salary)_target).ToString();
        }
        else if(_target is Emp_General )//일반직
        {
            if (!(_target is Emp_Salary))
            {
                result += ((Emp_General)_target).ToString();
            }
                
        }
        else if (_target is Emp_Parttime )//파트타임근무
        {
            result += ((Emp_Parttime)_target).ToString();
        }
        else
        {
            Console.WriteLine("응");
        }



        return result;
    }
    private String PrintDepartmentInfo(int _depIdx)
    {
        String result = "";
        Dept_Manage dm = Dept_Manage.GetInstance();
       
        for (int i = 0; i < dm.Dept_list.Count; i++)
        {
            if (dm.Dept_list[i].emp_id == _depIdx)
            {
                result += dm.Dept_list[i].ToString();
            }
        }

        return result;
    }
    private String PrintGradeInfo(Employee _target)
    {
        Salary_Manage sm = Salary_Manage.GetInstance();

        String result = "";
        double targetSal = 0d;
        if (_target is Emp_Salary)//영업직
        {
            targetSal = ((Emp_Salary)_target).salary;
            

        }
        else if (_target is Emp_General)//일반직
        {
            if(!(_target is Emp_Salary))
            {
                targetSal = ((Emp_General)_target).salary;
            }
            
        }
        else if (_target is Emp_Parttime)//파트타임근무
        {
            targetSal=((Emp_Parttime)_target).t_salary* ((Emp_Parttime)_target).w_time;
          
        }
        else
        {
            Console.WriteLine("응????");
        }
        
        foreach (SalaryGrade t in sm.Salary_list)
        {
            if(t.losal< targetSal && targetSal< t.hisal)
            { 
                //result += t.ToString();
                return t.ToString();
            }
            
        }

        return result;

    }
    private int FindIdx(int _emp_id)
    {
        Emp_Manage em = Emp_Manage.GetInstance();

        int result = -1;

        for(int i =0;i< em.Emp_list.Count; i++)
        {
            if (em.Emp_list[i].Emp_id== _emp_id)
            {
                return i;
            }
        }
 
        return result;
    }


    public void emp_Change()
    {
        // TODO implement here
        Emp_Manage em = Emp_Manage.GetInstance();

        int target_id;
        Console.Write("사원 id를 입력 해주세요");
        target_id = int.Parse(Console.ReadLine());

        int idx = FindIdx(target_id);
        
        //========================================================
        if (em.Emp_list[idx] is Emp_Salary)//영업직
        {
            double ch_sal=0d;
            double ch_incen = 0d;
            Console.Write("급여 수정");
            ch_sal = double.Parse(Console.ReadLine());
            Console.Write("성과급 수정");
            ch_incen = double.Parse(Console.ReadLine());

            ((Emp_Salary)em.Emp_list[idx]).salary = ch_sal;
            ((Emp_Salary)em.Emp_list[idx]).incentive=ch_incen;

        }
        else if (em.Emp_list[idx] is Emp_General)//일반직
        {
            if (!(em.Emp_list[idx] is Emp_Salary))//영업직 일경우 제외
            {
                double ch_sal = 0d;

                Console.Write("급여 수정");
                ch_sal = double.Parse(Console.ReadLine());
                ((Emp_General)em.Emp_list[idx]).salary= ch_sal;
            }

        }
        else if (em.Emp_list[idx] is Emp_Parttime)//파트타임근무
        {
            int ch_wtimel = 0;
            int ch_tsal = 0;
            Console.Write("일한 시간 수정");
            ch_wtimel = int.Parse(Console.ReadLine());
            Console.Write("시급 수정");
            ch_tsal = int.Parse(Console.ReadLine());

            ((Emp_Parttime)em.Emp_list[idx]).w_time = ch_wtimel;
            ((Emp_Parttime)em.Emp_list[idx]).t_salary = ch_tsal;

        }
        else
        {
            Console.WriteLine("응????");
        }

        //===============================================================

        //대기
        Console.WriteLine("수정 완료");
        Console.ReadLine();
    }

    
    public void emp_Delete() {
        // TODO implement here
        // TODO implement here
        Emp_Manage em = Emp_Manage.GetInstance();

        int target_id;
        Console.Write("사원 id를 입력 해주세요");
        target_id = int.Parse(Console.ReadLine());

        int idx = FindIdx(target_id);

        em.Emp_list.RemoveAt(idx);
        //대기
        Console.WriteLine("삭제 완료");
        Console.ReadLine();
    }
   
    public void emp_PrintList(int mode)
    {
        // TODO implement here
        //전체 출력
        if (mode == 0)
        {
            Emp_Manage em = Emp_Manage.GetInstance();
            for(int i=0;i<em.Emp_list.Count ;i++)
            {
                Console.WriteLine(em.Emp_list[i].ToString());
            }

        }
        //
        else if (mode == 1)
        {
            Emp_Manage em = Emp_Manage.GetInstance();

            Console.WriteLine("원하는 검색을 선택 해주세요.");
            Console.WriteLine("1 영업사원, 2 일반사원 3 파트타임");
            int choice = int.Parse(Console.ReadLine());

            switch(choice)
            {
                case 1:
                    {
                        foreach(Employee t in em.Emp_list)
                        {
                            if (t is Emp_Salary)//영업직
                            {
                                Console.WriteLine(((Emp_Salary)t).ToString());

                            }
                            
                            else
                            {
                               
                            }
                        }
                        break;
                    }
                case 2:
                    {
                        foreach (Employee t in em.Emp_list)
                        {
                            
                            if (t is Emp_General)//일반직
                            {
                                if (!(t is Emp_Salary))
                                {
                                    Console.WriteLine(((Emp_General)t).ToString());
                                }

                            }
                            else
                            {
                               
                            }
                        }
                        break;
                    }
                case 3:
                    {
                        foreach (Employee t in em.Emp_list)
                        {
                           
                            if (t is Emp_Parttime)//파트타임근무
                            {

                                Console.WriteLine(((Emp_Parttime)t).ToString());

                            }
                            else
                            {
                               
                            }
                        }
                        break;
                    }
                default :
                    {
                        Console.WriteLine("뭘 누르는거야 진짜.");
                        break;
                    }
            }

            Console.WriteLine("출력 완료");
            Console.ReadLine();
        }
    }

   

}