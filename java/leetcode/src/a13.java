/*
13. Roman to Integer

给定一个罗马数字，将它转化为数字

 * */
public class a13 {

	public int romanToInt(String s) {
		if (s == null || s.equals(""))
			return 0;

		String M[] = { "", "M", "MM", "MMM" };
		String C[] = { "", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM" };
		String X[] = { "", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC" };
		String I[] = { "", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX" };

		int end = s.length() - 1;

		int s0 = findNum(s, end, I);
		end = end - I[s0].length();
		int s1 = findNum(s, end, X);
		end = end - X[s1].length();
		int s2 = findNum(s, end, C);
		end = end - C[s2].length();
		int s3 = findNum(s, end, M);
		end = end - M[s3].length();
		
		return s0 + s1 * 10 + s2 * 100 + s3 * 1000;

	}

	public int findNum(String data, int end, String choose[]) {
		if(end < 0)
			return 0;
		
		int num = 0;
		int maxLen = 0;

		for (int i = 0; i < choose.length; i++) {
			int len = choose[i].length();
			if (len < maxLen)
				continue;

			int start = end - len + 1;
			if (start >= 0) {
				String temp = data.substring(start, end + 1);

				if (temp.equals(choose[i])) {
					maxLen = len;
					num = i;
				}
			}
		}

		return num;

	}

	public static void main(String[] args) {
		System.out.println(new a13().romanToInt("MM"));
	}
}
