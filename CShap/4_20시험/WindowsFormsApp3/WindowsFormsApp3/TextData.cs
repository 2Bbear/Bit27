using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WindowsFormsApp3
{
    class TextData
    {
        //좌표
        int x = 0;
        int y = 0;
        //색상
        Color currentColor;
        //문자열
        String str;
        //글자크기
        int fontSize;

        public int X { get => x; set => x = value; }
        public int Y { get => y; set => y = value; }
        public Color CurrentColor { get => currentColor; set => currentColor = value; }
        public string Str { get => str; set => str = value; }
        public int FontSize { get => fontSize; set => fontSize = value; }

        public TextData()
        {
            currentColor = Color.Red;
            str = "초기화된 문자열";
            fontSize = 10;
            x = 0;
            y = 0;
        }

        
    }
}
