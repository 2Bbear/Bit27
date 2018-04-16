using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
namespace PowoerPoint_0413
{
    /// <summary>
    /// This class is Static Class ,
    /// so use . sentence
    /// </summary>
    [Serializable]
    public static class FileIOControl
    {
        static FileIOControl()
        {

        }
        public static void SavePPT(PowerPoint target)
        {
            StreamWriter sw = new StreamWriter(new FileStream(target.FileName+".txt", FileMode.Create));
            //파일명 저장
            sw.WriteLine(target.FileName);
            //콘텐츠 저장
            foreach(Object c in target.PageContent)
            {
                sw.WriteLine(c);
            }
            //사이즈 저장
            sw.WriteLine(target.Size);
            //현재 페이지 저장
            sw.WriteLine(0);
            //isrun저장
            sw.WriteLine(false);

            sw.Close();
    }
      
        public static void SaveFile(List<String>target)
        {
            StreamWriter sw = new StreamWriter(new FileStream("save.txt", FileMode.Create));

            foreach (string s in target)
            {
                sw.WriteLine(s);
            }
            sw.Close();

        }
        public static void LoadFile(List<String> target)
        {
            StreamReader sr = new StreamReader(new FileStream("save.txt", FileMode.Open));
            while (sr.EndOfStream == false)
            {
                target.Add(sr.ReadLine());
                //
                //Console.WriteLine(sr.ReadLine());
            }
            sr.Close();
        }
    }
}
