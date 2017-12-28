/*
29. Divide Two Integers

实现两个数的除法
 
 * 
 * */
public class a29 {
	public int divide(int dividend, int divisor) {
		long x = dividend;
		long y = divisor;

		if (y == 0)
			return Integer.MAX_VALUE;
		if (y == 1)
			return dividend;
		long res = 0;
		long nage = 1;
		if (dividend > 0 && divisor < 0 || dividend < 0 && divisor > 0)
			nage = -1;
		if (dividend < 0) {
			x = -x;
		}
		if (divisor < 0)
			y = -y;

		while (x >= y) {
			int muti = 1;
			long temp = y;
			while ((temp << 1) < x) {
				temp = temp << 1;
				muti = muti << 1;
			}

			x -= temp;
			res += muti;
		}

		int trueResult = (int)(res*nage);
		
		if((long)trueResult != (res*nage))
			return Integer.MAX_VALUE;
		return trueResult;
	}

	public static void main(String[] args) {
		System.out.println(new a29().divide(10, 3));

	}
}
