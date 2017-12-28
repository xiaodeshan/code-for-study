/*
19. Remove Nth Node From End of List

Given a linked list, remove the nth node from the end of list and return its head.

For example,

   Given linked list: 1->2->3->4->5, and n = 2.

   After removing the second node from the end, the linked list becomes 1->2->3->5.
   
   给定一个链表，删除倒数第n个节点并返回表头
 * */
public class a19 {

	public class ListNode {
		int val;
		ListNode next;

		ListNode(int x) {
			val = x;
		}
	}

	public ListNode removeNthFromEnd(ListNode head, int n) {
		ListNode aim = head;
		ListNode aimFather = head;
		ListNode fastNode = head;

		for (int i = 0; i < n; i++)
			fastNode = fastNode.next;

		while (fastNode != null) {
			aimFather = aim;
            aim = aim.next;
			fastNode = fastNode.next;
		}

		if (aim == head)
			return aim.next;
		else {
			aimFather.next = aim.next;
			return head;
		}

	}

}
