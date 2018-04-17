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
        #region Attribute
        private string packetModeName;
        private byte[] outContents;
        private int contentsStringLength;

        public byte[] OutContents { get => outContents; private set => outContents = value; }
        public int ContentsStringLength { get => contentsStringLength; set => contentsStringLength = value; }
        public string PacketModeName { get => packetModeName; private set => packetModeName = value; }

       

        #endregion

        #region Constructor
        public SocketPacket()
        {
            PacketModeName = null;
            OutContents = null;
            ContentsStringLength = 0;
        }

        #endregion

        #region Method
        //Convert Method======================================
        //String을 byte로 변환해서 Contents에 저장함
        public void SetContents(string target)
        {
            outContents = Encoding.Default.GetBytes(target);
            ContentsStringLength = (Encoding.Default.GetString(OutContents)).Length;
            if (target==null|| outContents==null)
            {
                throw new Exception("콘텐츠 또는 콘텐츠에 넣을 값이 비어있습니다.");
            }
        }
        //Int를 byte로 변환해서 contents에 저장함
        public void Setcontents(int target)
        {
            outContents = Encoding.Default.GetBytes(target.ToString());
            ContentsStringLength = (Encoding.Default.GetString(OutContents)).Length;
            if (target == 0 || outContents == null)
            {
                throw new Exception("콘텐츠 또는 콘텐츠에 넣을 값이 비어있습니다.");
            }
        }

        //String을 byte로 변환해서 Contents에 추가함
        public void AddContents(string target)
        {
           
            String temp = Encoding.Default.GetString(outContents);
            outContents=Encoding.Default.GetBytes(temp + target);
            ContentsStringLength = (Encoding.Default.GetString(OutContents)).Length;
            if (target == null || outContents == null)
            {
                throw new Exception("콘텐츠 또는 콘텐츠에 넣을 값이 비어있습니다.");
            }
        }
        //Int을 byte로 변환해서 Contents에 추가함
        public void AddContents(int target)
        {
            String temp = Encoding.Default.GetString(outContents);
            outContents = Encoding.Default.GetBytes(temp + target.ToString());
            ContentsStringLength = (Encoding.Default.GetString(OutContents)).Length;
            if (target == 0 || outContents == null)
            {
                throw new Exception("콘텐츠 또는 콘텐츠에 넣을 값이 비어있습니다.");
            }
        }
        //byte를 String으로 변환
        public String GetContents()
        {
            return Encoding.Default.GetString(outContents);
        }

        //MakePacket Method===================================
        public void MakePacket(SocketPackMode mode)
        {
            switch (mode)
            {
                case SocketPackMode.Default:
                    { }
                    break;
                case SocketPackMode.ToServer:
                    { }
                    break;
                case SocketPackMode.ToClient:
                    { }
                    break;
            }
        }

        //Override Method=====================================
        public override string ToString()
        {
            if(PacketModeName==null|| ContentsStringLength==0|| OutContents==null)
            {
                throw new Exception("출력하려는 패킷의 값이 비어있거나 정상적이지 않습니다.");
            }
            String result = "";
            result += PacketModeName;
            result += ContentsStringLength;
            result += OutContents;

            return result;
        }

        #endregion
    }
}
