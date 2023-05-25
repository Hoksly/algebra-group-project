using System.Runtime.InteropServices;
using System.Text;

namespace AlgebraWASM.Client
{
    public static class FiniteFieldMethods
    {
        [DllImport("global-wrapper")]
        public static unsafe extern byte* addition(byte* a, byte* b, byte* mod, byte* errStr);

        [DllImport("global-wrapper")]
        public static unsafe extern byte* subtraction(byte* a, byte* b, byte* mod, byte* errStr);

        [DllImport("global-wrapper")]
        public static unsafe extern byte* multiplication(byte* a, byte* b, byte* mod, byte* errStr);

        [DllImport("global-wrapper")]
        public static unsafe extern byte* division(byte* a, byte* b, byte* mod, byte* errStr);

        [DllImport("global-wrapper")]
        public static unsafe extern byte* fastPow(byte* a, byte* degree, byte* mod, byte* errStr);

        [DllImport("global-wrapper")]
        public static unsafe extern byte* inverse(byte* num, byte* mod, byte* errStr);

		[DllImport("global-wrapper")]
		public static extern unsafe byte* factorizePolard(ref int size, byte* num, byte* mod, byte* errorStr);

		[DllImport("global-wrapper")]
		public static extern unsafe byte* factorizeSimple(ref int size, byte* num, byte* mod, byte* errorStr);

		[DllImport("global-wrapper")]
		public static extern unsafe byte* discreteSqrt(ref int size, byte* num, byte* mod, byte* errStr);

		[DllImport("global-wrapper")]
        public static unsafe extern byte* discreteLog(byte* num, byte* basa, byte* mod, byte* errStr);

        [DllImport("global-wrapper")]
        public static unsafe extern byte* orderOfElement(byte* num, byte* mod, byte* errStr);

        [DllImport("global-wrapper")]
        public static unsafe extern bool isGenerator(byte* num, byte* mod, byte* errStr); 

        [DllImport("global-wrapper")]
        public static unsafe extern byte* CarmichaelFunction(byte* num, byte* mod, byte* errStr); 

        [DllImport("global-wrapper")]
        public static unsafe extern bool isPrime(byte* num, byte* mod, byte* iterations, byte* errStr);

		[DllImport("global-wrapper")]
		public static unsafe extern byte* EulerFunction(byte* num, byte* mod, byte* errStr);
	}

	public static class PolyRingMethods
	{
		[DllImport("global-wrapper")]
		public static unsafe extern byte* polyAddition(ref int returnSize, int polySize1, byte** polyStr1, int polySize2, byte** polyStr2, byte* numModStr, byte* errorStr);

		[DllImport("global-wrapper")]
		public static unsafe extern byte* polySubstruction(ref int returnSize, int polySize1, byte** polyStr1, int polySize2, byte** polyStr2, byte* numModStr, byte* errorStr);

		[DllImport("global-wrapper")]
		public static unsafe extern byte* polyMultiplication(ref int returnSize, int polySize1, byte** polyStr1, int polySize2, byte** polyStr2, byte* numModStr, byte* errorStr);

		[DllImport("global-wrapper")]
		public static unsafe extern byte* polyDivision(ref int returnSize, int polySize1, byte** polyStr1, int polySize2, byte** polyStr2, byte* numModStr, byte* errorStr);

		[DllImport("global-wrapper")]
		public static unsafe extern byte* polyRest(ref int returnSize, int polySize1, byte** polyStr1, int polySize2, byte** polyStr2, byte* numModStr, byte* errorStr);

		[DllImport("global-wrapper")]
		public static unsafe extern byte* polyDerivative(ref int returnSize, int polySize1, byte** polyStr1, byte* numModStr, byte* errorStr);

		[DllImport("global-wrapper")]
		public static unsafe extern byte* polyGCD(ref int returnSize, int polySize1, byte** polyStr1, int polySize2, byte** polyStr2, byte* numModStr, byte* errorStr);

		[DllImport("global-wrapper")]
		public static unsafe extern byte* polyEvaluate(ref int returnSize, int polySize1, byte** polyStr1, byte* numModStr, byte* errorStr);

		[DllImport("global-wrapper")]
		public static unsafe extern byte* getCyclotomic(ref int returnSize, byte* orderStr, byte* numModStr, byte* errorStr);

		[DllImport("global-wrapper")]
		public static unsafe extern byte** polyParse(ref int returnSize, byte* inputPolyString);
	}

	public static class PolyFieldMethods
	{
		[DllImport("poly-field-wrapper")]
		public static unsafe extern byte* polyFieldAddition(ref int returnSize, int polySize1, byte** polyStr1, int polySize2, byte** polyStr2, int polyModSize, byte** powModStr, byte* numModStr, byte* errorStr);

		[DllImport("poly-field-wrapper")]
		public static unsafe extern byte* polyFieldSubstruction(ref int returnSize, int polySize1, byte** polyStr1, int polySize2, byte** polyStr2, int polyModSize, byte** powModStr, byte* numModStr, byte* errorStr);

		[DllImport("poly-field-wrapper")]
		public static unsafe extern byte* polyFieldMultiplication(ref int returnSize, int polySize1, byte** polyStr1, int polySize2, byte** polyStr2, int polyModSize, byte** powModStr, byte* numModStr, byte* errorStr);

		[DllImport("poly-field-wrapper")]
		public static unsafe extern byte* polyFieldDivision(ref int returnSize, int polySize1, byte** polyStr1, int polySize2, byte** polyStr2, int polyModSize, byte** powModStr, byte* numModStr, byte* errorStr);

		[DllImport("poly-field-wrapper")]
		public static unsafe extern byte* polyFieldInversion(ref int returnSize, int polySize1, byte** polyStr1, int polyModSize, byte** powModStr, byte* numModStr, byte* errorStr);

		[DllImport("poly-field-wrapper")]
		public static unsafe extern byte** polyParse1(ref int returnSize, byte* inputPolyString);
	}
}