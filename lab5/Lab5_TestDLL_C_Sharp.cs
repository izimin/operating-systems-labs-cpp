using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace TestDll
{
    class Program
    {
        [DllImport("C:\\Users\\Ilya\\Documents\\Visual Studio 2012\\Projects\\DllNastya\\Debug\\DllNastya.dll")]
        public static extern int Fak(int x);
        //[DllImport("C:\\Users\\Ilya\\Documents\\Visual Studio 2012\\Projects\\CppClassDll\\Debug\\CppClassDll.dll")]
        //public static extern int Rev(int x);

        static void Main(string[] args)
        {
            int x;
            Console.Write("Введите целое число: ");
            x = int.Parse(Console.ReadLine());
            Console.WriteLine("Число делителей введённого числа:  " + Fak(x));
           // Console.WriteLine("Обратная запись введённого числа:  " + Rev(x));
        }
    }
}
