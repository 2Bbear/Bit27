using System;

namespace _0409_Account
{
    class Program
    {
        static void Main(string[] args)
        {
            App app = App.Instance;
            app.Init();
            app.Run();
            app.Exit();
        }
    }
}
