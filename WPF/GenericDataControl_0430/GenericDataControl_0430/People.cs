using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GenericDataControl_0430 
{
    class People : List<Person>
    {
        public People()
        {
            Add(new Person() { Name = "홍길동", Phone = "010-1111-1234" ,Age =24});
            Add(new Person() { Name = "일지매", Phone = "010-2222-1234", Age = 29 });
            Add(new Person() { Name = "임꺽정", Phone = "010-3333-1234", Age = 30 });
        }

    }
}
