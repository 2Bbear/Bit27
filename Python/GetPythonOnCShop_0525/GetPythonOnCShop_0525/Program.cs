using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

//파이선을 실행하기 위해 추가
using IronPython;
using IronPython.Hosting;
using IronPython.Runtime;
using IronPython.Modules;

namespace GetPythonOnCShop_0525
{
    class Program
    {
        static void Main(string[] args)
        {
            //먼저 참조추가에서 IronPython을 추가하야 한다.

            var engine = IronPython.Hosting.Python.CreateEngine();


            var scope = engine.CreateScope();

            try
            {
                //파이선 프로그램 파일 실행.
                var source = engine.CreateScriptSourceFromFile("simple.py");
                source.Execute(scope);

                // call def HelloWorld() :
                var Fnhelloworld = scope.GetVariable<Func<object>>("HelloWorld");
                Console.WriteLine(Fnhelloworld());

                // call def HelloWorld2(data) :
                var Fnhelloworld2 = scope.GetVariable<Func<object, object>>("HelloWorld2");
                Console.WriteLine(Fnhelloworld2("HelloWorld 2 "));

                // call def ListTest() :
                var FnListTest = scope.GetVariable<Func<object>>("ListTest");

                IronPython.Runtime.List r = (IronPython.Runtime.List)FnListTest();

                foreach (string data in r)
                {
                    Console.WriteLine("아result: {0}", data);
                }

                // call class MyClass
                var myClass = scope.GetVariable<Func<object, object>>("MyClass");
                var myInstance = myClass("hello");

                Console.WriteLine(engine.Operations.GetMember(myInstance, "value"));

            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }

        }
    }
}
