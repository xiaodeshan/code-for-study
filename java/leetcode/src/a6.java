/*
6. ZigZag Conversion
The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)

P   A   H   N
A P L S I I G
Y   I   R
And then read line by line: "PAHNAPLSIIGYIR"
Write the code that will take a string and make this conversion given a number of rows:

string convert(string text, int nRows);
convert("PAYPALISHIRING", 3) should return "PAHNAPLSIIGYIR".

给定行数，字符串以曲折的方式写成这样：

P   A   H   N
A P L S I I G
Y   I   R

写一个函数，可以将字符通过给定的行数转化为曲折字符串
 * */
public class a6 {
	public String convert(String s, int numRows) {
		StringBuilder[] result = new StringBuilder[numRows];

		for (int i = 0; i < numRows; i++) {
			result[i] = new StringBuilder();
		}

		int i = 0;

		while (i != s.length()) {
			for (int j = 0; j < numRows && i < s.length(); j++, i++) {
				char ch = s.charAt(i);

				result[j].append(ch);
			}

			if (i >= s.length())
				break;

			for (int j = numRows - 2; j > 0 && i < s.length(); j--, i++) {
				char ch = s.charAt(i);

				result[j].append(ch);
			}
		}

		StringBuilder last = new StringBuilder();
		for (int k = 0; k < numRows; k++)
			last.append(result[k]);
		return last.toString();
	}

	public static void main(String[] args) {
		System.out.println(new a6().convert("PAYPALISHIRING", 3));
	}
}
