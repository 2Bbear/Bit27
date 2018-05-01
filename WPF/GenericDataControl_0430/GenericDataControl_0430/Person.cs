using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
/*
 * 
*/
namespace GenericDataControl_0430
{
    class Person : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;

        private string name;
        public string Name
        {
            get { return name; }
            set
            {
                name = value;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("Name"));
            }
        }

        private string phone;
        public string Phone
        {
            get { return phone; }
            set
            {
                phone = value;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("Phone"));
            }
        }
        private int? age;
        public int? Age
        {
            get { return age; }
            set
            {
                age = value;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("Age"));
            }
        }

        private bool? male;
        public bool? Male
        {
            get { return male; }
            set
            {
                male = value;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("Male"));
            }
        }

        private int? shortNumber;
        public int? ShortNumber
        {
            get { return shortNumber; }
            set
            {
                shortNumber = value;
                if (PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("ShortNumber"));
            }
        }


        public override string ToString()
        {
            string sex;
            if (Male == null)
                sex = "남/여";
            else if (Male == true)
                sex = "남";
            else
                sex = "여";

            return string.Format("단축번:{0}, 이름:{1}, 전화:{2},나이 :{3} 성별:{4}", ShortNumber, Name, Phone, Age, sex);
        }

    }

}
