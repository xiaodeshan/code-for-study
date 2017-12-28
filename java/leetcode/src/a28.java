/*
27. Implement strStr()

kmp
 
 * 
 * */
public class a28 {
	public int next[];

	public int strStr(String haystack, String needle) {
		if(haystack.equals(needle))
			return 0;
		if(needle.equals(""))
			return 0;
		
		next = new int[needle.length()];

		getNext(needle);
		return kmp(haystack, needle);
	}

	public int kmp(String haystack, String needle) {
		int i = 0, j = 0;
		int size = 0;

		while (i < haystack.length() && j < needle.length()) {
			char ch1 = haystack.charAt(i);
			char ch2 = needle.charAt(j);
			if (ch1 == ch2) {
				i++;
				j++;
				size++;

				if (size == needle.length()) {
					return i - size;
				}
			} else if (next[j] == -1) {
				i++;
				j = 0;
				size = 0;
			} else {
				j = next[j];
				size = j;
			}

		}
		if (size == needle.length()) {
			return haystack.length() - size + 1;
		}
		return -1;
	}

	void getNext(String needle) {
		int k = -1, j = 0;
		next[0] = -1;
		while (j < needle.length() - 1) {
			if (k == -1 || needle.charAt(k) == needle.charAt(j)) {
				++j;
				++k;
				if (needle.charAt(j) != needle.charAt(k)) {
					next[j] = k;
				} else {
					next[j] = next[k];
				}
			} else {
				k = next[k];
			}
		}
	}
	
	public static void main(String[] args) {
		System.out.println(new a28().strStr( "hello",  "llo"));
	}

}
