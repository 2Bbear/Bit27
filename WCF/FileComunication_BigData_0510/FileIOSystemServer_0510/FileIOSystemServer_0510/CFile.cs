using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.ServiceModel;
using System.Text;
using System.Threading.Tasks;

namespace FileIOSystemServer_0510
{
    class CFile : IFile
    {
        //델리게이트 선언
        public delegate void Data(string name, int idx, string msh, byte[] filedata, string type);
        //동기화 작업을 위해서 가상의 객체 생성
        private static Object syncObj = new Object();
        //채팅방에 있는 유저 이름 목록
        private static ArrayList Chatter = new ArrayList();
        //개인용 델리게이트
        private Data MyFile;
        //전체에게 보낼 정보를 담고 있는 델리게이트
        private static Data List;
        IFileCallback callback = null;

        public StudentData[] Join(string name, int idx)
        {
            Console.WriteLine("join메소드 시작");
            MyFile = new Data(UserHandler);
            lock (syncObj)
            {
                if(!Chatter.Contains(name))//이름이 기존 채터에 있는지 검색한다.
                {
                    //1. 로그인 데이터 처리==================================
                    StudentData data = new StudentData(true, name, idx);
                    Chatter.Add(data);

                    //2.사용자에게 보내 줄 채널을 설정한다.
                    callback = OperationContext.Current.GetCallbackChannel<IFileCallback>();

                    //현재 접속자 정보를 모두에게 전달
                    BroadcastMessage(name,idx,"",null,"UserEnter");

                    //델리게이터 추가(향후 데이터 수신이 가능하도록 구성)
                    List += MyFile;

                    //사용자리스트를 보내준다.
                    StudentData[] list = new StudentData[Chatter.Count];
                    lock(syncObj)
                    {
                        Chatter.CopyTo(list);

                    }
                    return list;

                }
                else//이미 사용자가 사용하고 있는 이름일 경우
                {
                    return null;
                }
            }
        }
        //떠남
        public void Leave(string name, int idx)
        {
            Console.WriteLine("Leave메소드 시작");
            if (name == null)
            {
                return;
            }
            //목록에서 제거
            lock(syncObj)
            {
                foreach(StudentData data in Chatter)
                {
                    if(data.Name==name)
                    {
                        Chatter.Remove(data);
                        break;
                    }
                }
            }
        }

        public bool UpLoadFile(string name, int idx, string filename, byte[] data)
        {
            Console.WriteLine("UpLoadFile 시작");
            try
            {
                FileStream writeFileStream = new FileStream(@"C:\MyImage\" + filename, FileMode.Create, FileAccess.Write);
                BinaryWriter dataWriter = new BinaryWriter(writeFileStream);

                dataWriter.Write(data);
                writeFileStream.Close();
                BroadcastMessage(name, idx, filename, data, "FileSender");
                return true;
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                return false;
            }
            finally
            {
            }
        }

        private void BroadcastMessage(string name, int idx, string msg, byte[] filedata, string msgType)
        {
            Console.WriteLine("BroadcastMessage 시작");
            if (List!=null)
            {
                foreach(Data handler in List.GetInvocationList())
                {
                    //if(handler != MyFile && msgType == "FileSender")
                    //{
                    //    continue;
                    //}
                    handler.BeginInvoke(name, idx, msg, filedata, msgType, new AsyncCallback(EndAsync), null);
                }
            }
        }

        private void EndAsync(IAsyncResult ar)
        {
            Console.WriteLine("EndAsync 시작");
            Data d = null;
            try
            {
                System.Runtime.Remoting.Messaging.AsyncResult asres = (System.Runtime.Remoting.Messaging.AsyncResult)ar;
                d = ((Data)asres.AsyncDelegate);
                d.EndInvoke(ar);
            }
            
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                List -= d;
            }
            finally
            {
            }
        }

        private void UserHandler(string name, int idx, string msg, byte[] filedata , string msgType)
        {
            Console.WriteLine("UserHandler 시작");
            try
            {
                if(msgType.Equals("FileSender"))
                {
                    callback.FileRecive(name, idx, msg, filedata);
                }
                switch (msgType)
                {
                    case "UserEnter":
                        {
                            callback.UserEnter(name, idx);
                            break;
                        }
                    case "UserLeave":
                        {
                            callback.UserLeave(name, idx);
                            break;
                        }
                    case "FileSender":
                        {
                            callback.FileRecive(name, idx,msg,filedata);
                            break;
                        }
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                Leave(name, idx);
            }
            finally
            {
            }
        }
    }
}
