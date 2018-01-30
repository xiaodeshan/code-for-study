import org.junit.jupiter.api.Test;

public class a66 {
    public int[] plusOne(int[] digits) {
    	int jinwei = 0;
    	boolean newSpace = false;
    
    	digits[digits.length - 1]++;
    	for(int i = digits.length - 1; i >= 0; i--) {  		
    		digits[i] += jinwei;
    		if(digits[i] >= 10) {
    			digits[i] -= 10;
    			jinwei = 1;
    			
    			if(i == 0) {
    				newSpace = true;
    				break;
    			}
    		}else {
				jinwei = 0;
				break;
			}    			
    	}
    	
    	if(newSpace) {
    		int result[] = new int[digits.length + 1];
    		result[0] = 1;
    		for(int i = 1; i < result.length; i++) {
    			result[i] = 0;
    		}
    		
    		return result;
    	}else {
    		return digits;
		}
    	
    	
    }
    
    @Test
    void testPlusOne() {
    	int data[] = {9, 9, 9, 9};
    	
    	int result[] = plusOne(data);
    	
    	for(int i = 0; i < result.length; i++) {
    		System.out.print(result[i]);
    	}
    }
}
