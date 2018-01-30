
public class a53 {
	public int maxSubArray(int[] nums) {
		int maxVal = nums[0];
		int tailMax = nums[0];
		for (int i = 1; i < nums.length; i++) {
			if (tailMax > 0)
				tailMax += nums[i];
			else {
				tailMax = nums[i];
			}

			if (maxVal < tailMax)
				maxVal = tailMax;
		}

		return maxVal;
	}
}
