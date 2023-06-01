using System;

namespace Cherry
{
    public class Core
    {
        public float number = 5;

        Core()
        {
            Console.WriteLine("Constructor");
        }

        public void PrintMessage()
        {
            Console.WriteLine("Hello from C#");
        }

        public void PrintSum(int num1, int num2)
        {
            Console.WriteLine(num1 + num2);
        }
    }
}
