import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/*
18. 4Sum

Given an array S of n integers, are there elements a, b, c, 
and d in S such that a + b + c + d = target? Find all unique quadruplets in the array 
which gives the sum of target.

给定一个数组，问能否在数组中找到不重复的四元组，使得它们的和为0，找出所有这样的四元组
 * */
public class a18 {

	public List<List<Integer>> fourSum(int[] nums, int target) {
		List<List<Integer>> resultList = new ArrayList<>();
		if (nums == null || nums.length < 4)
			return resultList;

		Arrays.sort(nums);

		int lastFirst = nums[0] - 1;
		int lastSecond = nums[0] - 1;

		for (int i = 0; i < nums.length - 3; i++) {
			int first = nums[i];

			if (first == lastFirst)
				continue;
			lastSecond = nums[0] - 1;
			for (int j = i + 1; j < nums.length - 2; j++) {
				int second = nums[j];

				if (lastSecond == second)
					continue;

				int aim = target - first - second;

				int beginInx = j + 1;
				int endInx = nums.length - 1;

				while (beginInx < endInx) {
					int b = nums[beginInx];
					int c = nums[endInx];
					int sum = b + c;
					if (sum == aim) {
						resultList.add(buildTriplets(first, second, b, c));

						while (beginInx + 1 < nums.length && nums[++beginInx] == b)
							;
						while (endInx + 1 < nums.length && nums[++endInx] == c)
							;
					} else if (sum > aim) {
						endInx--;
					} else {
						beginInx++;
					}
				}
				lastSecond = nums[j];
			}

			lastFirst = nums[i];
		}

		return resultList;
	}

	List<Integer> buildTriplets(int a, int b, int c, int d) {
		List<Integer> list = new ArrayList<>();
		list.add(a);
		list.add(b);
		list.add(c);
		list.add(d);
		return list;
	}

}
