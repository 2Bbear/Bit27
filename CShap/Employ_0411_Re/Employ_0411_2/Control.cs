
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
        Console.Write("[�̸�] : ");
        name = Console.ReadLine();
        Console.Write("[�Ի���] : ");
        date = Console.ReadLine();
        Console.WriteLine("[�μ�] �μ� ��ȣ�� ���� ���ּ��� ");
        Console.Write(dm.ToString());
        departmentId = int.Parse(Console.ReadLine());
        Console.WriteLine("[�������] 1. ������� 2. �Ϲݻ�� 3.��ƮŸ�� ");
        emp_select= int.Parse(Console.ReadLine());
        Console.WriteLine("===================================");
        //��� ����
        switch (emp_select)
        {
            case 1:
                {
                    double sal;
                    double incentive;
                    Console.Write("[����] : ");
                    sal = double.Parse(Console.ReadLine());
                    Console.Write("[�μ�Ƽ��] : ");
                    incentive = double.Parse(Console.ReadLine());
                   // em.Emp_list.Add(new Emp_Salary(name, date, departmentId, sal, incentive));
                    em.AddListAttribute(new Emp_Salary(name, date, departmentId, sal, incentive));
                    break;
                }
            case 2:
                {
                    double sal;
                    Console.Write("[����] : ");
                    sal = double.Parse(Console.ReadLine());
                   // em.Emp_list.Add(new Emp_General(name, date, departmentId, sal));
                    em.AddListAttribute(new Emp_General(name, date, departmentId, sal));
                    break;
                }
            case 3:
                {
                    int timesal;
                    Console.Write("[�ñ�] : ");
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
        Console.WriteLine("��� ��� ����");
        Console.ReadLine();

    }
    public void emp_Search()
    {
        // TODO implement here
        Emp_Manage em = Emp_Manage.GetInstance();

        Dept_Manage dm = Dept_Manage.GetInstance();

        

        int target_id;

        //�Է¹ޱ�
        Console.Write("ã�� ���ID�� �Է����ּ���");
        target_id = int.Parse(Console.ReadLine());

        //ã��
        int idx=FindIdx(target_id);

        //����ϱ�
        //��� ����
        Console.WriteLine(PrintEmployeeInfo(em.Emp_list[idx]));
        //�μ� ����
        Console.WriteLine(PrintDepartmentInfo(em.Emp_list[idx].Dept_id));
        //�޿� ���
        Console.WriteLine(PrintGradeInfo(em.Emp_list[idx]));

        Console.ReadLine();

    }
    private String PrintEmployeeInfo(Employee _target)
    {
        string result = "";

        if(_target is Emp_Salary)//������
        {
            result += ((Emp_Salary)_target).ToString();
        }
        else if(_target is Emp_General )//�Ϲ���
        {
            if (!(_target is Emp_Salary))
            {
                result += ((Emp_General)_target).ToString();
            }
                
        }
        else if (_target is Emp_Parttime )//��ƮŸ�ӱٹ�
        {
            result += ((Emp_Parttime)_target).ToString();
        }
        else
        {
            Console.WriteLine("��");
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
        if (_target is Emp_Salary)//������
        {
            targetSal = ((Emp_Salary)_target).salary;
            

        }
        else if (_target is Emp_General)//�Ϲ���
        {
            if(!(_target is Emp_Salary))
            {
                targetSal = ((Emp_General)_target).salary;
            }
            
        }
        else if (_target is Emp_Parttime)//��ƮŸ�ӱٹ�
        {
            targetSal=((Emp_Parttime)_target).t_salary* ((Emp_Parttime)_target).w_time;
          
        }
        else
        {
            Console.WriteLine("��????");
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
        Console.Write("��� id�� �Է� ���ּ���");
        target_id = int.Parse(Console.ReadLine());

        int idx = FindIdx(target_id);
        
        //========================================================
        if (em.Emp_list[idx] is Emp_Salary)//������
        {
            double ch_sal=0d;
            double ch_incen = 0d;
            Console.Write("�޿� ����");
            ch_sal = double.Parse(Console.ReadLine());
            Console.Write("������ ����");
            ch_incen = double.Parse(Console.ReadLine());

            ((Emp_Salary)em.Emp_list[idx]).salary = ch_sal;
            ((Emp_Salary)em.Emp_list[idx]).incentive=ch_incen;

        }
        else if (em.Emp_list[idx] is Emp_General)//�Ϲ���
        {
            if (!(em.Emp_list[idx] is Emp_Salary))//������ �ϰ�� ����
            {
                double ch_sal = 0d;

                Console.Write("�޿� ����");
                ch_sal = double.Parse(Console.ReadLine());
                ((Emp_General)em.Emp_list[idx]).salary= ch_sal;
            }

        }
        else if (em.Emp_list[idx] is Emp_Parttime)//��ƮŸ�ӱٹ�
        {
            int ch_wtimel = 0;
            int ch_tsal = 0;
            Console.Write("���� �ð� ����");
            ch_wtimel = int.Parse(Console.ReadLine());
            Console.Write("�ñ� ����");
            ch_tsal = int.Parse(Console.ReadLine());

            ((Emp_Parttime)em.Emp_list[idx]).w_time = ch_wtimel;
            ((Emp_Parttime)em.Emp_list[idx]).t_salary = ch_tsal;

        }
        else
        {
            Console.WriteLine("��????");
        }

        //===============================================================

        //���
        Console.WriteLine("���� �Ϸ�");
        Console.ReadLine();
    }

    
    public void emp_Delete() {
        // TODO implement here
        // TODO implement here
        Emp_Manage em = Emp_Manage.GetInstance();

        int target_id;
        Console.Write("��� id�� �Է� ���ּ���");
        target_id = int.Parse(Console.ReadLine());

        int idx = FindIdx(target_id);

        em.Emp_list.RemoveAt(idx);
        //���
        Console.WriteLine("���� �Ϸ�");
        Console.ReadLine();
    }
   
    public void emp_PrintList(int mode)
    {
        // TODO implement here
        //��ü ���
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

            Console.WriteLine("���ϴ� �˻��� ���� ���ּ���.");
            Console.WriteLine("1 �������, 2 �Ϲݻ�� 3 ��ƮŸ��");
            int choice = int.Parse(Console.ReadLine());

            switch(choice)
            {
                case 1:
                    {
                        foreach(Employee t in em.Emp_list)
                        {
                            if (t is Emp_Salary)//������
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
                            
                            if (t is Emp_General)//�Ϲ���
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
                           
                            if (t is Emp_Parttime)//��ƮŸ�ӱٹ�
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
                        Console.WriteLine("�� �����°ž� ��¥.");
                        break;
                    }
            }

            Console.WriteLine("��� �Ϸ�");
            Console.ReadLine();
        }
    }

   

}