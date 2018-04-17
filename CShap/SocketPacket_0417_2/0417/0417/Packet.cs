using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _0417
{
    /// <summary>
    /// Server와 client간의 Data 통신을 위한 클래스
    /// 모든 패키징의 내용을 담고 있고, 서로간의 변환을 할 수 있는 클래스
    /// 
    /// </summary>
    public class Packet
    {
        #region Attribute
        byte[] contents;
        public byte[] Contents { get => contents; private set => contents = value; }


        #endregion

        #region Constructor
        public Packet()
        {
           
        }

        

        #endregion

        #region Method

        #endregion

    }
}
