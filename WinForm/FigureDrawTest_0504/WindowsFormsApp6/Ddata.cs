using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WindowsFormsApp6
{
    public enum DrawType { RECT, ELLIPSE }

    public enum DrawSize : int{ RECT25 = 25, RECT50 = 50 }

    public class Ddata
    {
        public DrawType m_dt;
        public Color m_color;
        public DrawSize m_ds;
        public Point pt;

        public Ddata()
        {
            this.m_dt = DrawType.RECT;
            this.m_color = Color.Red;
            this.m_ds = DrawSize.RECT25;
            this.pt.X = 100;
            this.pt.Y = 100;
        }
    }
}
