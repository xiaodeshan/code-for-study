import java.util.HashMap;

/*
 * 3.Longest Substring Without Repeating Characters 
Given a string, find the length of the longest substring without repeating characters.

Examples:

Given "abcabcbb", the answer is "abc", which the length is 3.

Given "bbbbb", the answer is "b", with the length of 1.

Given "pwwkew", the answer is "wke", with the length of 3. Note that the answer must be a substring, "pwke" is a subsequence and not a substring.

给定一个字符串，找出最长的子串，其中子串不包含任何重复的字符
 * */

class a3 {
	/* 别人的答案 */
	public int lengthOfLongestSubstring(String s) {
		int result = 0;
		HashMap<Character, Integer> map = new HashMap<>();
		for(int i = 0, j = 0; i < s.length(); i++) {
			char ch = s.charAt(i);
			
			if(map.containsKey(ch)) {
				j = Math.max(j, map.get(ch) + 1);
			}
			map.put(ch, i);
			result = Math.max(result, i - j + 1);
		}
		
		return result;
	}
}
