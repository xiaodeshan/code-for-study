/*
 *  5. Longest Palindromic Substring
Given a string s, find the longest palindromic substring in s. 
You may assume that the maximum length of s is 1000.

Example:

Input: "babad"
Output: "bab"

Note: "aba" is also a valid answer.
Example:

Input: "cbbd"
Output: "bb"

给定字符串s,找到它的最长回文子串，设s的最长为1000
 * */
public class a5 {
	
	private int startResult = 0;
	private int endResult = 0;
	private int len = 1;
	//复杂度 O(n^2)
	public String longestPalindrome(String s) {
		// 奇偶数
		for (int i = 1; i < s.length() - 1; i++) {
			getMaxOfOdd(s, i);
		}

		for (int i = 0; i + 1 < s.length(); i++) {
			char ch1 = s.charAt(i);
			char ch2 = s.charAt(i + 1);

			if (ch1 == ch2) {
				getMaxOfEven(s, i);
			}
		}

		String result = s.substring(startResult, endResult + 1);
		return result;
	}

	private void getMaxOfEven(String data, int i) {
		int x = i - 1;
		int y = i + 2;
		while (x >= 0 && y < data.length()) {
			char ch1 = data.charAt(x);
			char ch2 = data.charAt(y);

			if (ch1 != ch2) {
				if(y - x - 2 + 1> len) {
					len = y - x - 2 + 1;
					startResult = x + 1;
					endResult = y - 1;
				}
				return;
			} else {
				x--;
				y++;
			}
		}
		x++;
		y--;
		if(y - x + 1 > len) {
			len = y - x + 1;
			startResult = x;
			endResult = y;
		}
	}

	private void getMaxOfOdd(String data, int i) {
		int x = i - 1;
		int y = i + 1;
		while (x >= 0 && y < data.length()) {
			char ch1 = data.charAt(x);
			char ch2 = data.charAt(y);

			if (ch1 != ch2) {
				if(y - x - 2 + 1> len) {
					len = y - x - 2 + 1;
					startResult = x + 1;
					endResult = y - 1;
				}
				return;
			} else {
				x--;
				y++;
			}
		}
		x++;
		y--;
		if(y - x + 1 > len) {
			len = y - x + 1;
			startResult = x;
			endResult = y;
		}
	}

	public static void main(String[] args) {
		System.out.println(new a5().longestPalindrome("babad"));
	}
}
