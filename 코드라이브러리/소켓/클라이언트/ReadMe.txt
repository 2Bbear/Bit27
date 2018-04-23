******************************************************************
사용법

using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;


1. Client를 시작하기 위한 코드를 작성한다.
private wbClient client; // 개체를 잡아주고

client = new wbClient(ip, port, LogMessage, DataMessage); // 를 이용해 아이피와 포트를 잡아준다.


2. 서버에서 전송받은 데이터를 처리하기 위한 DataMessage 딜리게이트를 원하는 곳에 정의한다.
  public void DataMessage(Socket sock, string msg)
        {   
            string[] filter = msg.Split('@');
            if (filter[0].Equals("SENDMESSAGE"))
            {
                string[] filter1 = filter[1].Split('#');
                string nickname = filter1[0];
                string message = filter1[1];
                //출력
                string print = string.Format("[{0}] {1}",
                    nickname, message);
                textBox1.Text += print + "\r\n";
            }
            else if (filter[0].Equals("ACK_NICKNAMECHECK"))
            {
                
                //ACK_NICKNAMECHECK@닉네임#TRUE
                //ACK_NICKNAMECHECK@닉네임#FALSE
                string[] filter1 = filter[1].Split('#');
                if( filter1[1].Equals("TRUE"))
                {
                    form.CheckNicknameResult(true);
                  }
                else
                {
                    form.CheckNicknameResult(false);
                }
            }
            else if (filter[0].Equals("ACK_IDCHECK"))
            {
                
                //ACK_IDCHECK@아이디#TRUE
                //ACK_IDCHECK@아이디#FALSE
                string[] filter1 = filter[1].Split('#');
                if (filter1[1].Equals("TRUE"))
                {
                    form.CheckIDResult(true);
                    
                }
                else
                {
                    form.CheckIDResult(false);
                    
                }
            }
            else if (filter[0].Equals("ACK_NEWMEMBER"))
            {
                //ACK_NEWMEMBER@아이디#TRUE
                //ACK_NEWMEMBER@아이디#FALSE
                string[] filter1 = filter[1].Split('#');
                if (filter1[1].Equals("TRUE"))
                {
                    NewMember(filter1[0], true);
                }
                else
                {
                    NewMember(filter1[0], false);
                }
            }
            //Login Message
            else if(filter[0].Equals("ACK_LOGIN"))
            {
                //ACK_LOGIN @닉네임#TRUE
                //ACK_LOGIN @닉네임#FALSE
                
                string[] filter1 = filter[1].Split('#');
                if (filter1[1].Equals("TRUE"))
                {
                    currentNickName = filter1[0];
                    logInForm.CheckLogidId(true);
                    SetNickNameBox(currentNickName);

                    // form.CheckIDResult(true);

                }
                else if(filter1[1].Equals("FALSE"))
                {
                    
                   
                    logInForm.CheckLogidId(false);
                   
                    
                    //form.CheckIDResult(false);
                }
            }
            //DelMeber Message
            else if(filter[0].Equals("ACK_DELMEMBER"))
            {
                //ACK_DELMEMBER @아이디#TRUE
                //ACK_DELMEMBER @아이디#FALSE
                string[] filter1 = filter[1].Split('#');
                if (filter1[1].Equals("TRUE"))
                {
                    textBox1.Text += String.Format("{0}이 삭제 되었습니다.", filter1[0]);
                    logInForm.CheckLogidId(false);
                    회원탈퇴ToolStripMenuItem.Enabled = false;
                    회원가입ToolStripMenuItem.Enabled = true;
                    로그인ToolStripMenuItem.Enabled = true;
                    회원정보수정ToolStripMenuItem.Enabled = false;
                    로그아웃ToolStripMenuItem.Enabled = false;
                }
                else if (filter1[1].Equals("FALSE"))
                {
                    textBox1.Text += String.Format("{0}의 삭제에 실패 했습니다..", filter1[0]);
                }
            }
            //회원 닉네임 수정
            else if(filter[0].Equals("ACK_UPDATENICKNAME"))
            {
                //ACK_UPDATENICKNAME @수정할닉네임#TRUE
                // ACK_UPDATENICKNAME @수정할닉네임#FALSE
                string[] filter1 = filter[1].Split('#');
                if (filter1[1].Equals("TRUE"))
                {
                    currentNickName = filter1[0];
                    textBox1.Text += String.Format("{0} 닉네임 변경 성공", currentNickName) + "\r\n";
                    SetNickNameBox(currentNickName);
                }
                else if (filter1[1].Equals("FALSE"))
                {
                    textBox1.Text += "닉네임 변경 실패" + "\r\n";
                }
            }
            //로그아웃

            //전체 회원리스트 얻기
        }

3. Client에서 발생하는 로그를 처리하기 위한 메소드를 원하는 곳에 정의한다.
 public void LogMessage(LogType ltype, string msg)
        {
            string str;
            if (ltype == LogType.Connect)
            {
                string[] temp = msg.Split('#');
                str = string.Format("[서버 접속] {0}:{1}",
                    temp[0], temp[1]);
            }
            else if (ltype == LogType.DisConnect)
            {
                string[] temp = msg.Split('#');
                str = string.Format("[서버 접속 해제] {0}:{1}",
                    temp[0], temp[1]);
            }
            else
            {
                str = string.Format(msg);
            }
            CheckForIllegalCrossThreadCalls = false;        //<++++++++++++++++++++++++++++++++++++++

            textBox1.Text += str + "\r\n";
        }

4. 1번에서 만들어진 DataMessage LogMessage를 합친다.

5. 데이터를 서버로 보내고 싶다면

client.SendMessage(client.Server,""); 이렇게 써서 날린다.
