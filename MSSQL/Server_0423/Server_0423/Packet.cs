using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


/*
 *InsertAccount
 * PACK _INSERTACCOUNT@이름#타입#잔액
 * => ACK_INSERTACCOUNT@이름#TRUE
 * => ACK_INSERTACCOUNT@이름#FALSE
 * 
 * SelectAllAccount
 * PACK _SELECTACCOUNT@
 * =>ACK_SELECTACCOUNT@.... #...# %...#...#..%
 * 
 * DeleteAccount
 * PACK _DELETEACCOUNT@계좌번호
 * => ACK_DELETEACCOUNT@계좌번호#TRUE
 * => ACK_DELETEACCOUNT@계좌번호#FALSE
 * 
 * InputAccount
 * PACK _INPUTACCOUNT@계좌번호#입금액
 * => ACK_INPUTACCOUNT@계좌번호#TRUE
 * => ACK_INPUTACCOUNT@계좌번호#FALSE
 * 
 * OutputAccount
 * PACK _OUTPUTACCOUNT@계좌번호#출금액
 * => ACK_OUTPUTACCOUNT@계좌번호#TRUE
 * => ACK_OUTPUTACCOUNT@계좌번호#FALSE
     */
namespace wb.lib
{
    class Packet
    {
        #region 싱글톤
        private Packet() { }
        public static Packet Singleton;
        static Packet()
        {
            Singleton = new Packet();
        }
        #endregion

        //계좌 생성
        public static string InsertAccountResult(string name, bool b)
        {
            string msg = "ACK_INSERTACCOUNT@";
            msg += name + "#";
            if (b)
                msg += "TRUE";
            else
                msg += "FALSE";
            return msg;
        }
        //전체 계좌 검색
        public static string SelectAllAccountResult(string data )
        {
            string msg = "ACK_SELECTACCOUNT@";
            msg += data;
            return msg;
        }
        //계좌 삭제
        public static string DeleteAccount(int _accid,bool b)
        {
            string msg = "ACK_DELETEACCOUNT@";
            msg += _accid + "#";
            if (b)
                msg += "TRUE";
            else
                msg += "FALSE";
            return msg;
        }
        //계좌 입금
        public static string InputAccount(int _accid,bool b)
        {
            string msg = "ACK_INPUTACCOUNT@";
            msg += _accid + "#";
            if (b)
                msg += "TRUE";
            else
                msg += "FALSE";
            return msg;
        }
        //계좌 출금
        public static string OutputAccount(int _accid, bool b)
        {
            string msg = "ACK_OUTPUTACCOUNT@";
            msg += _accid + "#";
            if (b)
                msg += "TRUE";
            else
                msg += "FALSE";
            return msg;
        }
        //===========================================================

        public static string IDCheckResult(string id, bool b)
        {
            string msg = "ACK_IDCHECK@";
            msg += id + "#";
            if (b)
                msg += "TRUE";
            else
                msg += "FALSE";
            return msg;
        }
        
        public static string NewMember(string nickname, bool b)
        {
            string msg = "ACK_NEWMEMBER@";
            msg += nickname + "#";
            if (b)
                msg += "TRUE";
            else
                msg += "FALSE";
            return msg;
        }
    }
}
