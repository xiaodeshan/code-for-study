import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class a47 {

	List<List<Integer>> resultLists = new ArrayList<>();

	public List<List<Integer>> permuteUnique(int[] nums) {
		getPermutations(nums, 0);

		return resultLists;
	}

	void getPermutations(int nums[], int begin) {
		if (begin == nums.length - 1) {
			List<Integer> tempList = new ArrayList<>();

			for (int k : nums) {
				tempList.add(k);
			}
			resultLists.add(tempList);
			return;
		}

		HashMap<Integer, HashMap<Integer, Boolean>> map = new HashMap<>();

		for (int i = begin; i <= nums.length - 1; i++) {
			if (!isExist(map, nums[begin], nums[i])) {
				insert(map, nums[begin], nums[i]);
				swap(nums, begin, i);
				getPermutations(nums, begin + 1);
				swap(nums, begin, i);
			}
		}
	}

	private void insert(HashMap<Integer, HashMap<Integer, Boolean>> map, int i, int j) {
		HashMap<Integer, Boolean> hashMap = map.get(i);
		if (hashMap == null) {
			hashMap = new HashMap<>();
			map.put(i, hashMap);
		}

		hashMap.put(j, true);
	}

	private boolean isExist(HashMap<Integer, HashMap<Integer, Boolean>> map, int i, int j) {
		HashMap<Integer, Boolean> hashMap = map.get(i);

		if (hashMap == null)
			return false;

		if (hashMap.get(j) == null)
			return false;

		return true;
	}

	private void swap(int[] nums, int begin, int i) {
		int t = nums[begin];
		nums[begin] = nums[i];
		nums[i] = t;
	}

	public static void main(String[] args) {
		int nums[] = { 1, 1, 2, 2 };

		List<List<Integer>> permute = new a47().permuteUnique(nums);

		System.out.println(permute);
	}

}
