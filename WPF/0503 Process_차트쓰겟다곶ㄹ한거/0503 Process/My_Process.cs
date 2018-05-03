using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _0503_Process
{
    class My_Process
    {
        int prioryty;
        string name;

        public My_Process()
        {
        }

        public My_Process(int prioryty, string name)
        {
            Prioryty = prioryty;
            Name = name;
        }

        public int Prioryty { get => prioryty; set => prioryty = value; }
        public string Name { get => name; set => name = value; }
    }
}
