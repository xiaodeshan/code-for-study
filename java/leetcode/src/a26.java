/*
26. Remove Duplicates from Sorted Array

Given a sorted array, remove the duplicates in-place such that each element appear only once and return the new length.
Do not allocate extra space for another array, you must do this by modifying the input array in-place with O(1) extra memory.
 
给定一个排序的数组，移除重复的数组元素，返回长度，且不能单独分配空间
 * 
 * */
public class a26 {
	public int removeDuplicates(int[] nums) {
		if (nums == null || nums.length == 0)
			return 0;

		int pos = 0;
		int last = nums[0] - 1;

		for (int i = 0; i < nums.length; i++) {
			if (nums[i] != last) {
				nums[pos] = last = nums[i];
				pos++;
			}
		}
		return pos;
	}

}
