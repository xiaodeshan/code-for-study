/*
24. Swap Nodes in Pairs

Given a linked list, swap every two adjacent nodes and return its head.

For example,
Given 1->2->3->4, you should return the list as 2->1->4->3.

Your algorithm should use only constant space. You may not modify the values in the list, only nodes itself can be changed.
 
 交换相邻的链表节点，只使用常量空间
 
 * 
 * */
public class a24 {
	public class ListNode {
		int val;
		ListNode next;

		ListNode(int x) {
			val = x;
		}
	}

	public ListNode swapPairs(ListNode head) {
		if (head == null || head.next == null)
			return head;

		ListNode temp = head;
		ListNode result = head.next;
		ListNode last = head;
		while (temp != null) {
			last.next = temp.next;
			swapPairsOne(temp);
			last = temp;
			temp = temp.next;
		}

		return result;
	}

	public void swapPairsOne(ListNode head) {
		if (head == null || head.next == null)
			return;
		ListNode t = head.next.next;
		head.next.next = head;
		head.next = t;
	}

}
