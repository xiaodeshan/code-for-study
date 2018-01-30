public class a83 {
	public class ListNode {
		int val;
		ListNode next;

		ListNode(int x) {
			val = x;
		}
	}

	public ListNode deleteDuplicates(ListNode head) {
		if (head == null)
			return head;
		ListNode current = head;
		ListNode nextNode = head.next;

		while (nextNode != null) {
			if (nextNode.val != current.val) {
				current.next = nextNode;
				current = current.next;
			}
			nextNode = nextNode.next;
		}
		current.next = null;	
		return head;
	}
}
