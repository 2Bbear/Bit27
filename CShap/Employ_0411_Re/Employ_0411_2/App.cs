
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
        //사원 전체 출력
        control.emp_PrintList(0);
        // TODO implement here
        Console.WriteLine("======================================");
        Console.WriteLine("1.사원 등록");
        Console.WriteLine("2.사원 검색");
        Console.WriteLine("3.사원 수정");
        Console.WriteLine("4.사원 삭제");
        Console.WriteLine("5.사원 출력");
        Console.WriteLine("6.종료");
        Console.WriteLine("======================================");
        int choice = int.Parse(Console.ReadLine());

        switch(choice)
        {
          
            //사원 등록
            case 1:
                {
                    Console.Write("sdfdsf");
                    control.emp_Insert();
                    break;
                }
            //사원 검색
            case 2:
                {
                    control.emp_Search();
                    break;
                }
            //사원 수정
            case 3:
                {
                    control.emp_Change();
                    break;
                }
           //사원 삭제
            case 4:
                {
                    control.emp_Delete();
                    break;
                }
           //사원 출력
            case 5:
                {
                    control.emp_PrintList(1);
                    break;
                }
           //종료
            case 6:
                {
                    break;
                }
            default:
                {
                    Console.Write("기본값");
                    break;
                }
        }

    }
    public void Init()
    {
        
        //각 데이터 테이블 초기화와 생성
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