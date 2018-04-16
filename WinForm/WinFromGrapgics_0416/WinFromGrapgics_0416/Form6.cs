using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WinFromGrapgics_0416
{
    public partial class Form6 : Form
    {
        Image imageFile = null;
        string path = @"C:\Users\User\Desktop\바탕화면\";
        //hanyijie-sky-scenery-ship-anime-ART-998071.jpg
        string filename = @"hanyijie-sky-scenery-ship-anime-ART-998071.jpg";
        public Form6()
        {
            //C:\Users\User\Desktop\바탕화면

            imageFile = Image.FromFile(path + filename);
            InitializeComponent();
        }

        protected override void OnPrint(PaintEventArgs e)
        {
            Graphics grfx = e.Graphics;
            if(grfx!=null)
            {
                grfx.DrawImage(imageFile,0,0);
            }
            
        }

        private void button1_Click(object sender, EventArgs e)
        {
            imageFile = Image.FromFile(path+filename);
            this.Invalidate(true);
        }
    }
}
