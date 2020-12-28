struct ListNode* middleNode(struct ListNode* head)
{
	struct ListNode* slow = head;
	struct ListNode* fast = head;
	while (fast && fast->next)
		//ѭ������ǽ�������������д��ȷʵ������ȥ�����������Զ����м����&&,����Ҫͬʱ���������������ż�������������
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
		//�������Kֵ�п��ܱ���������ĳ��ȳ�������Ҫ��֤��ʵ��Ч�ģ�
		//��һ������뵽�ľ������
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
		//���ҳ��м���Ǹ����
		ListNode* slow = A;
		ListNode* fast = A;
		ListNode* prev = NULL;
		//���������õ�ʱ����Ҫ֪��slow����һ������λ��
		while (fast && fast->next)
		{
			prev = slow;
			slow = slow->next;
			fast = fast->next->next;
		}
		//��һ��������д�ġ�ע�⡱
		prev->next = NULL;
		//����������
		ListNode* newHead = NULL;
		ListNode* cur = slow;
		while (cur)
		{
			ListNode* next = cur->next;
			cur->next = newHead;
			newHead = cur;
			cur = next;
		}
		//�۱Ƚϣ���ʱ��ʹ��A����newhead���ǿ��Եģ�
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
	//һ��Ҫ��ס��Ҫ����ֱ��ʹ����Ŀ������ͷ��Ҫ����һ��������Ȼ������һϵ�еĲ���
	//������ᷢ�֣�����Щ����������ᱨ����Ϊ����C������˵����Ҫ������Ҫ�ѱ������������ǰ��
	//�������������ĸ��Գ���
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
	//������ʡ�����жϵĹ���ֱ�Ӽ��跨���Ҿ�ֱ���賤����curA���̵���curB
	ListNode* longList = headA;
	ListNode* shortList = headB;
	//������ж�һ���ҵļ����Ƿ���ȷ���������ȷ�Ǿͽ����޸�
	if (lb > la)
	{
		longList = headB;
		shortList = headA;
	}
	//abs��C�����еĿ⺯���������þ���ֵ��
	int gap = abs(la - lb);
	//�ó�����������֮��Ĳ�ֵ����
	while (gap--)
	{
		longList = longList->next;
	}
	//��ʱ֮��longList��shortList��һ�����ģ���������ж���һ�����ǿ��Ե�
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
//������ᷢ���ύ����֮��������㱨һ�����ڴ泬�ޡ��Ĵ��󾯸棬���벻��ͨ������֮�����һ���¾������ѭ������
//д����һ����ѭ�������´����൱���γ���һ����
//����ԭ���� 1 9 3 5 6 7
// 1 3
// 9 5 6 7 ������д�Ĵ�����û��ë���ģ���Ϊ���7�ĺ�����NULL�ģ����뱣֤��������һ����ָ�����һ��Ϊ�գ�
//����
//����ԭ���� 1 9 3 5 6 7 2��ʱ��ͳ���������
//��Ϊcur�������������������7�����ָ���2����ڵ㣬����������
typedef struct ListNode ListNode;
class Partition {
public:
	ListNode* partition(ListNode* pHead, int x) {
		//�������ڱ�λ��ͷ��㣬���沢���洢��Ч������
		ListNode* lessHead, *lessTail;
		ListNode* greaterHead, *greaterTail;
		//��ᵽ�����lessTail��greaterTail���ͻ��ߵ���Ч�Ľ������
		lessHead = lessTail = (ListNode*)malloc(sizeof(ListNode));
		greaterHead = greaterTail = (ListNode*)malloc(sizeof(ListNode));
		//����ǵ�Ҫ�������ٵĽ����г�ʼ��������㲻���г�ʼ������ô������һ��ֵ��һ�����ֵ
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
		//�����ѭ���İ취���ǣ���������Ǹ�����������֮��͸����ÿ�
		greaterTail->next = NULL;
		//һ��Ҫ��ס��Ȼ����malloc�����Ŀռ����һ��Ҫ�����ͷţ����������������ͷŵ���֮��������ô���ҵ�
		//����µ�������ͷ�أ���������Ҫ����һ����������������ͷ
		ListNode* list = lessHead->next;
		free(lessHead);
		free(greaterHead);
		return list;
	}
};


int removeDuplicates(int* nums, int numsSize)
{
	//������һ��ʼ��ʱ���п���Ϊ�գ�������Ҳһ��Ҫ���ǽ�ȥ
	if (numsSize == 0)
		return 0;
	int prev = 0, cur = 1, dst = 0;
	while (cur < numsSize) //��cur���жϣ���Ϊ�����ջ�Խ�磬��Ϊѭ����������һ���жϱ�־��prevָ���������±�Ϊ0��Ԫ�أ�curָ���������±�Ϊ1��Ԫ��
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
	//��ʱprev��cur��ֵ�ǲ���ȵģ�����������ֻ������prev��ֵ��
	//���һ��curֵҲ����Ҫ���ص�
	nums[dst] = nums[prev];
	dst++;
	return dst;
}



int* addToArrayForm(int* A, int ASize, int K, int* returnSize)
{
	//����K�Ƕ���λ��
	int KSize = 0;
	int kNum = K; // ������������ᷢ�֣��㵽����K����ֵ�Ѿ��ı��ˣ����Ҳ�����
	while (kNum)
	{
		KSize++;
		kNum /= 10; // ����Ҳ����ʾ��Ҫ���׵��޸ĵ�ԭ����Kֵ����Ϊ����ᷢ��Kֵ�ı仯
	}
	int len = ASize > KSize ? ASize : KSize;
	int* retArr = (int*)malloc(sizeof(int)*(len + 1)); //��������ĳ��ȣ��������ﻹ��һ��С���ɣ���ᷢ����Ŀ�����������������ģ�0<K<10000
	//�������ֱ�ӿ���һ��6λ�������С�ռ�ͺ��ˡ�

	//A []
	//K
	int Ai = ASize - 1; //A��������һλ
	int reti = 0;
	int nextNum = 0;//��λ
	while (len--)
	{
		int a = 0;
		if (Ai >= 0) // A������̣���������
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
	//����
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
	//��Ϊ�㲢����ȷ���������һ���Ǵ����ģ�����ѭ������������Ҫ����������˼·��д��
	while (fast && fast->next)
	{
		//��ָ���ߵ�������ָ��һ���������ߵĿ죬����л�����ô�ܻ�ﵽ��ָ��׷������ָ��
		slow = slow->next;
		fast = fast->next->next;
		//���Ƕ������˻����ָ��׷������ָ��
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
		//��һ�����������в�������������ʱ�򷵻����жϷ��ֵ�һ�����⣬������if�жϷ���ǰ�棬�ͻ�һ��ʼ�Ŀ���ָ�������ȵģ���ô��һ�������ѭ����ʱ���ֱ��break��
		slow = slow->next;
		fast = fast->next->next;
		//��������ѡ���Ƚ�����һ����Ȼ���жϣ���Ȼ�ͻ�ֱ����������
		if (slow == fast)
			break;
	}
	//�����ѭ�������������ֿ��ܣ���һ��������Ǵ����ģ���ôһ����break���������Ǹ�ʱ����ҵ��˿���ָ��������㣬�ڶ��־��Ƕ��������ˣ�fast���ߵ�NULL��ʱ������û���ҵ����������ĵ㣬˵����������ǲ������ġ�
	//��δ����ʾ����������ػ�����Ϊ��������ʱ��fastΪNULL��ż������ʱ��fast->nextΪNULL�����ǲ�������������֣������Ա�ʾ����һ��û�лػ�������
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