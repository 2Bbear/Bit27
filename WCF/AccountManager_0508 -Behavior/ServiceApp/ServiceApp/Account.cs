using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ServiceModel;
using System.Runtime.Serialization;


namespace ServiceApp
{
    [DataContract(Namespace = "http://RuAAService.co.kr/Product", Name = "AccountInfo")]
    public class Account
    {
        [DataMember(Name = "ID", Order = 1, IsRequired = true)]
        public int Id;

        [DataMember(Name = "Balance", Order = 2, IsRequired = true)]
        public int Balance;

        [DataMember(Name = "AccountName", Order = 3, IsRequired = true)]
        public string AccountName;

        [DataMember(Name = "AccountDate",Order = 4, IsRequired = true)]
        public DateTime CreateDate;
    }

}
