#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <cstdlib>
#include <algorithm>
#include <sstream>
#include <unordered_map>
#include <cmath>
#include <queue>

using namespace std;

template <typename T>
string toString(T val)
{
    stringstream stream;
    stream << val;
    return stream.str();
}

string longestCommonPrefix(vector<string>& strs)
{
    string longestPrefix;
    if (strs.size() == 0)
        return longestPrefix;
    for(int i = 0; ; i++)
    {
        if (strs[0].length() <= i)
            return longestPrefix;
        char c = strs[0][i];
        for(int j = 1; j < strs.size(); j++)
        {
            if (strs[j].length() <= i || strs[j][i] != c)
                return longestPrefix;
        }
        longestPrefix.append(1, c);
    }
}

void combination(vector<string>& result, string tmp, vector<string> dic, string digits, int level)
{
    if (level >= digits.length())
    {
        if (tmp.length() > 0)
            result.push_back(tmp);
        return;
    }
    int index = digits[level]  - '0';
    for(int i = 0; i < dic[index].length(); i++)
    {
        tmp.push_back(dic[index][i]);
        combination(result, tmp, dic, digits, level + 1);
        tmp.pop_back();
    }
}

vector<string> letterCombinations(string digits)
{
    vector<string> result;
    vector<string> dic;
    string tmp;
    dic.push_back("");
    dic.push_back("");
    dic.push_back("abc");
    dic.push_back("def");
    dic.push_back("ghi");
    dic.push_back("jkl");
    dic.push_back("mno");
    dic.push_back("pqrs");
    dic.push_back("tuv");
    dic.push_back("wxyz");
    combination(result, tmp, dic, digits, 0);
    return result;
}

void generate(int left, int right, string s, vector<string>& result)
{
    if (left == 0 && right == 0)
    {
        result.push_back(s);
        return ;
    }
    if (left > 0)
        generate(left - 1, right, s + "(", result);
    if (right > 0 && left < right)
        generate(left, right - 1, s + ")", result);
}
vector<string> generateParenthesis(int n)
{
    vector<string> result;
    string s;
    if (n <= 0)
        return result;
    generate(n, n, s, result);
    return result;
}

bool isValid(string s)
{
    stack<char> parenthesesStack;
    char dic[128];
    dic['('] = ')';
    dic['['] = ']';
    dic['{'] = '}';
    for(int i = 0; i < s.length(); i++)
    {
        if (s[i] == '(' || s[i] == '[' || s[i] == '{')
        {
            parenthesesStack.push(s[i]);
            continue;
        }
        if (parenthesesStack.size() <= 0 || dic[parenthesesStack.top()] != s[i])
        {
            return false;
        }
        else
        {
            parenthesesStack.pop();
        }
    }
    if (parenthesesStack.size() == 0)
        return true;
    else
        return false;
}

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

ListNode* removeNthFromEnd(ListNode* head, int n)
{
    if (head == NULL)
    {
        return NULL;
    }
    ListNode *pre, *p1, *p2;
    pre = p1 = p2 = head;
    for(int i = 1; p2 != NULL && i < n; i++)
        p2 = p2->next;
    if (p2 == NULL)
        return NULL;
    while(p2->next != NULL)
    {
        if (p1 != head)
            pre = pre->next;
        p1 = p1->next;
        p2 = p2->next;
    }
    if (pre != p1)
        pre->next = p1->next;
    else
        head = head->next;
    delete p1;
    return head;
}

ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)
{
    ListNode* newList, *endOfNewList;
    if (l1 == NULL && l2 != NULL)
        return l2;
    if (l1 != NULL && l2 == NULL)
        return l1;
    if (l1 == NULL && l2 == NULL)
        return NULL;
    if (l1->val < l2->val)
    {
        newList = l1;
        l1 = l1->next;
        newList->next = NULL;
    }
    else
    {
        newList = l2;
        l2 = l2->next;
        newList->next = NULL;
    }
    endOfNewList = newList;

    while(l1 != NULL && l2 != NULL)
    {
        if (l1->val < l2->val)
        {
            endOfNewList->next = l1;
            endOfNewList = l1;
            l1 = l1->next;
            endOfNewList->next = NULL;
        }
        else
        {
            endOfNewList->next = l2;
            endOfNewList = l2;
            l2 = l2->next;
            endOfNewList->next = NULL;
        }
    }
    if (l1 == NULL)
        endOfNewList->next = l2;
    if (l2 == NULL)
        endOfNewList->next = l1;
    return newList;
}

ListNode* mergeKLists(vector<ListNode*>& lists)
{
    if (lists.size() == 0)
        return NULL;
    int n = lists.size();
    while(n > 1)
    {
        int k = (n + 1) / 2;
        for(int i = 0; i < n / 2; i++)
        {
            lists[i] = mergeTwoLists(lists[i], lists[i + k]);
        }
        n = k;
    }
    return lists[0];
}

ListNode* swapPairs(ListNode* head)
{
    if (head == NULL)
        return NULL;
    ListNode* p1 = head, * p2 = head->next;
    if (p2 != NULL)
        head = p2;
    while(p1 != NULL && p2 != NULL)
    {
        if (p2->next == NULL)
        {
            p1->next = NULL;
            p2->next = p1;
            break;
        }
        if (p2->next->next == NULL)
            p1->next = p2->next;
        else
            p1->next = p2->next->next;
        ListNode* tmp = p1;
        p1 = p2->next;
        p2->next = tmp;
        p2 = p1->next;
    }
    return head;
}

int removeDuplicates(vector<int>& nums)
{
    if (nums.size() == 0)
    {
        return 0;
    }
    int i = 0;
    for(int j = 1; j < nums.size(); j++)
    {
        if (nums[i] != nums[j])
            nums[++i] = nums[j];
    }

    return i + 1;
}

int removeElement(vector<int>& nums, int val)
{
    int i = 0, j = 0;
    for(int i = 0; i < nums.size(); i++)
    {
        if (nums[i] == val)
        {
            continue;
        }
        nums[j++] = nums[i];
    }

    return j;
}

ListNode* removeElements(ListNode* head, int val)
{
    while(head != NULL && head->val == val)
    {
        ListNode* tmp = head;
        head = head->next;
        delete tmp;
    }
    if (head == NULL)
    {
        return NULL;
    }
    ListNode* p, * pre;
    p = head->next;
    pre = head;
    while(p != NULL)
    {
        if (p->val == val)
        {
            pre->next = p->next;
            delete p;
            p = pre->next;
        }
        else
        {
            pre = p;
            p = p->next;
        }
    }

    return head;
}

int strStr(string haystack, string needle)
{
    if (needle.empty())
        return 0;
    int i = 0, j = 0;
    while(i < haystack.length() && j < needle.length())
    {
        if (haystack[i] != needle[j])
        {
            i = i - j + 1;
            j = 0;
            continue;
        }
        i++;
        j++;
    }
    if (j == needle.length())
        return i - j;
    else
        return -1;
}

int divide(int dividend, int divisor)
{
    if (divisor == 0 || (dividend == INT_MIN && divisor == -1))
        return INT_MAX;
    int sign = (dividend > 0) ^ (divisor > 0) ? -1 : 1;
    long long dvd = labs(dividend);
    long long dvs = labs(divisor);
    int result = 0;
    while(dvd >= dvs)
    {
        long long tmp = dvs, multiplier = 1;
        while(dvd >= (tmp << 1))
        {
            tmp <<= 1;
            multiplier <<= 1;
        }
        dvd -= tmp;
        result += multiplier;
    }

    return sign == 1 ? result : -result;
}

bool nextPermutation(vector<int>& nums)
{
    if (nums.size() < 2)
        false;
    int i, j;
    for(i = nums.size() - 2; i >= 0; i--)
    {
        if (nums[i] < nums[i + 1])
            break;
    }
    if (i >= 0)
    {
        for(j = nums.size() - 1; j > i; j--)
        {
            if (nums[j] > nums[i])
                break;
        }
        swap(nums[i], nums[j]);
        reverse(nums.begin() + i + 1, nums.end());
        return true;
    }
    return false;
}

void permutationBacktrack(vector<int>& tmp, int position, vector<int>& nums, vector<vector<int>>& result)
{
    if (position == nums.size())
    {
        result.push_back(tmp);
        return ;
    }
    for(int i = 0; i < nums.size(); i++)
    {
        if (find(tmp.begin(), tmp.end(), nums[i]) == tmp.end())
        {
            tmp.push_back(nums[i]);
            permutationBacktrack(tmp, position + 1, nums, result);
            tmp.pop_back();
        }
    }
}

vector<vector<int>> permute(vector<int>& nums)
{
    vector<vector<int>> result;
    sort(nums.begin(), nums.end());
    vector<int> tmp;
    /*
    result.push_back(nums);
    while(nextPermutation(nums)) {
        result.push_back(nums);
    }
    */
    permutationBacktrack(tmp, 0, nums, result);
    return result;
}

vector<vector<int>> permuteUnique(vector<int>& nums)
{
    vector<vector<int>> result;
    sort(nums.begin(), nums.end());
    result.push_back(nums);
    while(nextPermutation(nums))
    {
        result.push_back(nums);
    }
    return result;
}

vector<int> searchRange(vector<int>& nums, int target)
{
    vector<int> result;
    bool flag = false;

    for(int i = 0; i < nums.size(); i++)
    {
        if (!flag && nums[i] == target)
        {
            result.push_back(i);
            flag = true;
        }
        else if (flag && nums[i] != target)
        {
            result.push_back(i - 1);
            break;
        }
    }
    if (flag && result.size() == 1)
    {
        result.push_back(nums.size() - 1);
    }
    else if (!flag)
    {
        result.push_back(-1);
        result.push_back(-1);
    }

    return result;
}

vector<int> binarySearchRange(int A[], int n, int target)
{
    int i = 0, j = n - 1;
    vector<int> ret(2, -1);
    // Search for the left one
    while (i < j)
    {
        int mid = (i + j) /2;
        if (A[mid] < target) i = mid + 1;
        else j = mid;
    }
    if (A[i]!=target) return ret;
    else ret[0] = i;

    // Search for the right one
    j = n-1;  // We don't have to set i to 0 the second time.
    while (i < j)
    {
        int mid = (i + j) /2 + 1;	// Make mid biased to the right
        if (A[mid] > target) j = mid - 1;
        else i = mid;				// So that this won't make the search range stuck.
    }
    ret[1] = j;
    return ret;
}

/*
int firstBadVersion(int n) {
    int i = 1, j = n;
    while(i < j) {
        //int mid = (i + j) / 2;
        int mid = i + (j - i) / 2;
        if (isBadVersion(mid)) {
            j = mid;
        } else {
            i = mid + 1;
        }
    }
    return i;
}
*/

int searchInsert(vector<int>& nums, int target)
{
    int i = 0, j = nums.size() - 1;
    while(i < j)
    {
        int mid = i + (j - i) / 2;
        if (nums[mid] > target)
        {
            j = mid - 1;
        }
        else if (nums[mid] < target)
        {
            i = mid + 1;
        }
        else
        {
            return mid;
        }
    }
    if (nums[i] < target)
        return i + 1;
    else
        return i;
}

bool isValidSudoku(vector<vector<char>>& board)
{
    bool rowUse[9][9] = {false}, columnUse[9][9] = {false}, boxUse[9][9] = {false};
    for(int i = 0; i < board.size(); i++)
    {
        for(int j = 0; j < board[i].size(); j++)
        {
            if (board[i][j] != '.')
            {
                int num = board[i][j] - '0' - 1, boxIndex = i / 3 * 3 + j / 3;
                if (rowUse[i][num] || columnUse[j][num] || boxUse[boxIndex][num])
                    return false;
                rowUse[i][num] = columnUse[j][num] = boxUse[boxIndex][num] = true;
            }
        }
    }
    return true;
}

bool isvalid(vector<vector<char>>& board, int r, int c, char d)
{
    for(int i = 0; i < 9; i++)
    {
        if (board[r][i] == d)
            return false;
        if (board[i][c] == d)
            return false;
        if (board[(r / 3) * 3 + i / 3][(c / 3) * 3 + i % 3] == d)
            return false;
    }
    return true;
}
bool solve(vector<vector<char>>& board)
{
    for(int i = 0; i < board.size(); i++)
    {
        for(int j = 0; j < board[i].size(); j++)
        {
            if (board[i][j] == '.')
            {
                for(char c = '1'; c <= '9'; c++)
                {
                    if (isvalid(board, i, j, c))
                    {
                        board[i][j] = c;
                        if (solve(board))
                            return true;
                        board[i][j] = '.';
                    }
                }
                return false;
            }
        }
    }
    return true;
}

void solveSudoku(vector<vector<char>>& board)   //´ýÓÅ»¯
{
    solve(board);
}

string countAndSay(int n)
{
    if (0 == n) return "";
    if (1 == n) return "1";

    string res="1";
    string s;
    for (int i = 1; i < n; i++)     // run from starting to generate second string
    {
        int len = res.size();
        //cheack all digits in the string
        for (int j = 0; j < len; j++)
        {
            int count=1; // we have at least 1 occourence of each digit
            // get the number of times same digit occurred (be carefull with the end of the string)
            while ((j + 1 < len) && (res[j] == res[j + 1]))
            {
                count++;
                j++;        // we need to keep increasing the index inside of the string
            }
            // add to new string "count"+"digit itself"
            s += toString(count) + res[j];
        }
        // save temporary result
        res = s;
        // clean our string-helper
        s.clear();
    }
    return res;
}

bool contain(vector<vector<int>>& result, vector<int>& v)
{
    for(int i = 0; i < result.size(); i++)
    {
        if(result[i] == v)
            return true;
    }
    return false;
}

void combinationSum(vector<vector<int>>& result, vector<int>& candidates, vector<int> tmp, int sum, int target)
{
    if (sum == target)
    {
        sort(tmp.begin(), tmp.end());
        if (!contain(result, tmp))
        {
            result.push_back(tmp);
        }
        return ;
    }
    for(int i = 0; i < candidates.size(); i++)
    {
        if (sum + candidates[i] <= target)
        {
            tmp.push_back(candidates[i]);
            combinationSum(result, candidates, tmp, sum + candidates[i], target);
            tmp.pop_back();
        }
    }
}

vector<vector<int>> combinationSum(vector<int>& candidates, int target)
{
    vector<vector<int>> result;
    vector<int> tmp;
    combinationSum(result, candidates, tmp, 0, target);
    return result;
}

void combinationSum2(vector<vector<int>>& result, vector<int>& candidates, vector<bool>& used, vector<int> tmp, int sum, int target)
{
    if (sum == target)
    {
        sort(tmp.begin(), tmp.end());
        if (!contain(result, tmp))
        {
            result.push_back(tmp);
        }
        return ;
    }
    for(int i = 0; i < candidates.size(); i++)
    {
        if (!used[i] && sum + candidates[i] <= target)
        {
            tmp.push_back(candidates[i]);
            used[i] = true;
            combinationSum2(result, candidates, used, tmp, sum + candidates[i], target);
            used[i] = false;
            tmp.pop_back();
        }
    }
}

vector<vector<int>> combinationSum2(vector<int>& candidates, int target)
{
    vector<vector<int>> result;
    vector<int> tmp;
    vector<bool> used(candidates.size(), false);
    combinationSum2(result, candidates, used, tmp, 0, target);
    return result;
}

string multiply(string num1, string num2)
{
    string result;

    return result;
}

void rotate(vector<vector<int>>& matrix)
{
    reverse(matrix.begin(), matrix.end());
    for(int i = 0; i < matrix.size(); i++)
        for(int j = 0; j < i; j++)
            swap(matrix[i][j], matrix[j][i]);
}

vector<vector<string>> groupAnagrams(vector<string>& strs)
{
    unordered_map<string, vector<string>> count;
    int i = 0;
    for (auto s : strs)
    {
        sort(s.begin(), s.end());
        count[s].push_back(strs[i++]);
    }
    vector<vector<string>> res;
    for (auto n : count)
    {
        sort(n.second.begin(), n.second.end());
        res.push_back(n.second);
    }
    return res;
}

bool isAnagram(string s, string t)
{
    if (s.length() != t.length())
        return false;
    int count_s[128] = {0}, count_t[128] = {0};
    int length = s.length();
    for(int i = 0; i < length; i++)
    {
        count_s[s[i]]++;
        count_t[t[i]]++;
    }
    for(int i = 0; i < 128; i++)
    {
        if (count_s[i] != count_t[i])
            return false;
    }
    return true;
}

double myPow(double x, int n)
{
    if (x == 0 && n <= 0)
    {
        cout << "undefine" << endl;
        return -1;
    }
    if (x == 0)
        return 0;
    if (n == 0)
        return 1;
    bool positive = n > 0 ? true : false;
    double tmp = myPow(x, n / 2);
    double result;
    if (positive)
        result = (n % 2) ? (x * tmp * tmp) : (tmp * tmp);
    else
        result = ((-n) % 2) ? ((1 / x) * tmp * tmp) : (tmp * tmp);
    return result;
}

double pow(double x, int n)
{
    if (n==0) return 1;
    double t = pow(x,n/2);
    if (n%2)
    {
        return n<0 ? 1/x*t*t : x*t*t;
    }
    else
    {
        return t*t;
    }
}

int mySqrt(int x)
{
    if (x < 0)
    {
        return -1;
    }
    long long low = 0, high = x, mid;
    while(low <= high)
    {
        mid = (low + high) / 2;
        long long square = mid * mid;
        if (square == x)
            return mid;
        if (square > x)
            high = mid - 1;
        if (square < x)
            low = mid + 1;
    }
    return (low + high) / 2;
}

int superPow(int a, vector<int>& b)
{

}

bool isSubsequence(string s, string t)
{
    int length = t.length(), j = 0;
    for(int i = 0; i < length; i++)
    {
        if (s[j] == t[i])
        {
            j++;
        }
    }
    if (j == s.length())
        return true;
    else
        return false;
}

int combinationSum4(vector<int>& nums, int target)
{
    vector<int> result(target + 1);
    result[0] = 1;
    for(int i = 1; i <= target; i++)
    {
        for(auto num : nums)
        {
            if (i >= num)
                result[i] += result[i - num];
        }
    }
    return result[target];
}

int wiggleMaxLength(vector<int>& nums)
{
    int size = nums.size();
    if (size == 0)
        return 0;
    vector<int> up(size), down(size);
    up[0] = down[0] = 1;
    for(int i = 1; i < size; i++)
    {
        if (nums[i] > nums[i - 1])
        {
            up[i] = down[i - 1] + 1;
            down[i] = down[i - 1];
        }
        else if (nums[i] < nums[i - 1])
        {
            down[i] = up[i - 1] + 1;
            up[i] = up[i - 1];
        }
        else
        {
            up[i] = up[i - 1];
            down[i] = down[i - 1];
        }
    }
    return max(up[size - 1], down[size - 1]);
}

int getMoneyAmount(int n)
{

}

void solveNQueens(vector<vector<string>>& result, vector<string>& nQueens, vector<int>& flag, int row, int n)
{
    if (row == n)
    {
        result.push_back(nQueens);
        return;
    }
    for(int col = 0; col < n; col++)
    {
        if (flag[col] && flag[n+row+col] && flag[4*n-2+col-row])
        {
            nQueens[row][col] = 'Q';
            flag[col] = flag[n+row+col] = flag[4*n-2+col-row] = 0;
            solveNQueens(result, nQueens, flag, row+1, n);
            nQueens[row][col] = '.';
            flag[col] = flag[n+row+col] = flag[4*n-2+col-row] = 1;
        }
    }
}

vector<vector<string>> solveNQueens(int n)
{
    vector<vector<string>> result;
    vector<string> nQueens(n, string(n, '.'));
    vector<int> flag(5*n+2, 1);
    solveNQueens(result, nQueens, flag, 0, n);

    return result;
}

void solveNQueens(int& result, vector<string>& nQueens, vector<int>& flag, int row, int n)
{
    if (row == n)
    {
        result++;
        return;
    }
    for(int col = 0; col < n; col++)
    {
        if (flag[col] && flag[n+row+col] && flag[4*n-2+col-row])
        {
            nQueens[row][col] = 'Q';
            flag[col] = flag[n+row+col] = flag[4*n-2+col-row] = 0;
            solveNQueens(result, nQueens, flag, row+1, n);
            nQueens[row][col] = '.';
            flag[col] = flag[n+row+col] = flag[4*n-2+col-row] = 1;
        }
    }
}

int totalNQueens(int n)
{
    int result = 0;
    vector<string> nQueens(n, string(n, '.'));
    vector<int> flag(5*n+2, 1);
    solveNQueens(result, nQueens, flag, 0, n);

    return result;
}

int maxSubArray(vector<int>& nums)
{
    int len = nums.size();
    int max;
    vector<int> dp(len, 0);
    dp[0] = nums[0];
    max = dp[0];
    for(int i = 1; i < len; i++)
    {
        if (dp[i-1] > 0)
            dp[i] = dp[i-1] + nums[i];
        else
            dp[i] = nums[i];

        if (dp[i] > max)
            max = dp[i];
    }
    return max;
}

vector<int> spiralOrder(vector<vector<int>>& matrix)
{
    vector<int> result;
    vector<vector<int>> dir = {{0, 1},{1, 0},{0, -1},{-1, 0}};
    int nr = matrix.size();
    if (nr == 0) return result;
    int nc = matrix[0].size();
    if (nc == 0) return result;

    vector<int> step{nc, nr-1};
    int curDir = 0;
    int ir = 0, ic = -1;
    while(step[curDir%2])
    {
        for(int i = 0; i < step[curDir%2]; i++)
        {
            ir += dir[curDir][0];
            ic += dir[curDir][1];
            result.push_back(matrix[ir][ic]);
        }
        step[curDir%2]--;
        curDir = (curDir+1) % 4;
    }
    return result;
}

bool canJump(vector<int>& nums)
{
    int maxReach = 0, i;
    int len = nums.size();
    for(i = 0; i < len && i <= maxReach; i++)
    {
        maxReach = max(nums[i]+i, maxReach);
    }
    return i == len;
}

struct Interval
{
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

bool intervalCompare(const Interval& a, const Interval& b)
{
    return a.start < b.start;   //can not be <=
}

vector<Interval> merge(vector<Interval>& intervals)
{
    vector<Interval> res;
    if (intervals.size() == 0)
        return res;
    sort(intervals.begin(), intervals.end(), intervalCompare);
    res.push_back(intervals[0]);
    for(int i = 1; i < intervals.size(); i++)
    {
        if (res.back().end < intervals[i].start)
        {
            res.push_back(intervals[i]);
        }
        else
        {
            res.back().end = max(res.back().end, intervals[i].end);
        }
    }
    return res;
}

vector<Interval> insert(vector<Interval>& intervals, Interval newInterval)
{

}
/*
int lengthOfLastWord(string s) {
    if (s.length() == 0) return 0;
    int start = 1, end = 0;
    bool flag = false;
    for(int i = 0; i < s.length(); i++) {
        if (!flag && s[i] != ' ') {
            start = end = i;
            flag = true;
        } else if (flag && s[i] != ' ') {
            end = i;
        } else if (flag && s[i] == ' '){
            flag = false;
        }
    }
    return end-start+1;
}
*/
int lengthOfLastWord(string s)
{
    int len = 0, tail = s.length() - 1;
    while (tail >= 0 && s[tail] == ' ') tail--;
    while (tail >= 0 && s[tail] != ' ')
    {
        len++;
        tail--;
    }
    return len;
}

vector<vector<int>> generateMatrix(int n) {
    vector<vector<int>> matrix(n, vector<int>(n, 0));
    vector<vector<int>> dir{{0,1}, {1, 0}, {0, -1}, {-1, 0}};
    vector<int> step{n, n-1};
    int ir = 0, ic = -1;
    int iDir = 0;
    int count = 0;
    while(step[iDir%2]) {
        for(int i = 0; i < step[iDir%2]; i++) {
            ir += dir[iDir][0];
            ic += dir[iDir][1];
            matrix[ir][ic] = ++count;
        }
        step[iDir%2]--;
        iDir = (iDir+1) % 4;
    }
    return matrix;
}

bool canCross(vector<int>& stones) {

}

void AdjustDown(vector<int> A, int i, int len, vector<int>& index)
{
	int temp = A[i];  // 暂存A[i]
	int start = index[i];

	for(int largest=2*i+1; largest<len; largest=2*largest+1)
	{
		if(largest!=len-1 && A[largest+1]>A[largest])
			++largest;         // 如果右子结点大
		if(temp < A[largest])
		{
			A[i] = A[largest];
			index[i] = index[largest];
			i = largest;         // 记录交换后的位置
		}
		else
			break;
	}
	A[i] = temp;    // 被筛选结点的值放入最终位置
	index[i] = start;
}

/* 建堆 */
void BuildMaxHeap(vector<int> A, int len, vector<int>& index)
{
	for(int i=len/2-1; i>=0; --i)  // 从i=n/2-1到0，反复调整堆
		AdjustDown(A, i, len, index);
}


void topK(vector<int> A, int k, vector<int>& index)
{
	BuildMaxHeap(A, k, index);  // 先用前面的k个数建大根堆
	for(int i=k; i<A.size(); ++i)
	{
		if(A[i] < A[0])  // 如果小于堆顶元素，替换之
		{
			int tmp = A[0];
			A[0] = A[i];
			index[0] = i;
			A[i] = tmp;
			AdjustDown(A, 0, k, index);  // 向下调整
		}
	}
}

int n, m;
void zeroOnePack(vector<int>& res, int cost, int weight) {
    for(int v = m; v >= cost; v--)
        res[v] = max(res[v], res[v-cost]+weight);
}

int main()
{
    vector<int> vi, wi;
    cin >> n >> m;
    vector<int> res(m+1, 0);
    for(int i = 0; i < n; i++) {
        int v, w;
        cin >> v >> w;
        vi.push_back(v);
        wi.push_back(w);
    }
    for(int i = 0; i < n; i++)
        zeroOnePack(res, wi[i], vi[i]);
    cout << res[m] << endl;
    return 0;
    /*
    vector<int> v;
    vector<int> index;
    string line;
    int k;
    cin >> line >> k;
    for(int i = 0; i < line.length(); i++) {
        v.push_back(line[i]-'0');
    }
    for(int i = 0; i < k; i++) {
        index.push_back(i);
    }
    topK(v, k, index);
    for(int i = 0; i < k; i++) {
        v[index[i]] = -1;
    }
    for(int i = 0; i < v.size(); i++) {
        if (v[i] != -1)
            cout<<v[i];
    }
    cout << endl;
    */
}
