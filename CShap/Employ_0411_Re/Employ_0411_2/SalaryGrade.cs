
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;


public class SalaryGrade
{

    public int grade;
    public int losal;
    public int hisal;

    public SalaryGrade(int grade, int losal, int hisal)
    {
        this.grade = grade;
        this.losal = losal;
        this.hisal = hisal;
    }

    public override string ToString()
    {
        //String.Format("[등급]{0}", grade);
        return String.Format("[급여 등급]{0}", grade);
    }
}