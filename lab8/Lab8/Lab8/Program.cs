using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApplication1
{
    class Calculation
    {
        public static int FindRigrtBracket(string s, int index) 
        {
            int count = 1;
            while (count != 0)
            {
                switch (s[index])
                {
                    case ')': count--; break;
                    case '(': count++; break;
                }       
                index++;
            }
            return index - 1;
        }

        public static string SinCos(string s, int index)
        {
            index = index + 4;
            var indRight = FindRigrtBracket(s, index);
            var res = Calc(s.Substring(index, indRight - index));
            if (s[index-4] == 's')
            {
                return s.Substring(0, index - 4) + Math.Sin(res).ToString() + s.Substring(indRight + 1, s.Length - indRight - 1);
            }
            else return s.Substring(0, index - 4) + Math.Cos(res).ToString() + s.Substring(indRight + 1, s.Length - indRight - 1);
        }

        public static string Sqrt(string s, int index)
        {
            index = index+5;
            var indRight = FindRigrtBracket(s, index);
            var res = Calc( s.Substring(index, indRight-index));
            if (res >= 0) 
            {
                return s.Substring(0, index-5) + Math.Sqrt(res).ToString() + s.Substring(indRight+1, s.Length - indRight-1);
            }
            else throw new Exception("Под корнем отрицательное число!");
        }

        public static string Ln(string s, int index)
        {
            index = index + 3;
            var indRight = FindRigrtBracket(s, index);
            var res = Calc(s.Substring(index, indRight - index));
            if (res > 0)
            {
                return s.Substring(0, index - 3) + Math.Log(res).ToString() + s.Substring(indRight + 1, s.Length - indRight - 1);
            }
            else throw new Exception("Под знаком логорифма отрицательные числа!!");
        }

        public static double Calc(string s)
        {
            int index;
            while ((index = s.IndexOf("sqrt", 0)) != -1)
            {
                s = Sqrt(s, index);
            }

            while ((index = s.IndexOf("ln", 0)) != -1)
            {
                s = Ln(s, index);
            }

            while ((index = s.IndexOf("sin", 0)) != -1 || (index = s.IndexOf("cos", 0)) != -1)
            {
                s = SinCos(s, index);
            }

            double res;

            if (double.TryParse(s, out res)) 
                return res;

            s = '(' + s + ')';
            Stack<double> operands = new Stack<double>();
            Stack<char> op = new Stack<char>();
            int pos = 0;
            object token;
            object prevToken = ' ';
            do
            {
                token = getToken(s, ref pos);
                if (token is char && prevToken is char && (char)prevToken == '(' &&  (char)token == '-')
                    operands.Push(0); 

                if (token is double) 
                    operands.Push((double)token); 

                else if (token is char) 
                {
                    if ((char)token == ')')
                    {
                        while (op.Count > 0 && op.Peek() != '(')
                            popFunction(operands, op);
                        op.Pop();
                    }
                    else
                    {
                        while (canPop((char)token, op)) 
                            popFunction(operands, op);

                        op.Push((char)token); 
                    }
                }
                prevToken = token;
            }
            while (token != null);

            if (operands.Count > 1 || op.Count > 0 || operands.Count == 0)
                throw new Exception("Некорректное выражение!");

            return operands.Pop();
        }

        private static void popFunction(Stack<double> operands, Stack<char> op)
        {
            if (operands.Count < 2)
                throw new Exception("Выражение некорректно");
            double X = operands.Pop();
            double Y = operands.Pop();
            switch (op.Pop())
            {
                case '+': operands.Push(Y + X);
                    break;
                case '-': operands.Push(Y - X);
                    break;
                case '*': operands.Push(Y * X);
                    break;
                case '/': if (X != 0) operands.Push(Y / X); else throw new Exception("Деление на 0!!");
                    break;
            }
        }

        private static bool canPop(char op1, Stack<char> op)
        {
            if (op.Count == 0) return false;
            int p1 = PriorityOp(op1);
            int p2 = PriorityOp(op.Peek());

            return p1 >= 0 && p2 >= 0 && p1 >= p2;
        }

        private static int PriorityOp(char op)
        {
            switch (op)
            {
                case '(':  return -1; 
                case '*':  case '/':  return 1;
                case '+':  case '-':  return 2;
                default: throw new Exception("Введены посторонние символы");
            }
        }

        private static object getToken(string s, ref int pos)
        {
            if (pos == s.Length) 
                return null;
            if (char.IsDigit(s[pos]))
                return (object)double.Parse(ParseDouble(s, ref pos));
            else
                return s[pos++];
        }

        private static string ParseDouble(string s, ref int pos)
        {
            string res = "";
            while (pos < s.Length && (char.IsDigit(s[pos]) || s[pos] == '.' || s[pos] == ','))
                res += s[pos++];

            return res;
        }
    }

    static class Program
    {
        /// <summary>
        /// Главная точка входа для приложения.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Calc());
        }
    }
}
