using System;
using System.Collections.Generic;
using System.Text;

using ClassLibrary2;

namespace _0409_Account
{
    class WbArray
    {
        private Object[] acclist;
        public int Size { get; private set;}
        public int Max { get; private set; }

        public WbArray(int _max)
        {
            acclist = new Account[_max];

            Size = 0;
            Max = _max;
        }

        //Save instance
        public void push_back(Object obj)
        {
            if (Size >= Max)
            { throw new Exception("Overflow"); }
            acclist[Size++] = obj;

            
        }
        //Delete instance
        public Object erase(int idx)
        {
            Object obj = acclist[idx];
            //배열 삭제
            for (int i = idx; i < Size; i++)
            {
                acclist[i] = acclist[i + 1];
            }
            Size--;
            return obj;
        }

        public void erase(Object obj)
        {
            //배열 Search
            for (int i = 0; i < Size; i++)
            {
                Object o = acclist[i];
                if(o.Equals(obj)==true)
                {
                    //배열 삭제
                    for (int j = i; j < Size; j++)
                    {
                        acclist[j] = acclist[j + 1];
                    }
                    Size--;
                }
            }

        }

        //Indexer
        public Object this[int index]
        {
            get { return acclist[index]; }
        }
       
    }
}
