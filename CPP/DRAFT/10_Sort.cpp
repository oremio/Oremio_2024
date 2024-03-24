/*************************************************************************************

排序算法	平均时间复杂度	    最差时间复杂度	    空间复杂度	    数据对象稳定性
√冒泡排序	O(n2)	            O(n2)	            O(1)	        稳定
√选择排序	O(n2)	            O(n2)	            O(1)	        数组不稳定、链表稳定
√插入排序	O(n2)	            O(n2)	            O(1)	        稳定
√快速排序	O(n*log2n)	        O(n2)	            O(log2n)	    不稳定
x堆排序	    O(n*log2n)	        O(n*log2n)	        O(1)	        不稳定
x归并排序	O(n*log2n)	        O(n*log2n)	        O(n)	        稳定
x希尔排序	O(n*log2n)	        O(n2)	            O(1)	        不稳定
x计数排序	O(n+m)	            O(n+m)	            O(n+m)	        稳定
x桶排序	    O(n)	            O(n2)	            O(m)	        稳定
x基数排序	O(k*n)	            O(n2)		                        稳定

均按从小到大排列
n：代表数据规模
m：代表数据的最大值减最小值
k：代表数值中的 “数位” 个数

*************************************************************************************/
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// 冒泡排序：从无序区通过交换找出最大元素放到有序区前端。
class BubbleSort
{
    void bubbleSort(vector<int> &v)
    {
        int len = v.size();
        for (int i = 0; i < len - 1; i++)
        {
            for (int j = 0; j < len - 1 - i; j++)
            {
                if (v[j] > v[j + 1]) // 从小到大
                    swap(v[j], v[j + 1]);
            }
        }
    }

    void orderlyBubbleSort(vector<int> &v)
    {
        int len = v.size();
        bool orderly = false;
        for (int i = 0; i < len - 1 && !orderly; ++i)
        {
            orderly = true;
            for (int j = 0; j < len - 1 - i; ++j)
            {
                if (v[j] > v[j + 1])
                {                    // 从小到大
                    orderly = false; // 发生交换则仍非有序
                    swap(v[j], v[j + 1]);
                }
            }
        }
    }
};

// 选择排序：在无序区里找一个最小的元素跟在有序区的后面。对数组：比较得多，换得少。
void selectionSort(vector<int> &v)
{
    int min, len = v.size();
    for (int i = 0; i < len; i++)
    {
        min = i;
        for (int j = i + 1; j < len - 1; j++)
        {
            if (v[j] < v[min]) // 从小到大
                min = j;
        }
        if (i != min)
            swap(v[i], v[min]);
    }
}
/*
稳定性：
选择排序的不稳定例子很简单。
比如A 80 B 80 C 70 这三个卷子从小到大排序
第一步会把C和A做交换 变成C B A
第二步和第三步不需要再做交换了。所以排序完是C B A
但是稳定的排序应该是C A B
*/

/*
插入排序：把无序区的第一个元素插入到有序区的合适的位置。对数组：比较得少，换得多。
思路：
1. 从第一个元素开始，该元素可以认为已经被排序
2. 取出下一个元素，在已经排序的元素序列中从后向前扫描
3. 如果该元素（已排序）大于新元素，将该元素移到下一位置
4. 重复步骤3，直到找到已排序的元素小于或者等于新元素的位置
5. 将新元素插入到该位置后
6. 重复步骤2~5
*/
void insertSort(vector<int> &v)
{
    int len = v.size();
    for (int i = 1; i < len; i++)
    {
        int tmp = v[i];
        for (int j = i - 1; j >= 0; j--)
        {
            if (v[j] > tmp)
            {
                v[j + 1] = v[j];
                v[j] = tmp;
            }
            else // 保证了稳定性
                break;
        }
    }
}

// 快速排序：在区间中随机挑选一个元素作基准，将小于基准的元素放在基准之前，大于基准的元素放在基准之后，再分别对小数区与大数区进行排序。
// 第一种写法：双向遍历，小的放前、大的放后，退出循环后first就是分割点
void quickSort(vector<int> &v, int low, int high)
{
    if (low >= high) // 结束标志
        return;
    int first = low;    // 低位下标
    int last = high;    // 高位下标
    int key = v[first]; // 设第一个为基准
    while (first < last)
    {
        // 将比第一个小的移到前面
        while (first < last && v[last] >= key)
            last--;
        if (first < last)
            v[first++] = v[last];
        // 将比第一个大的移到后面
        while (first < last && v[first] <= key)
            first++;
        if (first < last)
            v[last--] = v[first];
    }
    // 基准置位
    v[first] = key;
    // 前半递归
    quickSort(v, low, first - 1);
    // 后半递归
    quickSort(v, first + 1, high);
}

// 第二种写法：单项遍历，仅仅是把小的放前面，最后返回分割点
class QuickSort
{
public:
    /* This function is same in both iterative and recursive*/
    int partition(int arr[], int l, int h)
    {
        int x = arr[h];  // 取最后一个元素
        int i = (l - 1); // 俗称存储指数

        for (int j = l; j <= h - 1; j++)
        { // 从l到h-1
            if (arr[j] <= x)
            {                         // 比arr[h]小的都在h前面
                i++;                  // 存储指数自增
                swap(arr[i], arr[j]); // 交换
            }
        }
        swap(arr[i + 1], arr[h]); // 分割点找到了
        return (i + 1);           // 返回分割点
    }

    void quickSortRecursive(int arr[], int l, int h)
    {
        if (l < h)
        {
            int p = partition(arr, l, h);
            quickSortRecursive(arr, l, p - 1);
            quickSortRecursive(arr, p + 1, h);
        }
    }

    /* A[] --> Array to be sorted,
    l --> Starting index,
    h --> Ending index */
    void quickSortIterative(int arr[], int l, int h)
    {
        // Create an auxiliary stack
        vector<int> stack(h - l + 1);

        // initialize top of stack
        int top = -1;

        // push initial values of l and h to stack
        stack[++top] = l;
        stack[++top] = h;

        // Keep popping from stack while is not empty
        while (top >= 0)
        {
            // Pop h and l
            h = stack[top--];
            l = stack[top--];

            // Set pivot element at its correct position
            // in sorted array
            int p = partition(arr, l, h);

            // If there are elements on left side of pivot,
            // then push left side to stack
            if (p - 1 > l)
            {
                stack[++top] = l;
                stack[++top] = p - 1;
            }

            // If there are elements on right side of pivot,
            // then push right side to stack
            if (p + 1 < h)
            {
                stack[++top] = p + 1;
                stack[++top] = h;
            }
        }
    }
};

// 堆排序：从堆顶把根卸出来放在有序区之前，再恢复堆。
class HeapSort
{
    void max_heapify(int arr[], int start, int end)
    {
        // 建立父节点和子节点
        int dad = start;
        int son = dad * 2 + 1;
        while (son <= end)
        {                                                  // 若子节点在范围内才做比较
            if (son + 1 <= end && arr[son] < arr[son + 1]) // 比较两个子节点，选更大的
                son++;
            if (arr[dad] > arr[son]) // 如果父节点大于子节点，说明调整完毕，直接跳出函数
                return;
            else
            { // 否则交换父子内容，换下来的父继续下筛
                swap(arr[dad], arr[son]);
                dad = son;
                son = dad * 2 + 1;
            }
        }
    }

    void heap_sort(int arr[], int len)
    {
        // 初始化，i从最后一个父节点开始调整
        for (int i = len / 2 - 1; i >= 0; i--)
            max_heapify(arr, i, len - 1);
        // 把最大的元素换到堆尾，然后排除这个元素进行上筛
        for (int i = len - 1; i > 0; i--)
        {
            swap(arr[0], arr[i]);
            max_heapify(arr, 0, i - 1);
        }
    }
};

// 归并排序：把数据分为两段，从两段中逐个选最小的元素移入新数据段的末尾。可从上到下或从下到上进行。
class MergeSort
{
public:
    template <typename T>
    void mergeSortRecursive(T arr[], T reg[], int start, int end)
    {
        if (start >= end)
            return;
        int len = end - start, mid = (len >> 1) + start;
        int start1 = start, end1 = mid;
        int start2 = mid + 1, end2 = end;
        mergeSortRecursive(arr, reg, start1, end1);
        mergeSortRecursive(arr, reg, start2, end2);

        int k = start;
        while (start1 <= end1 && start2 <= end2)
            reg[k++] = arr[start1] < arr[start2] ? arr[start1++] : arr[start2++]; // 合并
        while (start1 <= end1)
            reg[k++] = arr[start1++];
        while (start2 <= end2)
            reg[k++] = arr[start2++];
        for (k = start; k <= end; k++)
            arr[k] = reg[k]; // 写回原数组
    }

    template <typename T>
    void mergeSortMain(T arr[], const int len)
    {
        T *reg = new T[len];
        mergeSortRecursive(arr, reg, 0, len - 1);
        delete[] reg;
    }

    void mergeSortIterative(vector<int> &arr, int len)
    {
        vector<int> &a = arr;
        vector<int> b(len, 0);
        // vector<int>* c = new vector<int>(5,0);
        //(*c)[0] = 1;
        for (int seg = 1; seg < len; seg += seg)
        { // seg: 1 2 4 8
            for (int start = 0; start < len; start += seg + seg)
            {                                                                                     // low:start, mid:start+seg, high:start+seg+seg
                int low = start, mid = min(start + seg, len), high = min(start + seg + seg, len); // 由于和len比较，左闭右开
                int k = low;
                int start1 = low, end1 = mid;
                int start2 = mid, end2 = high;
                while (start1 < end1 && start2 < end2)
                    b[k++] = a[start1] < a[start2] ? a[start1++] : a[start2++];
                while (start1 < end1)
                    b[k++] = a[start1++];
                while (start2 < end2)
                    b[k++] = a[start2++];
            }
            auto temp = a;
            a = b;
            b = temp;
        }
        if (a != arr)
        {
            for (int i = 0; i < len; i++)
                b[i] = a[i];
            b = a;
        }
    }
};

// 希尔排序：每一轮按照事先决定的间隔进行插入排序，间隔会依次缩小，最后一次一定要是1。
template <typename T>
void shell_sort(T array[], int length)
{
    int h = 1;
    while (h < length / 3)
    {
        h = 3 * h + 1;
    }
    while (h >= 1)
    {
        for (int i = h; i < length; i++)
        {
            for (int j = i; j >= h && array[j] < array[j - h]; j -= h)
            {
                std::swap(array[j], array[j - h]);
            }
        }
        h = h / 3;
    }
}

// 计数排序：统计小于等于该元素值的元素的个数i，于是该元素就放在目标数组的索引i位（i≥0）。
void CountSort(vector<int> &vecRaw, vector<int> &vecObj)
{
    // 确保待排序容器非空
    if (vecRaw.size() == 0)
        return;

    // 使用 vecRaw 的最大值 + 1 作为计数容器 countVec 的大小
    int vecCountLength = (*max_element(begin(vecRaw), end(vecRaw))) + 1;
    vector<int> vecCount(vecCountLength, 0);

    // 统计每个键值出现的次数
    for (int i = 0; i < vecRaw.size(); i++)
        vecCount[vecRaw[i]]++;

    // 后面的键值出现的位置为前面所有键值出现的次数之和
    for (int i = 1; i < vecCountLength; i++)
        vecCount[i] += vecCount[i - 1];

    // 将键值放到目标位置
    for (int i = vecRaw.size(); i > 0; i--) // 此处逆序是为了保持相同键值的稳定性
        vecObj[--vecCount[vecRaw[i - 1]]] = vecRaw[i - 1];
}

/*****************

桶排序：将值为i的元素放入i号桶，最后依次把桶里的元素倒出来。

桶排序序思路：
1. 设置一个定量的数组当作空桶子。
2. 寻访序列，并且把项目一个一个放到对应的桶子去。
3. 对每个不是空的桶子进行排序。
4. 从不是空的桶子里把项目再放回原来的序列中。

假设数据分布在[0，100)之间，每个桶内部用链表表示，在数据入桶的同时插入排序，然后把各个桶中的数据合并。

*****************/
class BucketSort
{
public:
    const int BUCKET_NUM = 10;

    struct ListNode
    {
        explicit ListNode(int i = 0) : mData(i), mNext(NULL) {}
        ListNode *mNext;
        int mData;
    };

    // 桶插入
    ListNode *insert(ListNode *head, int val)
    {
        ListNode dummyNode;
        ListNode *newNode = new ListNode(val);
        ListNode *pre, *cur;
        dummyNode.mNext = head;
        pre = &dummyNode;
        cur = head;
        while (NULL != cur && cur->mData <= val)
        {
            pre = cur;
            cur = cur->mNext;
        }
        newNode->mNext = cur;
        pre->mNext = newNode;
        return dummyNode.mNext;
    }

    // 合并两个桶
    ListNode *merge(ListNode *head1, ListNode *head2)
    {
        ListNode dummyNode;
        ListNode *dummy = &dummyNode;
        while (NULL != head1 && NULL != head2)
        {
            if (head1->mData <= head2->mData)
            {
                dummy->mNext = head1;
                head1 = head1->mNext;
            }
            else
            {
                dummy->mNext = head2;
                head2 = head2->mNext;
            }
            dummy = dummy->mNext; // dummy相当于pre
        }
        if (NULL != head1)
            dummy->mNext = head1;
        if (NULL != head2)
            dummy->mNext = head2;
        return dummyNode.mNext;
    }

    void bucketSort(int n, int arr[])
    {
        vector<ListNode *> buckets(BUCKET_NUM, (ListNode *)(0));
        for (int i = 0; i < n; i++)
        {
            int index = arr[i] / BUCKET_NUM;
            ListNode *head = buckets.at(index);       // 找到对应桶的头指针
            buckets.at(index) = insert(head, arr[i]); // 插入到对应桶
        }
        ListNode *head = buckets.at(0);
        for (int i = 1; i < BUCKET_NUM; i++)
        {
            head = merge(head, buckets.at(i));
        }
        for (int i = 0; i < n; i++)
        {
            arr[i] = head->mData;
            head = head->mNext;
        }
    }
};

// 基数排序：一种多关键字的排序算法，可用桶排序实现。

int main()
{
    MergeSort ms;
    vector<int> arr{3, 44, 38, 5, 47, 15, 36, 26, 27, 2, 46, 4, 19, 50, 48};
    ms.mergeSortIterative(arr, 15);
    for (auto i : arr)
        cout << i << " ";
}
