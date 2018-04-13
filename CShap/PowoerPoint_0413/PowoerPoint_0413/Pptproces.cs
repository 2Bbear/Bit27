using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PowoerPoint_0413
{
    /*
     ppt선택 -> 파워포인터 실행 -> 종료
                                -> 이동
            ->파워포인터 편집 
            후작업을 요청하기 전에 Control에 질의를 해서 판단.
         */
    class Pptproces
    {

        #region Method
        public void Selectppt()
        {
            try
            {
                Console.Clear();
                //파일 리스트 출력
                PrintpptList();
                //파일 번호 받기
                Console.Write("선택할 파일의 인덱스를 적어주세요");
                int idx = int.Parse(Console.ReadLine());
                if(idx<0 || idx>=Control.SingleTone.Pptlist.Count)
                {
                    throw new Exception("올바른 파일의 인덱스가 아닙니다.");
                }
                Control.SingleTone.Selectppt(idx);
                Console.WriteLine("선택 성공");
                Console.ReadLine();
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                Console.ReadLine();

                Selectppt();
            }
            

        }
        public void PrintpptList()
        {
            for(int i =0; i < Control.SingleTone.Pptlist.Count; i++)
            {
                Console.WriteLine(Control.SingleTone.PrintpptListAttribute(i));
            }
        }
        public void Createppt()
        {
            try
            {
                //User Input
                Console.Write(">>파일명 : ");
                string filename = Console.ReadLine();
                foreach (PowerPoint t in Control.SingleTone.Pptlist)
                {
                    if (t.FileName.Equals(filename))
                    {
                        throw new Exception("중복된 파일명이 있습니다. 다시 작성해주세요");
                    }
                }
                Console.Write(">>페이지 갯수 : ");
                int pageCount = int.Parse(Console.ReadLine());

                //Create PowerPoint
                if (Control.SingleTone.Createppt(filename, pageCount))
                {
                    Console.WriteLine("파일 생성 성공");
                }
                else
                {
                    Console.WriteLine("파일 생성 실패");
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                
                Console.ReadLine();

                Createppt();
            }
           
        }
        public void SelectCurPage()
        {
            try
            {
                Console.Clear();
                //현재 페이지 출력
                Console.WriteLine("현재 페이지 : "+(Control.SingleTone.Ppt.CurPage)+1);
                Console.WriteLine("마지막 페이지 : " + Control.SingleTone.Ppt.Size);
                Console.Write("선택하고 싶은 페이지를 적어주세요");
                int selectpage =int.Parse( Console.ReadLine());
                if(selectpage<0 || selectpage> Control.SingleTone.Ppt.Size)
                {
                    throw new Exception("올바른 페이지 번호가 아닙니다. 다시 적어주세요");
                }
                //현재 페이지 수정
                Control.SingleTone.Ppt.CurPage = selectpage-1;

                Console.WriteLine("페이지 선택 성공");
                Console.ReadLine();
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);

                Console.ReadLine();

                SelectCurPage();

            }
        }
        public void PrintPPT()
        {
            Control.SingleTone.PrintPPT();
        }
        public void FileLoad()
        {

        }
        public void Runppt()
        {
            Control.SingleTone.Runppt();
        }
       
        public void NextPage()
        {
            Control.SingleTone.NextPage();
        }
        public void PrevPage()
        {
            Control.SingleTone.PrevPage();
        }
        public void Stopppt()
        {
            Control.SingleTone.Stopppt();
        }
        public void Editppt()
        {
           
            try
            {
                Console.Clear();
                Console.WriteLine("페이지 수정");
                //컨트롤에 질의 현재 파일이 선택되었느냐

                Console.Write("편집할 페이지 번호  1~N :");
                int pagenumber = int.Parse(Console.ReadLine());
                if(pagenumber<=0 || pagenumber > Control.SingleTone.Ppt.Size)
                {
                    throw new Exception();
                }
                
                Console.Write("편집할 문자열 :");
                string str = Console.ReadLine();

                Control.SingleTone.Editppt(pagenumber-1, str);
                Console.WriteLine("수정 성공");
                Console.ReadLine();
            }
            catch (Exception ex)
            {
                Console.WriteLine("잘못된 페이지 번호 입니다.");

                Console.WriteLine("다시 수정해주세요");
                Console.ReadLine();

                Editppt();
            }
            
            
        }
        #endregion
    }
}
