import java.util.Stack;

/*
20. Valid Parentheses

Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

The brackets must close in the correct order, "()" and "()[]{}" are all valid but "(]" and "([)]" are not.
   
   给定包含'(', ')', '{', '}', '[' 和 ']'字符的字符串，判断输入串是否合法
 * */
public class a20 {

	public boolean isValid(String s) {
		Stack<Character> stack = new Stack<>();

		for (int i = 0; i < s.length(); i++) {
			char ch = s.charAt(i);

			if (!isPop(ch)) {
				stack.push(ch);
			} else {
				if (stack.isEmpty()) {
					return false;
				}

				Character popCh = stack.pop();

				if (!isMathch(popCh, ch))
					return false;
			}
		}

		return stack.isEmpty();
	}

	boolean isPop(char ch) {
		if (ch == '(' || ch == '{' || ch == '[') {
			return false;
		}
		return true;
	}

	boolean isMathch(char ch1, char ch2) {
		if (ch1 == '(' && ch2 == ')' || ch1 == '[' && ch2 == ']' || ch1 == '{' && ch2 == '}') {
			return true;
		}
		return false;
	}

}
