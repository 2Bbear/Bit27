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
        public static void SaveFile(List<String>target)
        {
            StreamWriter sw = new StreamWriter(new FileStream("Log.txt", FileMode.Create));

            foreach (string s in target)
            {
                sw.WriteLine(s);
            }
            sw.Close();

        }
        public static void LoadFile(List<String> target)
        {
            StreamReader sr = new StreamReader(new FileStream("Log.txt", FileMode.Open));
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
