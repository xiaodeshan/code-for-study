import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/*
30. Substring with Concatenation of All Words

You are given a string, s, and a list of words, words, that are all of the same length. Find all starting indices of substring(s) in s that is a concatenation of each word in words exactly once and without any intervening characters.

For example, given:
s: "barfoothefoobarman"
words: ["foo", "bar"]

You should return the indices: [0,9].
(order does not matter).
 
 找到所有s的索引，使得从该索引开始，所有word里面的字符串刚好出现一次，word里每一个字符串长度相同
 
 * 
 * */
public class a30 {
	public List<Integer> findSubstring(String s, String[] words) {
		if (s == null || s.length() == 0)
			return new ArrayList<>();

		Map<String, Integer> dataMap = new HashMap<>();
		for (int i = 0; i < words.length; i++) {
			Integer times = dataMap.get(words[i]);
			int time = (times == null) ? 1 : times + 1;
			dataMap.put(words[i], time);
		}

		List<Integer> resultList = new ArrayList<>();
		int len = words[0].length();
		int total = len * words.length;

		for (int i = 0; i < len; i++) {
			Map<String, Integer> tempMap = new HashMap<>();
			tempMap.putAll(dataMap);
			for (int j = i; j + total - 1 < s.length(); j = j + len) {
				if (j == i) {
					for (int k = 0; k < words.length; k++) {
						String tempAddString = s.substring(j + len * k, j + len * k + len);
						adjust(dataMap, tempMap, tempAddString, null);
					}

					if (tempMap.size() == 0)
						resultList.add(j);
					continue;
				}

				String addString = s.substring(j + total - len, j + total);
				String passString = null;
				if (j - len >= 0)
					passString = s.substring(j - len, j);
				if (dataMap.containsKey(addString)) {
					boolean state = adjust(dataMap, tempMap, addString, passString);

					if (state == true) {
						resultList.add(j);
					}
				} else {
					adjust(dataMap, tempMap, null, passString);
				}

			}
		}

		return resultList;
	}

	private boolean adjust(Map<String, Integer> dataMap, Map<String, Integer> tempMap, String addString,
			String passString) {
		if (passString != null) {
			if (dataMap.containsKey(passString)) {
				Integer passInteger = tempMap.get(passString);
				if (passInteger == null) {
					tempMap.put(passString, 1);
				} else {
					if (passInteger == -1)
						tempMap.remove(passString);
					else {
						tempMap.put(passString, passInteger + 1);
					}
				}

			}
		}

		if (addString == null)
			return false;
		if(!dataMap.containsKey(addString))
			return false;
		Integer addInteger = tempMap.get(addString);
		if (addInteger != null) {
			if (addInteger == 1)
				tempMap.remove(addString);
			else {
				tempMap.put(addString, addInteger - 1);
			}
		} else {
			tempMap.put(addString, -1);
		}

		return tempMap.size() == 0;

	}

	public static void main(String[] args) {
		String[] words = { "fooo", "barr", "wing", "ding", "wing" };
		String s = "lingmindraboofooowingdingbarrwingmonkeypoundcake";
		List<Integer> ans = new a30().findSubstring(s, words);

		for (Integer x : ans) {
			System.out.println(x);
		}

	}
}
