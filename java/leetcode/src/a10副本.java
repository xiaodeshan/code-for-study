/*
 * 10. Regular Expression Matching
'.' Matches any single character.
'*' Matches zero or more of the preceding element.

The matching should cover the entire input string (not partial).

The function prototype should be:
bool isMatch(const char *s, const char *p)

Some examples:
isMatch("aa","a") → false
isMatch("aa","aa") → true
isMatch("aaa","aa") → false
isMatch("aa", "a*") → true
isMatch("aa", ".*") → true
isMatch("ab", ".*") → true
isMatch("aab", "c*a*b") → true

正则匹配
 * */
public class a10副本 {

	public boolean isMatch(String s, String p) {
		boolean dp[][] = new boolean[s.length() + 1][p.length() + 1];

		dp[0][0] = true;
		for (int i = 2; i <= p.length(); i = i + 2) {
			char ch = p.charAt(i - 1);

			if (ch == '*') {
				dp[0][i] = true;
			} else {
				break;
			}
		}

		for (int i = 1; i <= s.length(); i++) {
			for (int j = 1; j <= p.length(); j++) {
				char ch1 = s.charAt(i - 1);
				char ch2 = p.charAt(j - 1);

				if (isLetter(ch2) || ch2 == '.') {
					if (isLetter(ch2)) {
						dp[i][j] = (ch1 == ch2) && dp[i - 1][j - 1];
						;
					} else {
						dp[i][j] = dp[i - 1][j - 1];
					}

				} else {
					char lastCh = p.charAt(j - 2);

					boolean result = false;

					for (int k = 0; i - k >= 0; k++) {
						if (k != 0 && !charMatch(s.charAt(i - k), lastCh)) {
							break;
						}
						result = result || dp[i - k][j - 2];
						if (result == true)
							break;

					}
					dp[i][j] = result;

				}
			}
		}

		return dp[s.length()][p.length()];

	}

	public boolean charMatch(char ch1, char ch2) {
		if (ch1 == ch2) {
			return true;
		}
		return ch2 == '.';
	}

	public boolean isLetter(char ch) {
		if (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z')
			return true;
		return false;
	}

	public static void main(String[] args) {
		System.out.println(new a10副本().isMatch("aab", "b.*"));
		// System.out.println(new a10副本().isMatch("aa", "a"));
		// System.out.println(new a10副本().isMatch("aa", "aa"));
		// System.out.println(new a10副本().isMatch("aaa", "aa"));
		// System.out.println(new a10副本().isMatch("aa", "a*"));
		// System.out.println(new a10副本().isMatch("aa", ".*"));
		// System.out.println(new a10副本().isMatch("ab", ".*"));
		// System.out.println(new a10副本().isMatch("aab", "c*a*b*"));
	}
}
