/*
25. Reverse Nodes in k-Group

Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.
k is a positive integer and is less than or equal to the length of the linked list. If the number of nodes is not a multiple of k then left-out nodes in the end should remain as it is.
You may not alter the values in the nodes, only nodes itself may be changed.
Only constant memory is allowed.
 
 交换k个相邻的链表节点，只使用常量空间，这里k是正整数且小于等于列表长
 * 
 * */
public class a25 {
	public static class ListNode {
		int val;
		ListNode next;

		ListNode(int x) {
			val = x;
		}
	}

	public ListNode reverseKGroup(ListNode head, int k) {
		if (isLongK(head, k)) {
			ListNode nextRecursionNode = null;
			ListNode afterNode = head;
			ListNode beforeNode = null;
			ListNode tempNode = afterNode.next;
			ListNode result = null;
			for (int i = 0; i < k; i++) {
				if (i == k - 1) {
					nextRecursionNode = afterNode.next;
					result = afterNode;
				}
				tempNode = afterNode.next;
				afterNode.next = beforeNode;
				beforeNode = afterNode;
				afterNode = tempNode;
			}
			head.next = reverseKGroup(nextRecursionNode, k);

			return result;
		} else {
			return head;
		}
	}

	boolean isLongK(ListNode head, int k) {
		if (head == null)
			return false;
		int count = 0;
		ListNode temp = head;
		while (temp != null) {
			++count;
			temp = temp.next;
			if (count >= k)
				return true;
		}
		return false;

	}

}
