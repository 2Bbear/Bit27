using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media;

namespace _0501
{
    public class ShapeCollection : List<Shape>
    {
        public ShapeCollection()
        {
            Add(new Shape() {
                Type = false, 
                PointX = 10,
                PointY = 10, 
                Size = 100,
                Color = Colors.Blue});

            Add(new Shape()
            {
                Type = true,
                PointX = 20,
                PointY = 20,
                Size = 200,
                Color = Colors.Aquamarine
            });
        }

        public void myadd()
        {
            Add(new Shape()
            {
                Type = true,
                PointX = 10,
                PointY = 20,
                Size = 100,
                Color = Colors.Blue
            });
        }
    }
}
