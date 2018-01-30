import org.junit.jupiter.api.Test;

public class a58 {
    public int lengthOfLastWord(String s) {
    	
    	int len = 0;
    	boolean begin = false;
    	for(int i = s.length() - 1; i >= 0; i--) {
    		char ch = s.charAt(i);
    		if(!begin && ch != ' ') {
    			begin = true;
    			len++;
    		}else if(begin && ch == ' ') {
    			break;
    		}else if(!begin && ch == ' '){
				
			}else {
				len++;
			}
    	}
    	
    	return len;
    }
    
    @Test
    public void testLengthOfLastWord() {
    	assert lengthOfLastWord("") == 0;
    	assert lengthOfLastWord("aaa bbb ccc    d") == 1;
    	assert lengthOfLastWord("     ") == 0;
    	assert lengthOfLastWord("  ffs      ") == 3;
    }
}
