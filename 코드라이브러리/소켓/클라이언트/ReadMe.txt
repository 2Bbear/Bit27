******************************************************************
����

using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;


1. Client�� �����ϱ� ���� �ڵ带 �ۼ��Ѵ�.
private wbClient client; // ��ü�� ����ְ�

client = new wbClient(ip, port, LogMessage, DataMessage); // �� �̿��� �����ǿ� ��Ʈ�� ����ش�.


2. �������� ���۹��� �����͸� ó���ϱ� ���� DataMessage ��������Ʈ�� ���ϴ� ���� �����Ѵ�.
  public void DataMessage(Socket sock, string msg)
        {   
            string[] filter = msg.Split('@');
            if (filter[0].Equals("SENDMESSAGE"))
            {
                string[] filter1 = filter[1].Split('#');
                string nickname = filter1[0];
                string message = filter1[1];
                //���
                string print = string.Format("[{0}] {1}",
                    nickname, message);
                textBox1.Text += print + "\r\n";
            }
            else if (filter[0].Equals("ACK_NICKNAMECHECK"))
            {
                
                //ACK_NICKNAMECHECK@�г���#TRUE
                //ACK_NICKNAMECHECK@�г���#FALSE
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
                
                //ACK_IDCHECK@���̵�#TRUE
                //ACK_IDCHECK@���̵�#FALSE
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
                //ACK_NEWMEMBER@���̵�#TRUE
                //ACK_NEWMEMBER@���̵�#FALSE
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
                //ACK_LOGIN @�г���#TRUE
                //ACK_LOGIN @�г���#FALSE
                
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
                //ACK_DELMEMBER @���̵�#TRUE
                //ACK_DELMEMBER @���̵�#FALSE
                string[] filter1 = filter[1].Split('#');
                if (filter1[1].Equals("TRUE"))
                {
                    textBox1.Text += String.Format("{0}�� ���� �Ǿ����ϴ�.", filter1[0]);
                    logInForm.CheckLogidId(false);
                    ȸ��Ż��ToolStripMenuItem.Enabled = false;
                    ȸ������ToolStripMenuItem.Enabled = true;
                    �α���ToolStripMenuItem.Enabled = true;
                    ȸ����������ToolStripMenuItem.Enabled = false;
                    �α׾ƿ�ToolStripMenuItem.Enabled = false;
                }
                else if (filter1[1].Equals("FALSE"))
                {
                    textBox1.Text += String.Format("{0}�� ������ ���� �߽��ϴ�..", filter1[0]);
                }
            }
            //ȸ�� �г��� ����
            else if(filter[0].Equals("ACK_UPDATENICKNAME"))
            {
                //ACK_UPDATENICKNAME @�����Ҵг���#TRUE
                // ACK_UPDATENICKNAME @�����Ҵг���#FALSE
                string[] filter1 = filter[1].Split('#');
                if (filter1[1].Equals("TRUE"))
                {
                    currentNickName = filter1[0];
                    textBox1.Text += String.Format("{0} �г��� ���� ����", currentNickName) + "\r\n";
                    SetNickNameBox(currentNickName);
                }
                else if (filter1[1].Equals("FALSE"))
                {
                    textBox1.Text += "�г��� ���� ����" + "\r\n";
                }
            }
            //�α׾ƿ�

            //��ü ȸ������Ʈ ���
        }

3. Client���� �߻��ϴ� �α׸� ó���ϱ� ���� �޼ҵ带 ���ϴ� ���� �����Ѵ�.
 public void LogMessage(LogType ltype, string msg)
        {
            string str;
            if (ltype == LogType.Connect)
            {
                string[] temp = msg.Split('#');
                str = string.Format("[���� ����] {0}:{1}",
                    temp[0], temp[1]);
            }
            else if (ltype == LogType.DisConnect)
            {
                string[] temp = msg.Split('#');
                str = string.Format("[���� ���� ����] {0}:{1}",
                    temp[0], temp[1]);
            }
            else
            {
                str = string.Format(msg);
            }
            CheckForIllegalCrossThreadCalls = false;        //<++++++++++++++++++++++++++++++++++++++

            textBox1.Text += str + "\r\n";
        }

4. 1������ ������� DataMessage LogMessage�� ��ģ��.

5. �����͸� ������ ������ �ʹٸ�

client.SendMessage(client.Server,""); �̷��� �Ἥ ������.
