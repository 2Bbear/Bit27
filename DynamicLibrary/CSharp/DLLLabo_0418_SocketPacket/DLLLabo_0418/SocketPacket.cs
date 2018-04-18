using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace DLLLabo_0418
{
    public enum SocketPackMode { Default, ToServer, ToClient }

    /// <summary>
    /// Server와 Client 간의 Data 통신을 위한 패킷 클래스
    /// </summary>
    public class SocketPacket
    {
        #region SingleTone
        private static SocketPacket singletone;
       

        static SocketPacket()
        {
            singletone = new SocketPacket();
        }
        #endregion

        private string nickname;
        private string id;
        private string pw;
        private bool login;



        public SocketPacket()
        {
            nickname = null;
            id = null;
            pw = null;
            login = false;
        }

        //서버로 전송하는 회원가입 
        public static string SignUpMessage(String _nickName)
        {
            String result = "NEWMEMBER@";
            result += _nickName + "#" + true.ToString();
            return result;
        }
        //클라로 전송하는 회원가입
        public static string ASK_SignUpMessage(String _nickName, bool b)
        {
            String result = "ASK_NEWMEMBER@";
            result += _nickName +"#"+ b.ToString();
            return "";
        }
        //서버로 전송하는 닉네임 중복여부 확인
        public static string NickNameCheck(String _nickName)
        {
            String result = "NICKNAMECHECK@";
            result += _nickName + true.ToString();
            return result;
        }
        //클라로 전송하는 닉네임 중복여부 확인
        public static string ASK_NickNameCheck(String _nickName,bool b)
        {
            String result = "NICKNAMECHECK@";
            result += _nickName + true.ToString();
            return result;
        }



    }
}
