using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

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
    

        public static string NickNameCheck(string nickname)
        {
            string str = "NICKNAMECHECK@";
            str += nickname;
            return str;
        }

        public static string IDCheck(string id)
        {
            string str = "IDCHECK@";
            str += id;
            return str;
        }

        public static string NewMember(string nickname, string id, string pw)
        {
            string str = "NEWMEMBER@";
            str += nickname + "#";
            str += id + "#";
            str += pw;
            return str;
        }

        public static string SendMessage(string nickname, string msg)
        {
            string str = "SENDMESSAGE@";
            str += nickname + "#";
            str += msg;
            return str;
        }

        public static string CheckNickName(string nickname)
        {
            string str = "CHECKNICKNAME@";
            str += nickname;
            return str;
        }

        public static string LogIn(string _ID, String PW)
        {
            string str = "LOGIN@";
            str += _ID+"#"+ PW;
            return str;
        }
        public static string DelMember(string _ID)
        {
            string str = "DELMEMBER@";
            str += _ID;
            return str;
        }
        public static string UpdateNickName(String _nickName, String _modifyNickName)
        {
            string str = "UPDATENICKNAME@";
            str += _nickName + "#" + _modifyNickName;
            return str;
        }
    }
}
