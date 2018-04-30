using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;

namespace GenericDataControl_0430
{
    class ShortNumberValidationRule : ValidationRule
    {
        int min;
        public int Min
        {
            get { return min; }
            set { min = value; }
        }

        int max;
        public int Max
        {
            get { return max; }
            set { max = value; }
        }

        public override ValidationResult Validate(object value,System.Globalization.CultureInfo cultureInfo)
        {
            int number;
            if (!int.TryParse((string)value, out number))
            {
                return new ValidationResult(false, "정수를 입력하세요.");
            } 

            if (min <= number && number <= max)
            {
                // new ValidationResult(true, null) 같다
                return ValidationResult.ValidResult;
            }
            else
            {
                string msg =string.Format("단축 번호는 {0}에서 {1}까지 입력 가능합니다.", min, max);
                return new ValidationResult(false, msg);
            }
        }

    }
}
