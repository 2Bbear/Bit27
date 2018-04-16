using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PowoerPoint_0413
{
    public class PowerPoint
    {
        #region Attribute
        private String fileName;
        private Object[] pageContent;
        private int size;
        private int curPage;
        private bool isRun;
        #endregion
       
        #region Property
        public string FileName { get => fileName; set => fileName = value; }
        public int Size { get => size; set => size = value; }
        public int CurPage { get => curPage;  set => curPage = value; }
        public bool IsRun { get => isRun; set => isRun = value; }
        public object[] PageContent { get => pageContent; set => pageContent = value; }

        #endregion

        #region index
        public Object this[int index]
        {
            get { return PageContent[index]; }
            set { PageContent[index] = value; }
        }
        #endregion

        #region Constructor
        public PowerPoint(string _fileName, int _size)
        {
            //Initializing
            FileName = _fileName;
            Size = _size;
            PageContent = new Object[Size];
            CurPage = 0;
            IsRun = false;
        }
        #endregion


    }
}
