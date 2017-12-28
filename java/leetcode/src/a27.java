/*
27. Remove Element

Given an array and a value, remove all instances of that value in-place and return the new length.
Do not allocate extra space for another array, you must do this by modifying the input array in-place with O(1) extra memory.
The order of elements can be changed. It doesn't matter what you leave beyond the new length.
 
给定一个数组，移除指定的元素，返回长度，且不能单独分配空间
 * 
 * */
public class a27 {
	public int removeElement(int[] nums, int val) {
		if (nums == null || nums.length == 0)
			return 0;
		int pos = 0;
		for (int i = 0; i < nums.length; i++) {
			if (nums[i] != val) {
				nums[pos] = nums[i];
				pos++;
			}
		}
		return pos;
	}

}
