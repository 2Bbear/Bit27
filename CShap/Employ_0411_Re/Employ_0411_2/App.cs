
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

public class App {

    #region Attribute
    private Control control;
    private static App me;
 

    #endregion

    #region Contructor
    private App()
    {
        control = new Control();
    }
    #endregion

    #region Method
    public static App GetInstance()
    {
        
        if (me==null)
        {
            me = new App();
        }
        return me;
    }


    public void Menu()
    {
        Console.Clear();
        //��� ��ü ���
        control.emp_PrintList(0);
        // TODO implement here
        Console.WriteLine("======================================");
        Console.WriteLine("1.��� ���");
        Console.WriteLine("2.��� �˻�");
        Console.WriteLine("3.��� ����");
        Console.WriteLine("4.��� ����");
        Console.WriteLine("5.��� ���");
        Console.WriteLine("6.����");
        Console.WriteLine("======================================");
        int choice = int.Parse(Console.ReadLine());

        switch(choice)
        {
          
            //��� ���
            case 1:
                {
                    Console.Write("sdfdsf");
                    control.emp_Insert();
                    break;
                }
            //��� �˻�
            case 2:
                {
                    control.emp_Search();
                    break;
                }
            //��� ����
            case 3:
                {
                    control.emp_Change();
                    break;
                }
           //��� ����
            case 4:
                {
                    control.emp_Delete();
                    break;
                }
           //��� ���
            case 5:
                {
                    control.emp_PrintList(1);
                    break;
                }
           //����
            case 6:
                {
                    break;
                }
            default:
                {
                    Console.Write("�⺻��");
                    break;
                }
        }

    }
    public void Init()
    {
        
        //�� ������ ���̺� �ʱ�ȭ�� ����
        Emp_Manage em = Emp_Manage.GetInstance();
       
        Dept_Manage dm = Dept_Manage.GetInstance();
     
        Salary_Manage sm = Salary_Manage.GetInstance();
        
       
        

    }
    public void Run()
    {
        while(true)
        {
            Menu();

        }
    }
    public void Exit()
    {

    }
    //private Method============================================
    private void Logo()
    {

    }

    private void Eding()
    {

    }
    private void Pause()
    {

    }

    #endregion





}