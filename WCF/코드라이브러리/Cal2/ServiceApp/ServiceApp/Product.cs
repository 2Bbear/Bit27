using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ServiceModel;
using System.Runtime.Serialization;


namespace ServiceApp
{
    [DataContract(Namespace = "http://RuAAService.co.kr/Product", Name = "ProductInfo")]
    public class Product
    {
        [DataMember(Name = "ID", Order = 1, IsRequired = true)]
        public int ProductId;

        [DataMember(Name = "Name", Order = 2, IsRequired = true)]
        public string ProductName;

        [DataMember(Order = 3)]
        public string Company;

        [DataMember(Name = "Value", Order = 4, IsRequired = true)]
        public double Price;

        [DataMember(Order = 5, IsRequired = true)]
        public DateTime CreateDate;
    }

}
