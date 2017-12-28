import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class a46 {

	List<List<Integer>> resultLists = new ArrayList<>();

	public List<List<Integer>> permute(int[] nums) {
		getPermutations(nums, 0);

		return resultLists;
	}

	void getPermutations(int nums[], int begin) {
		if (begin == nums.length - 1) {
			List<Integer> tempList = new ArrayList<>();
			
			for(int k : nums) {
				tempList.add(k);
			}			
			resultLists.add(tempList);
			return;
		}

		for (int i = begin; i <= nums.length - 1; i++) {
			swap(nums, begin, i);
			getPermutations(nums, begin + 1);
			swap(nums, begin, i);
		}
	}

	private void swap(int[] nums, int begin, int i) {
		int t = nums[begin];
		nums[begin] = nums[i];
		nums[i] = t;
	}

	public static void main(String[] args) {
		int nums[] = { 1, 2, 3 };

		List<List<Integer>> permute = new a46().permute(nums);

		System.out.println(permute);
	}

}
