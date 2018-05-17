using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;


namespace Team5project
{
    class Register
    {
        static string path = @"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";

        public Register(){}

        public static bool AutoRegist()
        {
            var rkApp = Registry.CurrentUser.OpenSubKey(path, true);

            //레지스트리 등록 할때
            if (rkApp.GetValue("Team5project") == null)
            {
                rkApp.SetValue("Team5project", System.Windows.Forms.Application.ExecutablePath.ToString());

                return true;
            }
            return false;
        }

        public static void AdminRegist()
        {
            bool enable = true;
            // 시작프로그램에 등록하는 레지스트리
            string runkey = path;
            Microsoft.Win32.RegistryKey startupekey = Microsoft.Win32.Registry.LocalMachine.OpenSubKey(runkey);

            if (enable)
            {
                if (startupekey.GetValue("Team5project") == null)
                {
                    startupekey.Close();
                    startupekey = Microsoft.Win32.Registry.LocalMachine.OpenSubKey(runkey, true);
                    startupekey.SetValue("Team5project", Application.ExecutablePath.ToString());
                    startupekey.Close();
                    MessageBox.Show("성공");
                }
            }
            else
                MessageBox.Show("실패");
        }

        public static bool AutoRunDisRegist()
        {
            var rkApp = Registry.CurrentUser.OpenSubKey(path, true);

            //레지스트리 삭제 할때
            if (rkApp.GetValue("Team5project") != null)
            {
                rkApp.DeleteValue("Team5project", false);
                MessageBox.Show("레지스트리 삭제");
                return true;
            }
            return false;
        }

        public static void AdminDisRegist()
        {
            bool enable = false;
            try
            {
                string runkey = path;
                Microsoft.Win32.RegistryKey startupekey = Microsoft.Win32.Registry.LocalMachine.OpenSubKey(runkey);

                if (enable == false)
                {
                    if (startupekey.GetValue("Team5project") == null)
                    {
                        startupekey.DeleteValue("Team5project", false);
                        startupekey.Close();
                    }
                }

                MessageBox.Show("성공");
            }
            catch (Exception error)
            {
                MessageBox.Show(error.Message);
            }
        }


    }
}
