public class a100 {
	public class TreeNode {
		int val;
		TreeNode left;
		TreeNode right;

		TreeNode(int x) {
			val = x;
		}
	}

	public boolean isSameTree(TreeNode p, TreeNode q) {
		if(p == q) {
			return true;
		}
		
		if(p == null || q == null)
			return false;
		
		if(p.val != q.val) {
			return false;
		}
		
		return isSameTree(p.left, q.left) && isSameTree(p.right, q.right);
	}
}
