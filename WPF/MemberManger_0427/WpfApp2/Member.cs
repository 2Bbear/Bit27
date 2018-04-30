using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media;

namespace WpfApp2
{

    class Member
    {
        String m_name;
        String m_phonenum;
        String m_id;
        String m_password;
        //true = 남성 false = 여성
        bool gender;
        [Flags]
        public enum Ehooby : byte {Default=0x00, ReadBook=0x01, WatchingMovie=0x02, Tour=0x04 };
        Ehooby myhoby;
        Color mycolor;

        public Member(Ehooby myhoby, Color mycolor, string name, string phonenum, string id, string password, bool gender)
        {
            Myhoby = myhoby;
            Mycolor = mycolor;
            Name = name;
            Phonenum = phonenum;
            Id = id;
            Password = password;
            Gender = gender;
            
        }

        public Ehooby Myhoby { get => myhoby; set => myhoby = value; }
        public Color Mycolor { get => mycolor; set => mycolor = value; }
        public string Name { get => m_name; set => m_name = value; }
        public string Phonenum { get => m_phonenum; set => m_phonenum = value; }
        public string Id { get => m_id; set => m_id = value; }
        public string Password { get => m_password; set => m_password = value; }
      
        public bool Gender { get => gender; set => gender = value; }


    }
}
