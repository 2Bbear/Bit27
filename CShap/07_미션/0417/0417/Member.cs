using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _0417
{
    public class Member
    {
        public string NickName { get; set; }
        public string Id { get; private set; }
        public string Password { get; private set; }
        public bool IsLogindState{get;  set;}

        public Member(string _nickname, string _id, string _password)
        {
            NickName = _nickname;
            Id = _id;
            Password = _password;
            IsLogindState = false;
        }
    }
}
