using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PowoerPoint_0413
{
    class Control
    {
        #region SingleTonePathern
        private static Control singleTone;

        public static Control SingleTone { get => singleTone; set => singleTone = value; }
        

        private Control() { }
        static Control()
        {
            SingleTone = new Control();
        }
        #endregion

        #region Property
        internal PowerPoint Ppt { get => ppt; private set => ppt = value; }
        internal List<PowerPoint> Pptlist { get => pptlist; set => pptlist = value; }
        public int CurrentPptListIndex { get => currentPptListIndex; private set => currentPptListIndex = value; }
        #endregion

        #region Field
        //오후에는 컬렉션으로 확장 private List<M> pptlist;
        private List<PowerPoint> pptlist = new List<PowerPoint>();

        //선택한 ppt 파일
        private int currentPptListIndex = 0;
        private PowerPoint ppt=null;

        //Event
        public event CreateEvent CreatePPT = null;
        public event DeleteEvent DeletePPT = null;
        public event EditEvent EditPPT = null;

        #endregion

        #region Method
        public void Selectppt(int _idx)
        {
            ppt = pptlist[_idx];
            if(ppt==null)
            {
                throw new Exception("선택한 ppt가 null값 입니다.");
            }
        }
        public String PrintpptListAttribute(int _idx)
        {
            String result = "";
            result += String.Format("인덱스 : {0}  파일명 : {1}", _idx, Pptlist[_idx].FileName);
            return result;
        }

        public bool Createppt(string filename,int size)
        {
            //중복 파일명이 있는 경우 false
            
            Ppt = new PowerPoint(filename,size);
            pptlist.Add(Ppt);
            if (Ppt!=null)
            {
                if(CreatePPT != null)
                {
                    //호출
                    CreatePPT(this, new PowerPointCreateLogEventArg(Ppt));
                }
                return true;
            }
            else
            {
                return false;
            }   
        }
        public void PrintPPT()
        {
            if(Ppt==null)
            {
                Console.WriteLine("ppt파일을 생성하세요");
                return;
            }
            if(Ppt.IsRun==false)
            {//5를 눌러야 출력함
                Console.WriteLine("ppt파일을 선택했습니다.");
                return;
            }
            Console.WriteLine("**************************************");
            Console.WriteLine(": ["+(Ppt.CurPage+1)+"]");
            Console.WriteLine(": 컨텐츠 추가할 위치");
            Console.WriteLine(": ");
            Console.WriteLine(": "+Ppt[Ppt.CurPage]);
            Console.WriteLine(": ");
            Console.WriteLine(": 현재 날짜 / 시간 정보 출력");
            Console.WriteLine("**************************************");
        }
        public void Runppt()
        {
            Ppt.IsRun = true;
        }
        public  void Stopppt()
        {
            Ppt.IsRun = false;
        }
        public void NextPage()
        {
            if(Ppt.CurPage>=Ppt.Size-1)
            {
                return;
            }
            Ppt.CurPage += 1;
        }
        public void PrevPage()
        {
            if (Ppt.CurPage <= 0)
            {
                return;
            }
            Ppt.CurPage -= 1;
        }
        public void Editppt(int _pagenumber, string _str)
        {
            Ppt[_pagenumber] = _str;

            if (CreatePPT != null)
            {
                //호출
                EditPPT(this, new PowerPointEditLogEventArg(Ppt));
            }
        }
        public void FileLoad()
        {

            /*
              //파일 리스트를 화면에 출력
              파일명 입력받는 기능 수행
              3.해당파일 객체를 선택
              3.1 올바른 파일
              private Powerpoint ppt =선택;
              3.2 잘못된 파일이면 리턴
             */
        }
        #endregion



    }
}
