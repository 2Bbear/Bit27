using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp9
{
    public class Member
    {
        #region Attribute
        private string name;
        private string id;
        private string pw;

        
        #endregion

        #region Property
        public string Name { get => name; set => name = value; }
        public string Id { get => id; set => id = value; }
        public string Pw { get => pw; set => pw = value; }
        #endregion

        #region Constructor
        public Member(string name, string id, string pw)
        {
            this.name = name;
            this.id = id;
            this.pw = pw;
        }


        #endregion

        #region Override
        public override string ToString()
        {
            return Name + "," + Id + "," + Pw;
        }
        #endregion


    }
}
