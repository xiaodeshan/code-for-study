
import java.util.HashMap;
import java.util.Map;

/*
 * 1. Two Sum 
 Given an array of integers, return indices of the two numbers such that they add up to a specific target.
 You may assume that each input would have exactly one solution, and you may not use the same element twice.

  给定一个整数数组，返回两个索引，其中索引对应的两个数的和等于某个目标值，可以假定输入的数只对应一组满足条件的数据，并且
  同一个数不能使用两次
 * */

public class a1 {
	public int[] twoSum(int[] nums, int target) {
		int len = nums.length;
		Map<Integer, Integer> map = new HashMap<>();

		for (int i = 0; i < len; i++) {
			int data = nums[i];
			int aim = target - data;

			if (map.containsKey((aim))) {
				return new int[] { map.get(aim), i };
			}
			
			map.put(data, i);
		}

		return null;
	}
}
