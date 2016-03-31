public class Solution {
    public List<List<Integer>> fourSum(int[] nums, int target) {
        List<List<Integer>> result = new ArrayList<List<Integer>>();
		HashMap<Integer, List<Integer[]>> hashMap = new HashMap<Integer, List<Integer[]>>();

		Arrays.sort(nums);
		for (int i = 0; i < nums.length; i++) {
			for (int j = i + 1; j < nums.length; j++) {
				int sum = nums[i] + nums[j];
				Integer[] tuple = { nums[i], i, nums[j], j };
				if (!hashMap.containsKey(sum)) {
					hashMap.put(sum, new ArrayList<Integer[]>());
				}
				hashMap.get(sum).add(tuple);
			}
		}

		Integer[] keys = hashMap.keySet().toArray(new Integer[hashMap.size()]);
		Arrays.sort(keys);
		for (int key : keys) {
			if (hashMap.containsKey(key)) {
				if (hashMap.containsKey(target - key)) {
					List<Integer[]> firstPairs = hashMap.get(key);
					List<Integer[]> secondPairs = hashMap.get(target - key);

					for (int i = 0; i < firstPairs.size(); i++) {
						Integer[] first = firstPairs.get(i);
						for (int j = 0; j < secondPairs.size(); j++) {
							Integer[] second = secondPairs.get(j);

							if (first[1] != second[1] && first[1] != second[3] && first[3] != second[1]
									&& first[3] != second[3]) {
								List<Integer> validPair = Arrays.asList(first[0], first[2], second[0], second[2]);
								Collections.sort(validPair);
								if (!result.contains(validPair)) {
									result.add(validPair);
								}
							}
						}
					}

					hashMap.remove(key);
					hashMap.remove(target - key);
				}
			}
		}

		return result;
    }
}