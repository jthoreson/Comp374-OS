using System;
using System.Collections.Generic;
using System.Threading;

namespace Homework3
{
    internal class IsNumberPrimeCalculator
    {
        private readonly ICollection<long> _primeNumbers;
        private readonly Queue<long> _numbersToCheck;
        public static object LockQueue = new object();
        public static object LockList = new object();

        public IsNumberPrimeCalculator(ICollection<long> primeNumbers, Queue<long> numbersToCheck)
        {
            _primeNumbers = primeNumbers;
            _numbersToCheck = numbersToCheck;
        }

        public void CheckIfNumbersArePrime()
        {

            while (true)
            {
                Thread.Sleep(0);
                long numberToCheck = 0;
                lock (LockQueue)
                {
                    if (_numbersToCheck.Count > 0)
                    {
                        numberToCheck = _numbersToCheck.Dequeue();
                    }
                }
                if (IsNumberPrime(numberToCheck))
                {
                    lock (LockList)
                    {
                        _primeNumbers.Add(numberToCheck);
                    }
                }
            }
        }

        private bool IsNumberPrime(long numberWeAreChecking)
        {
            const long firstNumberToCheck = 3;

            if (numberWeAreChecking % 2 == 0)
            {
                return false;
            }
            var lastNumberToCheck = Math.Sqrt(numberWeAreChecking);
            for (var currentDivisor = firstNumberToCheck; currentDivisor < lastNumberToCheck; currentDivisor += 2)
            {
                if (numberWeAreChecking % currentDivisor == 0)
                {
                    return false;
                }
            }
            return true;
        }
    }
}