using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media;
namespace FigureMaster_0501
{
    class ShapeCollection:List<Shape>
    {

        public ShapeCollection()
        {
            Add(new Shape() {
                Type = true,
                Pointx = 10,
                Pointy=10,
                Size=100,
                Color=Colors.AliceBlue
            });

            Add(new Shape()
            {
                Type = true,
                Pointx = 20,
                Pointy = 20,
                Size = 200,
                Color = Colors.Aquamarine
            });
        }
    }
}
