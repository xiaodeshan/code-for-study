/*
9. Palindrome Number
Determine whether an integer is a palindrome. Do this without extra space.

判断一个整数是不是回文数，不能使用额外空间
 * */
public class a9 {
	public boolean isPalindrome(int x) {
		if(x < 0) return false;
		
		int res = 0;
		while(x > res) {
			res = res * 10 + (x % 10);
			x = x/10;
		}
		return res == x || x == res / 10;
	}

	public static void main(String[] args) {
		System.out.println(new a9().isPalindrome(10));
	}
}
