using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _0417
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

        //회원 가입 과정 닉네임 중복 체크 메세지
        public static string NickNameCheckResult(string nickname, bool b)
        {
            string msg = "ACK_NICKNAMECHECK@";
            msg += nickname + "#";
            if (b)
                msg += "TRUE";
            else
                msg += "FALSE";
            return msg;
        }
        //ID 중복 체크 메세지
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
        //회원 가입 메세지
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
        //로그인 메세지
        public static string LogIn(string nickname, bool b)
        {
            string msg = "ACK_LOGIN@";
            msg += nickname + "#";
            if (b)
                msg += "TRUE";
            else
                msg += "FALSE";

            return msg;

        }
        //회원 삭제 메시지
        public static string DelMember(string _ID , bool b)
        {
            string msg = "ACK_DELMEMBER@";
            msg += _ID + "#";
            if (b)
                msg += "TRUE";
            else
                msg += "FALSE";

            return msg;
        }
        //회원 닉네임 수정
        public static string UpdateNickName(string _modifyed, bool b)
        {
            string msg = "ACK_UPDATENICKNAME@";
            msg += _modifyed + "#";
            if (b)
                msg += "TRUE";
            else
                msg += "FALSE";

            return msg;
        }
    }
}