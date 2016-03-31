/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode(int x) { val = x; }
 * }
 */
public class Solution {
    public ListNode addTwoNumbers(ListNode l1, ListNode l2) {
        ListNode p1, p2, head, pLast;
		int tmp = 0;

		head = new ListNode(-1);
		pLast = head;
		for (p1 = l1, p2 = l2; p1 != null && p2 != null; p1 = p1.next, p2 = p2.next) {
			pLast.next = new ListNode(0);
			pLast = pLast.next;
			int sum = p1.val + p2.val + tmp;
			pLast.val = sum % 10;
			tmp = sum / 10;
		}
		while (p1 != null) {
			pLast.next = new ListNode(0);
			pLast = pLast.next;
			int sum = p1.val + tmp;
			pLast.val = sum % 10;
			tmp = sum / 10;
			p1 = p1.next;
		}

		while (p2 != null) {
			pLast.next = new ListNode(0);
			pLast = pLast.next;
			int sum = p2.val + tmp;
			pLast.val = sum % 10;
			tmp = sum / 10;
			p2 = p2.next;
		}
		if (tmp != 0) {
			pLast.next = new ListNode(0);
			pLast = pLast.next;
			pLast.val = tmp;
			tmp = 0;
		}
		
		return head.next;
    }
}