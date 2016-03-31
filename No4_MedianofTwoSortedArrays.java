
public class Solution {
	public static double findKMinFromTwoSortedArray(int[] a, int aStart, int[] b, int bStart, int k) {
		int aLength = a.length - aStart, bLength = b.length - bStart;
		
		if(k > aLength + bLength) {
			System.out.println("Kth min num does not exist");
			System.exit(-1);
		}
		if (aLength > bLength)
			return findKMinFromTwoSortedArray(b, bStart, a, aStart, k);
		if (aLength == 0)
			return b[bStart + k - 1];
		if (k == 1)
			return a[aStart] < b[bStart] ? a[aStart] : b[bStart];
		int pa = k / 2 < aLength ? k / 2 : aLength;
		int pb = k -pa;
		if (a[aStart + pa - 1] < b[bStart + pb - 1]) {
			return findKMinFromTwoSortedArray(a, aStart + pa, b, bStart, k - pa);
		} else if (a[aStart + pa - 1] > b[bStart + pb - 1]) {
			return findKMinFromTwoSortedArray(a, aStart, b, bStart + pb, k - pb);
		} else {
			return a[aStart + pa - 1];
		}
	}

	public static double findMedianSortedArrays(int[] nums1, int[] nums2) {
		int total = nums1.length + nums2.length;
		if (total % 2 == 1) {
			return findKMinFromTwoSortedArray(nums1, 0, nums2, 0, total / 2 + 1);
		} else {
			return (findKMinFromTwoSortedArray(nums1, 0, nums2, 0, total / 2)
					+ findKMinFromTwoSortedArray(nums1, 0, nums2, 0, total / 2 + 1)) / 2;
		}
	}
}
