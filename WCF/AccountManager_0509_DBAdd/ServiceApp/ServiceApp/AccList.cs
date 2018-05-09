using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;

namespace ServiceApp
{
    [DataContract(Namespace = "http://RuAAService.co.kr/Product", Name = "AccountList")]
    public class AccList
    {
        [DataMember(Name = "AccListID", Order = 1, IsRequired = true)]
        public int accListID;
        [DataMember(Name = "AccID", Order = 2, IsRequired = true)]
        public int accID;
        [DataMember(Name = "InputMoney", Order = 3, IsRequired = true)]
        public int inputMoney;
        [DataMember(Name = "OutputMoney", Order = 4, IsRequired = true)]
        public int outputMoney;
        [DataMember(Name = "Balance", Order = 5, IsRequired = true)]
        public int balance;
        [DataMember(Name = "Date", Order = 6, IsRequired = true)]
        public DateTime date;

    }
}
