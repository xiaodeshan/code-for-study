import java.util.ArrayList;
import java.util.List;

/*
17. Letter Combinations of a Phone Number

Given a digit string, return all possible letter combinations that the number could represent.

A mapping of digit to letters (just like on the telephone buttons) is given below.

给定一个由数字构成的字符串，求出它们可以表示出的字符组合
在数字与字母间的映射和手机按键是对应的
 * */
public class a17 {

	public StringBuilder builder = new StringBuilder();
	public char[][] mapping = { {}, {}, { 'a', 'b', 'c' }, { 'd', 'e', 'f' }, { 'g', 'h', 'i' }, { 'j', 'k', 'l' },
			{ 'm', 'n', 'o' }, { 'p', 'q', 'r', 's' }, { 't', 'u', 'v' }, { 'w', 'x', 'y', 'z' } };

	public List<String> letterCombinations(String digits) {
		List<String> list = new ArrayList<>();
		if (digits == null || digits.length() == 0)
			return list;

		build(0, digits, list);

		return list;
	}

	private void build(int pos, String digits, List<String> list) {
		if (pos == digits.length()) {
			list.add(builder.toString());
			return;
		}
		
		int index = digits.charAt(pos) - '0';
		
		for (int i = 0; i < mapping[index].length; i++) {
			builder.append(mapping[index][i]);
			build(pos + 1, digits, list);
			builder.deleteCharAt(pos);
		}
	}

}
