using System;
using System.Collections.Generic;
using System.Threading.Tasks;

namespace MonteCarloPiSharp
{
    class Program
    {
		static int Main(string[] args)
        {
            ulong reps = Convert.ToUInt64(args[0]);
            ulong total = 0;

            ulong cores = Convert.ToUInt64(Environment.ProcessorCount);

            var watch = System.Diagnostics.Stopwatch.StartNew();

            var threads = new List<Task<ulong>>();
            for (ulong i = 0; i < cores; i++)
            {
                var task = new Task<ulong>(() => MonteCarloPi(reps / cores));
                task.Start();
                threads.Add(task);
            }

            foreach (var thread in threads)
            {
                thread.Wait();
                total += thread.Result;
            }                

            double pi = (Convert.ToDouble(total) / Convert.ToDouble(reps)) * 4.0;

            watch.Stop();

            Console.WriteLine("pi: " + pi);
            Console.WriteLine("time: " + watch.ElapsedMilliseconds + "ms");

            return 0;
        }

        private static ulong MonteCarloPi(ulong reps)
        {
            var random = new Random();

            ulong count = 0;
			for (ulong i = 0; i < reps; i++)
			{
				if (InUnitCircle(random.NextDouble(), random.NextDouble()))
                    count++;
			}

            return count;
        }

        private static bool InUnitCircle(double x, double y)
        {
            if (x * x + y * y <= 1.0)
                return true;
            else return false;
        }
    }
}
