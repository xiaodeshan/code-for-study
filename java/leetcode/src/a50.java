
public class a50 {
	public double myPow(double x, int n) {
		long nn = n;
		if (nn == 0)
			return 1.00000;
		if(equalInt(x, 1)) {
			return 1.00000;
		}
		if (nn < 0) {
			x = 1 / x;
			nn = -nn;
		}

		// 快速幂
		double result = 1.0;
		double y = x;
		while (nn != 0) {
			long k = (nn & 1);
			if (k == 1)
				result *= k * y;
			nn = (nn >> 1);
			y = y * y;
		}

		return result;
	}
	
	boolean equalInt(double x,int y) {
		if(Math.abs(x - y) <= 0.0000001) {
			return true;
		}
		return false;
	}

	public static void main(String[] args) {
		System.out.println(new a50().myPow(2.00000, -2147483648));
	}
}
