public class Solution {
    public int threeSumClosest(int[] nums, int target) {
        Arrays.sort(nums);
		int min = Integer.MAX_VALUE;
		int result = 0;

		for (int i = 0; i < nums.length; i++) {
			if (i > 0 && nums[i] == nums[i - 1])
				continue;
			int begin = i + 1;
			int end = nums.length - 1;

			while (begin < end) {
				int sum = nums[i] + nums[begin] + nums[end];
				if (sum < target) {
					if (target - sum < min) {
						min = target - sum;
						result = sum;
					}
					begin++;
				} else if (sum > target) {
					if (sum - target < min) {
						min = sum - target;
						result = sum;
					}
					end--;
				} else {
					min = 0;
					return sum;
				}
			}
		}

		return result;
    }
}