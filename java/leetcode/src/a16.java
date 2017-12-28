import java.util.Arrays;

/*
16. 3Sum Closest

Given an array S of n integers, find three integers in S such that the sum is 
closest to a given number, target. 
Return the sum of the three integers. 
You may assume that each input would have exactly one solution.

给定一个数组，找到三个数，使得它们的和最接近目标数
 * */
public class a16 {

	public int threeSumClosest(int[] nums, int target) {
		if (nums == null || nums.length < 3)
			return 0;
		Arrays.sort(nums);
		int lastFirst = nums[0] - 1;
		int resultSum = 0x7f7f7f7f;

		for (int i = 0; i < nums.length - 2; i++) {
			int first = nums[i];
			if (first == lastFirst) {
				continue;
			}

			int aim = target - first;

			int beginInx = i + 1;
			int endInx = nums.length - 1;

			while (beginInx < endInx) {
				int b = nums[beginInx];
				int c = nums[endInx];
				int sum = b + c;
				if (sum == aim) {
					return target;
				} else if (sum > aim) {
					if (moreClose(first, b, c, target, resultSum))
						resultSum = first + b + c;
					endInx--;
				} else {
					if (moreClose(first, b, c, target, resultSum))
						resultSum = first + b + c;
					beginInx++;
				}
			}

			lastFirst = nums[i];
		}

		return resultSum;

	}

	public boolean moreClose(int a, int b, int c, int target, int lastSum) {
		return Math.abs(a + b + c - target) < Math.abs(lastSum - target);
	}

}
