import java.util.ArrayList;
import java.util.List;

/*
23. Merge k Sorted Lists

Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.
   
   合并k个排序好的列表
 * */
public class a23 {

	public static class ListNode {
		int val;
		ListNode next;

		ListNode(int x) {
			val = x;
		}
	}

	public class HeapNode implements Comparable<HeapNode> {
		public int value;
		public int index;

		public HeapNode(int value, int index) {
			this.index = index;
			this.value = value;
		}

		@Override
		public int compareTo(HeapNode o) {
			if (o.value < value)
				return -1;
			else if (o.value > value) {
				return 1;
			}
			return 0;
		}

	}

	public class MyHeap {
		private int size = 0;

		HeapNode heapArray[];

		public MyHeap(int cap, List<HeapNode> dataList) {
			heapArray = new HeapNode[cap];

			for (int i = 0; i < dataList.size(); i++) {
				heapArray[i] = dataList.get(i);
			}
			size = dataList.size();
			adjustAll();
		}

		void adjustAll() {
			for(int i = (size - 2) / 2; i >= 0; i--) {
				adjustDown(i);
			}
		}

		void adjustDown(int place) {
			HeapNode curNode = heapArray[place];
			int max = place;

			while (true) {
				int left = place * 2 + 1;
				int right = place * 2 + 2;

				if (left < size && heapArray[left].compareTo(heapArray[max]) > 0) {
					max = left;
				}

				if (right < size && heapArray[right].compareTo(heapArray[max]) > 0) {
					max = right;
				}

				if (max != place) {
					heapArray[place] = heapArray[max];
					heapArray[max] = curNode;
					place = max;
				} else {
					break;
				}
			}
		}

		public HeapNode getHead() {
			return heapArray[0];
		}

		public void setHead(HeapNode head) {
			heapArray[0] = head;
		}

		public boolean isEmpty() {
			return size == 0;
		}

		public void removeHead() {
			heapArray[0] = heapArray[size - 1];
			size--;

			adjustDown(0);
		}
	}

	public ListNode result = null;
	public ListNode lastTemp = null;

	public ListNode mergeKLists(ListNode[] lists) {
		List<HeapNode> list = new ArrayList<>();
		int trueExist = 0;
		for (int i = 0; i < lists.length; i++) {
			if (lists[i] != null) {
				list.add(new HeapNode(lists[i].val, i));
				trueExist++;
			}

		}

		MyHeap heap = new MyHeap(trueExist, list);

		while (!heap.isEmpty()) {
			HeapNode tempNode = heap.getHead();
			append(tempNode.value);

			if (lists[tempNode.index].next != null) {
				heap.setHead(new HeapNode(lists[tempNode.index].next.val, tempNode.index));
				heap.adjustDown(0);
				lists[tempNode.index] = lists[tempNode.index].next;
			} else {
				heap.removeHead();
			}
		}
		return result;
	}

	void append(int val) {
		ListNode node = new ListNode(val);

		if (result == null) {
			result = node;
			lastTemp = node;
			return;
		} else {
			lastTemp.next = node;
			lastTemp = lastTemp.next;
		}

	}
	
    public ListNode mergeKLists(ArrayList<ListNode> lists) {
    	ListNode[] listNodes = new ListNode[lists.size()];
    	
    	for(int i = 0; i < lists.size(); i++) {
    		listNodes[i] = lists.get(i);
    	}
        return mergeKLists(listNodes);
    }

	public static void main(String[] args) {
		ListNode listNode1 = new ListNode(-8);
		ListNode listNode2 = new ListNode(-2);
		ListNode listNode3 = new ListNode(-10);

		ListNode[] nodes = { listNode1, listNode2, listNode3 };
		new a23().mergeKLists(nodes);

	}
	
	

}
