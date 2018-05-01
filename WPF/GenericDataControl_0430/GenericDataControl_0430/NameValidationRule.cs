using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;

namespace GenericDataControl_0430
{
    //정수값 입력시 에러
    //
    class NameValidationRule : ValidationRule
    {
        public int Min { get; set; }
        public int Max { get; set; }

        public override ValidationResult Validate(object value, System.Globalization.CultureInfo cultureInfo)
        {
            int number;
            if (int.TryParse((string)value, out number))
            {
                return new ValidationResult(false, "문자를 입력하세요.");
            }
            float number2;
            if (float.TryParse((string)value, out number2))
            {
                return new ValidationResult(false, "문자를 입력하세요.");
            }
            if (Min <= ((string)value).Length && ((string)value).Length <= Max)
            {
                // new ValidationResult(true, null) 같다
                return ValidationResult.ValidResult;
            }
            else
            {
                string msg = string.Format("이름의 문자 개수는 {0}에서 {1}까지 입력 가능합니다.", Min, Max);
                return new ValidationResult(false, msg);
            }
        }
    }
}
