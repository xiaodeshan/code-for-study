import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/*
15. 3Sum

Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.

Note: The solution set must not contain duplicate triplets.

给定一个数组，问能否在数组中找到不重复的三元组，使得它们的和为0，找出所有这样的三元组
 * */
public class a15 {

	public List<List<Integer>> threeSum(int[] nums) {
		List<List<Integer>> resultList = new ArrayList<>();
		if (nums == null || nums.length < 3)
			return resultList;

		Arrays.sort(nums);

		int lastFirst = nums[0] - 1;

		for (int i = 0; i < nums.length - 2; i++) {
			int first = nums[i];
			if (first == lastFirst) {
				continue;
			}

			int aim = -first;

			int beginInx = i + 1;
			int endInx = nums.length - 1;

			while (beginInx < endInx) {
				int b = nums[beginInx];
				int c = nums[endInx];
				int sum = b + c;
				if (sum == aim) {
					resultList.add(buildTriplets(first, b, c));

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
			
			lastFirst = nums[i];
		}

		return resultList;
	}

	List<Integer> buildTriplets(int a, int b, int c) {
		List<Integer> list = new ArrayList<>();
		list.add(a);
		list.add(b);
		list.add(c);

		return list;
	}

}
