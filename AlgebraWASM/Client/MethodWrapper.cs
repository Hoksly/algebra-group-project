﻿using System.Runtime.InteropServices;
using System.Text;

namespace AlgebraWASM.Client
{
    public static class FiniteFieldMethods
    {
        [DllImport("finite-field-wrapper")]
        public static unsafe extern byte* addition(byte* a, byte* b, byte* mod, byte* errStr);

        [DllImport("finite-field-wrapper")]
        public static unsafe extern byte* subtraction(byte* a, byte* b, byte* mod, byte* errStr);

        [DllImport("finite-field-wrapper")]
        public static unsafe extern byte* multiplication(byte* a, byte* b, byte* mod, byte* errStr);

        [DllImport("finite-field-wrapper")]
        public static unsafe extern byte* division(byte* a, byte* b, byte* mod, byte* errStr);

        [DllImport("finite-field-wrapper")]
        public static unsafe extern byte* fastPow(byte* a, byte* degree, byte* mod, byte* errStr);

        [DllImport("finite-field-wrapper")]
        public static unsafe extern byte* inverse(byte* num, byte* mod, byte* errStr);

		[DllImport("finite-field-wrapper")]
		public static extern unsafe byte** factorizePolard(ref int size, byte* num, byte* mod, byte* errorStr);

		[DllImport("finite-field-wrapper")]
		public static extern unsafe byte** factorizeSimple(ref int size, byte* num, byte* mod, byte* errorStr);

		[DllImport("finite-field-wrapper")]
		public static extern unsafe byte** discreteSqrt(byte* num, byte* mod, byte* errorStr);

		[DllImport("finite-field-wrapper")]
        public static unsafe extern byte* discreteLog(byte* num, byte* basa, byte* mod, byte* errStr);

        [DllImport("finite-field-wrapper")]
        public static unsafe extern byte* orderOfElement(byte* num, byte* mod, byte* errStr);

        [DllImport("finite-field-wrapper")]
        public static unsafe extern bool isGenerator(byte* num, byte* mod, byte* errStr); 

        [DllImport("finite-field-wrapper")]
        public static unsafe extern byte* CarmichaelFunction(byte* num, byte* mod, byte* errStr); 

        [DllImport("finite-field-wrapper")]
        public static unsafe extern bool isPrime(byte* num, byte* mod, byte* iterations, byte* errStr);

		[DllImport("finite-field-wrapper")]
		public static unsafe extern byte* EulerFunction(byte* num, byte* mod, byte* errStr);
	}

	public static class PolyRingMethods
	{
		[DllImport("poly-ring-wrapper")]
		public static unsafe extern byte** polyAddition(ref int returnSize, int polySize1, byte** polyStr1, int polySize2, byte** polyStr2, byte* numModStr, byte* errorStr);

		[DllImport("poly-ring-wrapper")]
		public static unsafe extern byte** polySubstruction(ref int returnSize, int polySize1, byte** polyStr1, int polySize2, byte** polyStr2, byte* numModStr, byte* errorStr);

		[DllImport("poly-ring-wrapper")]
		public static unsafe extern byte** polyMultiplication(ref int returnSize, int polySize1, byte** polyStr1, int polySize2, byte** polyStr2, byte* numModStr, byte* errorStr);

		[DllImport("poly-ring-wrapper")]
		public static unsafe extern byte** polyDivision(ref int returnSize, int polySize1, byte** polyStr1, int polySize2, byte** polyStr2, byte* numModStr, byte* errorStr);

		[DllImport("poly-ring-wrapper")]
		public static unsafe extern byte** polyRest(ref int returnSize, int polySize1, byte** polyStr1, int polySize2, byte** polyStr2, byte* numModStr, byte* errorStr);

		[DllImport("poly-ring-wrapper")]
		public static unsafe extern byte** polyParse(ref int returnSize, byte* inputPolyString);
	}
}