using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using wb.lib;
using wb.lib1;
namespace Result
{
    class Result
    {

        #region attribute


        #endregion

        #region Constructor

        #endregion

        #region Method
        public void SendResult(Member mem)
        {
            if (mem != null)
            {
                Control c = Control.Instance();
                Console.WriteLine(mem);
            }
            else
            {
                Console.WriteLine("아이고 로그인 못했습니다.");
            }
        }
        #endregion
    }
}
