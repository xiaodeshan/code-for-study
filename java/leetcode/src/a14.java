/*
14. Longest Common Prefix

Write a function to find the longest common prefix string amongst an array of strings.

写一个函数，在字符串数组中找到最长的公共前缀
 * */
public class a14 {

	public String longestCommonPrefix(String[] strs) {
		if (strs == null || strs.length == 0) {
			return "";
		}

		int end = 0;
		for (int i = 0; i < strs[0].length(); i++) {
			if (match(strs, i))
				end++;
			else {
				break;
			}
		}

		return strs[0].substring(0, end);
	}

	public boolean match(String[] strs, int pos) {
		char ch = strs[0].charAt(pos);

		for (int i = 0; i < strs.length; i++) {
			if (strs[i].length() <= pos || strs[i].charAt(pos) != ch)
				return false;
		}
		return true;
	}
	
	
}
