struct ListNode* middleNode(struct ListNode* head)
{
	struct ListNode* slow = head;
	struct ListNode* fast = head;
	while (fast && fast->next)
		//循环想的是结束的条件但是写的确实继续下去的条件，所以对于中间这个&&,是需要同时满足奇数个数组和偶数个数组的条件
	{
		slow = slow->next;
		fast = fast->next->next;
	}
	return slow;
}



class Solution {
public:
	ListNode* FindKthToTail(ListNode* pListHead, unsigned int k) {
		ListNode* slow = pListHead, *fast = pListHead;
		//你这里的K值有可能比你链表本身的长度长，所以要保证其实有效的，
		//这一题最不好想到的就是这里。
		while (k--)
		{
			if (fast != NULL)
				fast = fast->next;
			else
				return NULL;
		}
		while (fast)
		{
			slow = slow->next;
			fast = fast->next;
		}
		return slow;
	}
};


/*
struct ListNode {
int val;
struct ListNode *next;
ListNode(int x) : val(x), next(NULL) {}
};*/
class PalindromeList {
public:
	bool chkPalindrome(ListNode* A) {
		//①找出中间的那个结点
		ListNode* slow = A;
		ListNode* fast = A;
		ListNode* prev = NULL;
		//在下面逆置的时候需要知道slow的上一个结点的位置
		while (fast && fast->next)
		{
			prev = slow;
			slow = slow->next;
			fast = fast->next->next;
		}
		//这一步就是所写的“注意”
		prev->next = NULL;
		//②逆置链表
		ListNode* newHead = NULL;
		ListNode* cur = slow;
		while (cur)
		{
			ListNode* next = cur->next;
			cur->next = newHead;
			newHead = cur;
			cur = next;
		}
		//③比较（此时你使用A或者newhead都是可以的）
		while (A)
		{
			if (newHead->val != A->val)
			{
				return false;
			}
			else
			{
				newHead = newHead->next;
				A = A->next;
			}
		}
		return true;
	}
};

typedef struct ListNode ListNode;
struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB)
{
	//一定要记住不要随便的直接使用题目所给的头，要定义一个变量，然它进行一系列的操作
	//这里你会发现，在有些编译器上面会报错，因为对于C语言来说，他要求你需要把变量定义在域的前面
	//①求出两个链表的各自长度
	ListNode* curA = headA;
	int la = 0;
	while (curA)
	{
		la++;
		curA = curA->next;
	}
	ListNode* curB = headB;
	int lb = 0;
	while (curB)
	{
		lb++;
		curB = curB->next;
	}
	//这里我省略了判断的过程直接假设法，我就直接设长的是curA，短的是curB
	ListNode* longList = headA;
	ListNode* shortList = headB;
	//这里就判断一下我的假设是否正确，如果不正确那就进行修改
	if (lb > la)
	{
		longList = headB;
		shortList = headA;
	}
	//abs是C语言中的库函数，用来用绝对值的
	int gap = abs(la - lb);
	//让长的链表先走之间的差值步数
	while (gap--)
	{
		longList = longList->next;
	}
	//此时之后longList和shortList是一样长的，所以随便判断哪一个都是可以的
	while (longList)
	{
		if (longList == shortList)
		{
			return longList;
		}
		else
		{
			longList = longList->next;
			shortList = shortList->next;
		}
	}
	return NULL;
}


/*
struct ListNode {
int val;
struct ListNode *next;
ListNode(int x) : val(x), next(NULL) {}
};*/
//但是你会发现提交代码之后他会给你报一个“内存超限”的错误警告，代码不能通过，这之中情况一般下就是你的循环部分
//写成了一个死循环，导致代码相当于形成了一个环
//对于原链表 1 9 3 5 6 7
// 1 3
// 9 5 6 7 这样你写的代码是没有毛病的，因为最后7的后面是NULL的（必须保证链表的最后一个所指向的下一个为空）
//但是
//对于原链表 1 9 3 5 6 7 2的时候就出现问题了
//因为cur往下来遍历，但是你的7最后又指向的2这个节点，就有问题了
typedef struct ListNode ListNode;
class Partition {
public:
	ListNode* partition(ListNode* pHead, int x) {
		//创建带哨兵位的头结点，里面并不存储有效的内容
		ListNode* lessHead, *lessTail;
		ListNode* greaterHead, *greaterTail;
		//你会到最后发现lessTail和greaterTail最后就会走到有效的结点上面
		lessHead = lessTail = (ListNode*)malloc(sizeof(ListNode));
		greaterHead = greaterTail = (ListNode*)malloc(sizeof(ListNode));
		//这里记得要对所开辟的结点进行初始化，如果你不进行初始化，那么他的下一个值是一个随机值
		lessHead->next = greaterHead->next = NULL;
		ListNode* cur = pHead;
		while (cur)
		{
			if (cur->val < x)
			{
				lessTail->next = cur;
				lessTail = lessTail->next;
			}
			else
			{
				greaterTail->next = cur;
				greaterTail = greaterTail->next;
			}
			cur = cur->next;
		}
		lessTail->next = greaterHead->next;
		//解决死循环的办法就是，当下面的那个都遍历完了之后就给他置空
		greaterTail->next = NULL;
		//一定要记住既然你是malloc出来的空间最后一定要进行释放，但是你现在里面释放掉了之后，我能怎么能找到
		//这个新的排序后的头呢，所以这里要定义一个变量来保存它的头
		ListNode* list = lessHead->next;
		free(lessHead);
		free(greaterHead);
		return list;
	}
};


int removeDuplicates(int* nums, int numsSize)
{
	//数组在一开始的时候有可能为空，这个情况也一定要考虑进去
	if (numsSize == 0)
		return 0;
	int prev = 0, cur = 1, dst = 0;
	while (cur < numsSize) //用cur来判断，因为他最终会越界，作为循环来结束的一个判断标志，prev指向数组中下标为0的元素，cur指向数组中下标为1的元素
	{
		if (nums[prev] != nums[cur])
		{
			nums[dst] = nums[prev];
			prev++;
			dst++;
			cur++;
		}
		else
		{
			prev++;
			cur++;
		}
	}
	//此时prev和cur的值是不相等的，但是上面你只返回了prev的值，
	//最后一个cur值也是需要返回的
	nums[dst] = nums[prev];
	dst++;
	return dst;
}



int* addToArrayForm(int* A, int ASize, int K, int* returnSize)
{
	//计算K是多少位的
	int KSize = 0;
	int kNum = K; // 如果不加这个你会发现，你到最后把K的数值已经改变了，就找不到了
	while (kNum)
	{
		KSize++;
		kNum /= 10; // 这里也在提示不要轻易的修改掉原来的K值，因为这里会发生K值的变化
	}
	int len = ASize > KSize ? ASize : KSize;
	int* retArr = (int*)malloc(sizeof(int)*(len + 1)); //返回数组的长度，但是这里还有一个小技巧，你会发现题目下面是有限制条件的，0<K<10000
	//所以你就直接开辟一个6位数数组大小空间就好了。

	//A []
	//K
	int Ai = ASize - 1; //A数组的最后一位
	int reti = 0;
	int nextNum = 0;//进位
	while (len--)
	{
		int a = 0;
		if (Ai >= 0) // A的数组短，会先走完
		{
			a = A[Ai];
			Ai--;
		}
		int ret = a + K % 10 + nextNum;
		K /= 10;
		if (ret > 9)
		{
			ret -= 10;
			nextNum = 1;
		}
		else
		{
			nextNum = 0;
		}
		retArr[reti] = ret;
		reti++;
	}
	if (nextNum == 1)
	{
		retArr[reti] = 1;
		reti++;
	}
	//逆置
	int left = 0;
	int right = reti - 1;
	while (left < right)
	{
		int tmp = retArr[left];
		retArr[left] = retArr[right];
		retArr[right] = tmp;
		left++;
		right--;
	}
	*returnSize = reti;
	return retArr;
}


/**
* Definition for singly-linked list.
* struct ListNode {
*     int val;
*     struct ListNode *next;
* };
*/
bool hasCycle(struct ListNode *head) {
	struct ListNode* fast = head, *slow = head;
	//因为你并不能确定这个链表一定是带环的，所以循环的条件还是要按照正常的思路来写的
	while (fast && fast->next)
	{
		//慢指针走的慢，快指针一次走两步走的快，如果有环，那么总会达到快指针追上了慢指针
		slow = slow->next;
		fast = fast->next->next;
		//他们都进入了环里，快指针追上了慢指针
		if (slow == fast)
			return true;
	}
	return false;
}



/**
* Definition for singly-linked list.
* struct ListNode {
*     int val;
*     struct ListNode *next;
* };
*/
struct ListNode *detectCycle(struct ListNode *head) {
	struct ListNode* slow = head, *fast = head;
	while (fast && fast->next)
	{
		//这一步是在最后进行测试用例不过的时候返回来判断发现的一个问题，如果你把if判断放在前面，就会一开始的快慢指针就是相等的，那么你一进入这个循环的时候就直接break了
		slow = slow->next;
		fast = fast->next->next;
		//所以这里选择先进行走一步，然后判断，不然就会直接跳出来了
		if (slow == fast)
			break;
	}
	//上面的循环跳出来有两种可能，第一如果链表是带环的，那么一定以break跳出来，那个时候就找到了快慢指针的相遇点，第二种就是都遍历完了，fast都走到NULL的时候依旧没有找到两个相遇的点，说明这个链表是不带环的。
	//这段代码表示这个链表不带回环，当为奇数个的时候fast为NULL，偶数个的时候fast->next为NULL，但是不管哪种情况出现，都可以表示这是一个没有回环的链表
	if (fast == NULL || fast->next == NULL)
		return NULL;
	struct ListNode * meet = fast;
	while (head != meet)
	{
		head = head->next;
		meet = meet->next;
	}
	return meet;
}