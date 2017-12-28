/*
7. Reverse Integer
Reverse digits of an integer.

Example1: x = 123, return 321
Example2: x = -123, return -321

click to show spoilers.

Note:
The input is assumed to be a 32-bit signed integer. 
Your function should return 0 when the reversed integer overflows.

将一个整数翻转，注意溢出和特殊情况，溢出输出0
 * */
public class a7 {
	public int reverse(int x) {
		int sign = (x >= 0) ? 1 : -1;
		if (x < 0)
			x = -x;

		int bits[] = new int[12];
		int bitsNum = 0;

		int y = x;
		while (y != 0) {
			bits[bitsNum++] = y % 10;
			y = y / 10;
		}

		int result = 0;
		boolean error = false;

		for (int i = 0; i < bitsNum; i++) {
			if(result > Integer.MAX_VALUE / 10 || result < 0) {
				error = true;
				break;
			}
			result = result * 10;
			result += bits[i];
		}
		if (!error)
			return sign * result;
		else {
			return 0;
		}
	}

	public static void main(String[] args) {
		System.out.println(new a7().reverse(-1000000009));
	}
}
