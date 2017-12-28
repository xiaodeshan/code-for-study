import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Queue;
import java.util.Set;
import java.util.Map.Entry;

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
public class a10 {
	public boolean isMatch(String s, String p) {
		if (p.equals(s)) {
			return true;
		}

		if (p.equals("")) {
			return false;
		}
		NFA nfa = buildNfa(0, p.length() - 1, p);
		// nfa.print();

		DFANode dfaNode = transformDFA(nfa);

		DFA dfa = new DFA(dfaNode);
		//dfa.print();
		return dfa.match(s);
	}

	private static DFANode transformDFA(NFA nfa) {
		List<NFANode> firstList = new ArrayList<>();
		firstList.add(nfa.start);
		DFANode firstNode = NFANode.epClosure(firstList, nfa.start.nfaNum, nfa.end.nfaNum);
		// firstNode.print();
		firstNode.setNum();
		Queue<DFANode> queue = new LinkedList<>();
		queue.add(firstNode);

		HashMap<DFANode, DFANode> dfmap = new HashMap<>();
		dfmap.put(firstNode, firstNode);

		while (!queue.isEmpty()) {
			DFANode tempNode = queue.poll();

			for (Entry<Character, List<NFANode>> entry : tempNode.map.entrySet()) {
				char ch = entry.getKey();

				List<NFANode> nfaNodes = entry.getValue();

				DFANode tempResult = NFANode.epClosure(nfaNodes, nfa.start.nfaNum, nfa.end.nfaNum);
				// tempResult.print();
				DFANode findNode = dfmap.get(tempResult);
				if (findNode != null) {
					tempNode.acceptList.put(ch, findNode);
				} else {
					tempResult.setNum();
					tempNode.acceptList.put(ch, tempResult);
					queue.add(tempResult);
					dfmap.put(tempResult, tempResult);
				}

			}
		}

		return firstNode;
	}

	NFA buildNfa(int start, int end, String str) {
		NFA nfa = buildNfa0(start, end, str);

		nfa.start.setStart();
		nfa.end.setEnd();

		return nfa;
	}

	NFA buildNfa0(int start, int end, String str) {
		if (start > end) {
			// throw new RuntimeException("error index");
			return null;
		}

		char startCh = str.charAt(start);

		if (start == end) {
			NFA nfa = new NFA(str.charAt(start));

			return nfa;
		} else {
			assert start != (str.length() - 1);
			char nextChar = str.charAt(start + 1);

			if (nextChar == '*')
				return and(closureChar(startCh), buildNfa0(start + 2, end, str));
			else {
				return and(new NFA(startCh), buildNfa0(start + 1, end, str));
			}
		}
	}

	NFA and(NFA nfa1, NFA nfa2) {
		if (nfa1 == null)
			return nfa2;
		if (nfa2 == null)
			return nfa1;

		nfa1.end.addPair(NFA.ep, nfa2.start);
		nfa1.end = nfa2.end;
		return nfa1;
	}

	NFA closure(NFA nfa1) {
		assert nfa1 != null;
		NFANode node1 = NFANode.createNfa();
		NFANode node2 = NFANode.createNfa();

		node1.addPair(NFA.ep, nfa1.start);
		node1.addPair(NFA.ep, node2);
		nfa1.end.addPair(NFA.ep, nfa1.start);
		nfa1.end.addPair(NFA.ep, node2);

		return new NFA(node1, node2);
	}

	NFA closureChar(char ch) {
		return closure(new NFA(ch));
	}

	public class NFA {
		public NFANode start;
		public NFANode end;

		public static final char ep = 0;

		public NFA(char ch) {
			start = NFANode.createNfa();
			end = NFANode.createNfa();

			start.addPair(ch, end);
		}

		public NFA() {

		}

		public NFA(NFANode start, NFANode end) {
			this.end = end;
			this.start = start;
		}

		public void print() {
			System.out.println("start : " + start.nfaNum + " end : " + end.nfaNum);
			for (Entry<Integer, NFANode> entry : NFANode.debugMap.entrySet()) {
				entry.getValue().print();
			}
			System.out.println("-----------");
		}
	}

	public static class DFA {
		public static int total = 0;

		public static List<DFANode> nodes = new ArrayList<>();

		public DFANode fisrtNode;

		public DFA(DFANode first) {
			this.fisrtNode = first;
		}

		public void print() {
			System.out.println("dfa");
			System.out.println("start : " + fisrtNode.num);
			for (DFANode node : nodes) {
				System.out.println(String.format("num [%d] %s", node.num, node.states.toString()));
				if (node.acceptList != null) {
					for (Entry<Character, DFANode> entry : node.acceptList.entrySet()) {
						System.out
								.println(String.format("%d - %c - %d", node.num, entry.getKey(), entry.getValue().num));
					}
				}
			}
		}

		public boolean match(String data) {
			DFANode temp = fisrtNode;
			for (int i = 0; i < data.length(); i++) {
				char ch = data.charAt(i);

				DFANode nextnode = temp.acceptList.get(ch);

				if (nextnode == null) {
					DFANode nextDotNode = temp.acceptList.get('.');
					if (nextDotNode != null) {
						temp = nextDotNode;
						continue;
					}
					return false;
				} else {
					temp = nextnode;
					continue;
				}
			}

			return temp.states.isEnd();
		}
	}

	public static class DFANode {
		private Set<Integer> set = new HashSet<>();
		/* 状态 */
		public DFANFAState states = new DFANFAState();

		public int num;

		public Map<Character, List<NFANode>> map = new HashMap<>();
		/* 接收列表 */
		public Map<Character, DFANode> acceptList = new HashMap<>();

		public DFANode(Set<Integer> set, DFANFAState states, Map<Character, List<NFANode>> map) {
			this.set = set;
			this.states = states;
			this.map = map;
		}

		@Override
		public boolean equals(Object obj) {
			if (obj instanceof DFANode) {
				DFANode node = (DFANode) obj;

				return node.set.equals(set);
			}
			return false;
		}

		@Override
		public int hashCode() {
			return set.hashCode();
		}

		void setNum() {
			num = DFA.total;
			DFA.total++;

			DFA.nodes.add(this);
		}

		void setNum(int sum) {
			this.num = sum;

			DFA.nodes.add(this);
		}

		public void print() {
			System.out.print("set:");
			for (Integer index : set) {
				System.out.print(index + " ");
			}

			System.out.println();

			System.out.println(String.format("num [%d]", num));
			for (Entry<Character, DFANode> entry : acceptList.entrySet()) {
				System.out.println(String.format("%d - %c - %d", num, entry.getKey(), entry.getValue().num));
			}

			System.out.println();
		}
	}

	public static class NFANode {

		/* 节点编号 */
		public int nfaNum;
		/* 状态 */
		public DFANFAState states = new DFANFAState();

		/* 接收列表 */
		public Map<Character, NFANode> acceptList = new HashMap<>();
		/* ξ列表 */
		public List<NFANode> list = new ArrayList<>();

		public NFANode(int nfaNum) {
			this.nfaNum = nfaNum;
		}

		public static int total = 0;

		public static NFANode createNfa() {
			NFANode nfaNode = new NFANode(total);

			debugMap.put(total, nfaNode);

			total++;

			return nfaNode;
		}

		public static Map<Integer, NFANode> debugMap = new HashMap<>();

		public void setStart() {
			states.setStart();
		}

		public void setEnd() {
			states.setEnd();
		}

		public void addPair(Character ch, NFANode node) {
			if (ch == 0) {
				list.add(node);
				return;
			}
			acceptList.put(ch, node);
		}

		public void print() {
			System.out.println(String.format("node [%d]", nfaNum));
			for (Entry<Character, NFANode> entry : acceptList.entrySet()) {
				System.out.println(String.format("%d - %c - %d", nfaNum, entry.getKey(), entry.getValue().nfaNum));
			}

			for (NFANode node : list) {
				System.out.println(String.format("%d - ξ - %d", nfaNum, node.nfaNum));
			}

			System.out.println();
		}

		public static DFANode epClosure(List<NFANode> nodes, int start, int end) {
			Queue<Integer> queue = new LinkedList<>();
			Set<Integer> resultSet = new HashSet<>();
			Map<Character, List<NFANode>> map = new HashMap<>();
			boolean exist[] = new boolean[total];

			for (NFANode node_ : nodes) {
				queue.add(node_.nfaNum);
				exist[node_.nfaNum] = true;
			}

			DFANFAState states = DFANFAState.getnone();
			while (!queue.isEmpty()) {
				Integer head = queue.poll();
				resultSet.add(head);

				NFANode headNode = debugMap.get(head);

				if (headNode.nfaNum == start) {
					states.setStart();
				}
				if (headNode.nfaNum == end) {
					states.setEnd();
				}

				for (Entry<Character, NFANode> tNfaNode : headNode.acceptList.entrySet()) {
					// 同一个点对应的字母可能有多个流向，如'a*a'
					List<NFANode> charList = map.get(tNfaNode.getKey());

					if (charList == null) {
						charList = new ArrayList<>();
					}
					charList.add(tNfaNode.getValue());
					map.put(tNfaNode.getKey(), charList);
				}

				for (NFANode temp : headNode.list) {
					if (!exist[temp.nfaNum]) {
						exist[temp.nfaNum] = true;

						queue.add(temp.nfaNum);

					}
				}
			}
			return new DFANode(resultSet, states, map);

		}
	}

	public static class DFANFAState {

		private static final int start = 0x1;
		private static final int end = 0x10;
		private static final int none = 0x100;

		private int stateRaw = none;

		public boolean isStart() {
			return (stateRaw & start) == start;
		}

		public boolean isEnd() {
			return (stateRaw & end) == end;
		}

		public void setStart() {
			stateRaw = stateRaw | start;
		}

		public void setEnd() {
			stateRaw = stateRaw | end;
		}

		public static DFANFAState getnone() {
			return new DFANFAState();
		}

		@Override
		public String toString() {
			List<String> list = new ArrayList<>();
			if (isStart()) {
				list.add("start");
			}
			if (isEnd()) {
				list.add("end");
			}
			if (list.size() == 0) {
				list.add("none");
			}

			return list.toString();

		}
	}

	public static void main(String[] args) {
		System.out.println(new a10().isMatch("bbbba", ".*a*a"));
	}
}
