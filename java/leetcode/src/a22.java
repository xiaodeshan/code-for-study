import java.util.ArrayList;
import java.util.List;
import java.util.Stack;

/*
22. Generate Parentheses

Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.
   
   给定n对括号，写一个函数输出所有结构完好的括号组合
 * */
public class a22 {

	public List<String> generateParenthesis(int n) {
		solve(n, n);
		return list;
	}

	public Stack<Character> stack = new Stack<>();

	public List<String> list = new ArrayList<>();
	public StringBuilder builder = new StringBuilder();

	public void solve(int n, int in) {
		if (in == 0 && stack.isEmpty()) {
			list.add(builder.toString());
			return;
		}

		if (in != 0) {
			stack.push('(');
			builder.append('(');
			solve(n, in - 1);
			stack.pop();
			builder.deleteCharAt(builder.length() - 1);
		}

		if (!stack.isEmpty()) {
			stack.pop();
			builder.append(')');
			solve(n, in);
			stack.push('(');
			builder.deleteCharAt(builder.length() - 1);
		}
	}

}
