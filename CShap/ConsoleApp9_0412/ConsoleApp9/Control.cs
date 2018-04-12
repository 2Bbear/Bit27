using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.Remoting.Messaging;


namespace ConsoleApp9
{
    /*
     Member가 기본 internal 상태여서 
     public인 DelResult를 사용할 때 internal인 Member를 사용 할 수 없다.
     그래서 액세스 오류가 발생한다.
     Member도 public으로 노출 시키면 이 문제는 해결된다.

         */
    public delegate void DelResult(Member mm);
    class Control
    {
        #region attribute

        private DelResult result;
        private List<Member> memlist;

        private static Control singleton;
        #endregion

        #region Constructor
        private Control() { }

        static Control()
        {
            singleton = new Control();
            singleton.memlist = new List<Member>();
        }
        #endregion

        #region Method
        public static Control Instance()
        {
            return singleton;
        }

        public void DataInit()
        {
            memlist.Add(new Member("홍길동", "11", "11"));
            memlist.Add(new Member("김이라", "22", "22"));
            memlist.Add(new Member("아이린", "33", "33"));
        }
        //리스트 안에서 멤버를 찾는 함수
        public Member Login(string id,string pw)
        {
            foreach(Member mem in memlist)
            {
                if(mem.Id.Equals(id)&&mem.Pw.Equals(pw))
                {
                    return mem;
                }
            }
            return null;
        }
        public void Login1(Result r,string id, string pw)
        {
            foreach (Member mem in memlist)
            {
                if (mem.Id.Equals(id) && mem.Pw.Equals(pw))
                {
                    r.SendResult(mem);
                    return;
                }
            }
            r.SendResult(null);
            
        }
        public void Login2(DelResult r, string id, string pw)
        {
            result = r;
            foreach (Member mem in memlist)
            {
                if (mem.Id.Equals(id) && mem.Pw.Equals(pw))
                {
                    r(mem);
                    return;
                }
            }
            r.Invoke(null);

        }
        #endregion

    }
}
