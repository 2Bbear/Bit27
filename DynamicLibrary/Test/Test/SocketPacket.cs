using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;



namespace DLLLabo_0418
{
    public enum SocketPackMode { NEWMEMBER, ACK_NEWMEMBER, NICKNAMECHECK, ASK_NICKNAMECHECK, IDCHECK, ASK_IDCHECK, DELMEMBER, ASK_DELMEMBER, LOGIN, ASK_LOGIN, UPDATENICKNAME,
        ASK_UPDATENICKNAME, LOGOUT, ASK_LOGOUT, SELECTALLNICKNAME, ASK_SELECTALLNICKNAME }
    /// <summary>
    /// Server와 Client 간의 Data 통신을 위한 패킷 클래스
    /// </summary>
    public  class SocketPacket
    {
        #region SingleTone
        public static SocketPacket singletone;

        static SocketPacket()
        {
            singletone = new SocketPacket();
        }
        private SocketPacket()
        {

        }
        #endregion

        #region Method
        
        //1===================================================================
        //서버로 전송하는 회원가입 
        public static string SignUpMessage(String id,String pw, String _nickName)
        {
            String result = "NEWMEMBER@";
            result +=id+"#"+pw + "#"+_nickName ;
            return result;
        }
        //클라로 전송하는 회원가입
        public static string ASK_SignUpMessage(String _nickName, bool b)
        {
            String result = "ASK_NEWMEMBER@";
            result += _nickName + "#" + b.ToString();
            return result;
        }
        //2===================================================================
        //서버로 전송하는 닉네임 회원 가입 과정에서 중복여부 확인
        public static string NickNameCheckMessage(String _nickName)
        {
            String result = "NICKNAMECHECK@";
            result += _nickName + "#";
            return result;
        }

        //클라로 전송하는 닉네임 회원 가입 과정에서 중복여부 확인
        public static string ASK_NickNameCheckMessage(String _nickName, bool b)
        {
            String result = "ASK_NICKNAMECHECK@";
            result += _nickName + "#" + b.ToString();
            return result;
        }
        //3===================================================================
        //서버로 전송하는 아이디 중복 여부 확인
        public static string IDCheck(String _nickName)
        {
            String result = "IDCHECK@";
            result += _nickName + "#";
            return result;
        }
        //클라로 전송하는 아이디 중복 여부 확인
        public static string ASK_IDCheck(String _nickName, bool b)
        {
            String result = "ASK_IDCHECK@";
            result += _nickName + "#" + b.ToString();
            return result;
        }
        //4===================================================================
        //서버로 전송하는 회원 탈퇴 메세지
        public static string DeleteMemberMessage(String _nickName)
        {
            String result = "DELMEMBER@";
            result += _nickName + "#";
            return result;
        }
        //클라로로 전송하는 회원 탈퇴 메세지
        public static string ASK_DeleteMemberMessage(String _nickName, bool b)
        {
            String result = "ASK_DELMEMBER@";
            result += _nickName + "#" + b.ToString();
            return result;
        }
        //5===================================================================
        //서버로 전송하는 로그인 메세지
        public static string LoginMessage(String id, String pw)
        {
            String result = "LOGIN@";
            result += id + "#" + pw;
            return result;
        }
        //클라로 전송하는 로그인 메세지
        public static string ASK_LoginMessage(String _nickName, bool b)
        {
            String result = "ASK_LOGIN@";
            result += _nickName +"#" + b.ToString();
            return result;
        }
        //6===================================================================
        //서버로 전송하는 회원 닉네임 수정 메세지
        public static string UpdateNickNameMessage(String _nickName, String _modifyNickName)
        {
            String result = "UPDATENICKNAME@";
            result += _nickName + "#" + _modifyNickName;
            return result;
        }
        //클라로 전송하는 회원 닉네임 수정 메세지
        public static string ASK_UpdateNickNameMessage(String _nickName, String _modifyNickName, bool b)
        {
            String result = "ASK_UPDATENICKNAME@";
            result += _nickName + "#" + _modifyNickName + "#" + b.ToString();
            return result;
        }

        //7===================================================================
        //서버로 전송하는 로그아웃 메세지
        public static string LogOutMessage(String _nickName)
        {
            String result = "LOGOUT@";
            result += _nickName + "#";
            return result;
        }
        //클라로 전송하는 로그아웃 메세지
        public static string ASK_LogOutMessage(String _nickName, bool b)
        {
            String result = "ASK_LOGOUT@";
            result += _nickName + "#" + b.ToString();
            return result;
        }


        //8===================================================================
        //서버로 전달하는  전체 회원리스트 얻기
        public static string SelectAllNickNameMessage()
        {
            String result = "SELECTALLNICKNAME@";

            return result;
        }
        //클라로 전달하는 전체 회원 리스트
        public static string ASK_SelectAllNickNameMessage(List<String> _nickNameList)
        {
            String result = "ASK_SELECTALLNICKNAME@";
            foreach (String t in _nickNameList)
            {
                result += t + "#";
            }
            return result;
        }
        //9===============================================================
        //문자열을 Split해서 List로 출력하기
        public static List<String> SplitMessge(String msg)
        {
            List<String> result=new List<String>();

            String[] msgHeader = msg.Split('@');
            result.Add(msgHeader[0]);
            String[] msgTemp = msgHeader[1].Split('#');

            foreach(String target in msgTemp)
            {
                result.Add(target);
            }
            return result;
        }

        #endregion


        

    }
}

