/*
 * 2. Add Two Numbers 
You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.
You may assume the two numbers do not contain any leading zero, except the number 0 itself.

Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8

给出两个非空整数列表来表示两个整数，整数是以逆序列表的形式存储的，可以假设没有前导0除非0本身。

输入 (2 -> 4 -> 3) + (5 -> 6 -> 4) 
输出 (342+465=807 =》7 -> 0 -> 8)

 * */

class ListNode {
	int val;
	ListNode next;

	ListNode(int x) {
		val = x;
	}
}

class a2 {
	public ListNode addTwoNumbers(ListNode l1, ListNode l2) {
		int carry = 0;
		
		ListNode point1 = l1;
		ListNode point2 = l2;
		
		int x1 = point1.val;
		int x2 = point2.val;
		
		point1 = point1.next;
		point2 = point2.next;
		
		carry = (x1 + x2) / 10;
		ListNode ansList = new ListNode(x1 + x2 - carry * 10);
		ListNode tempList = ansList;
			
		while(point1 != null || point2 != null) {
			int ans = add(point1, point2) + carry;
            if(point1 != null){
                point1 = point1.next;
            }
            if(point2 != null){
                point2 = point2.next;
            }
			carry = ans / 10;
			append(tempList, ans - carry * 10);
			tempList = tempList.next;
		}
		
		if(carry != 0)
			append(tempList, 1);
		return ansList;
	}
	
	void append(ListNode list, int data){
		ListNode newNode = new ListNode(data);	
		list.next = newNode;
	}
	
	int add(ListNode l1, ListNode l2) {
		int ans = 0;
		if(l1 != null) {
			ans += l1.val;
		}
		
		if(l2 != null) {
			ans += l2.val;
		}
		
		return ans;
	}
}
