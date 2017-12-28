/*
 * 4. Median of Two Sorted Arrays 
There are two sorted arrays nums1 and nums2 of size m and n respectively.
Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).

Example 1:

nums1 = [1, 3]
nums2 = [2]

The median is 2.0

Example 2:

nums1 = [1, 2]
nums2 = [3, 4]

The median is (2 + 3)/2 = 2.5

给定两个长度分别m和n的排序数组
找出这两个数组的中位数，时间复杂度为O(log (m+n)
 * */

class a4 {
	public double findMedianSortedArrays(int[] nums1, int[] nums2) {
		int m = nums1.length;
		int n = nums2.length;

		if (m > n)
			return findMedianSortedArrays(nums2, nums1);
		// m < n
		int start = 0;
		int end = m;

		while (start <= end) {
			int mid = (start + end);
			int midN = (m + n + 1) / 2 - mid;

			if (mid != 0 && nums1[mid - 1] > nums2[midN]) {
				end = mid - 1;
			} else if (midN != 0 && nums1.length != 0 && mid != nums1.length && nums2[midN - 1] > nums1[mid]) {
				start = mid + 1;
			} else {
				int x1 = (mid == 0) ? Integer.MIN_VALUE : nums1[mid - 1];
				int x2 = (midN == 0) ? Integer.MIN_VALUE : nums2[midN - 1];

				int y1 = (mid == m) ? Integer.MAX_VALUE : nums1[mid];
				int y2 = (midN == n) ? Integer.MAX_VALUE : nums2[midN];

				if ((m + n) % 2 == 1)
					return (Math.max(x1, x2));
				return (Math.max(x1, x2) + Math.min(y1, y2)) / 2.0;
			}
		}
		
		return 0;
	}

	public static void main(String[] args) {
		int a1[] = new int[] { 1, 3 };
		int a2[] = new int[] { 2 };

		System.out.println(new a4().findMedianSortedArrays(a1, a2));
	}
}
