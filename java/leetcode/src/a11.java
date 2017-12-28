/*
11. Container With Most Water
Given n non-negative integers a1, a2, ..., an, 
where each represents a point at coordinate (i, ai). 
n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0). 
Find two lines, which together with x-axis forms a container, 
such that the container contains the most water.

Note: You may not slant the container and n is at least 2.

给定n个非负整数a1, a2, ..., an,它们分别表示坐标系上的点 (i, ai)
有n条垂直的直线，它们端点分别为(i, ai)和(i, 0)
找到两条线，它们与x轴构成一个容器，且这个容器里面有最多的水

注意：你不能倾斜容器，且n大于等于2
 * */
public class a11 {
	public int maxArea(int[] height) {
		int i = 0;
		int j = height.length - 1;
		int ans = 0;

		while (i < j) {
			ans = Math.max(ans, Math.min(height[i], height[j]) * (j - i));
			
			if(height[i] > height[j])
				j--;
			else {
				i++;
			}
		}
		
		return ans;
	}
}
