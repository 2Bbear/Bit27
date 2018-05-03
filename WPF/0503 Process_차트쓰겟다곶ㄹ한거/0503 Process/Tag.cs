using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SampleProcess
{
    public class Tag
    {
        public List<int> tags { get; set; }

        public DateTime RightNow { get; set;  }

        public Tag(List<int> t)
        {
            tags = t;
        }
    }
}
