using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Team5project.Resources
{
    class UIManager
    {
        #region  싱글톤
       public static UIManager Singleton { get; private set; }

        static UIManager()
        {
            Singleton = new UIManager();
        }

        private UIManager()
        {
        }
        #endregion

        public void subwindow()
        {

        }

        



    }
}
