// Huffman coding
// ~

#include <iostream>

using namespace std;

// huffman tree node
struct CNode
{
	int value;
	int weight;
	bool flag;
	CNode *left;
	CNode *right;
};

CNode * huffmanCoding(CNode *p, int len); //构造huffman编码树，以生成huffman code
void showHuffmanCode(CNode *p, int *code, int len);
void showCode(int value, int *code, int len);

int main()
{
	char str[100];
	cout<<"please input a sequence of number :";
	cin>>str;
	
	// 统计数字0-9出现的次数，作权重
	int count[10] = {0};
	for(int i=0; str[i]!='\0'; i++)
	{
		if(str[i] < '0' || str[i] > '9')
			continue;
		count[str[i]-'0']++;
	}
	
	int n = 0;
	for(i=0; i<10; i++)
	{
		if(count[i] == 0)
			continue;
		n++;
		cout<<i<<" : "<<count[i]<<" "<<endl;
	}
	
	// 统一分配2n个结点，n个叶子，构造的二叉树不超过2n结点
	CNode *p = new CNode[2*n];
	// 由统计构造出现各数字的huffman tree结点，并初始化
	i = 0;
	for(int j=0; i<10; i++)
	{
		if(count[i] == 0)
			continue;
		p[j].value = i;
		p[j].weight = count[i];
		p[j].flag = false;
		p[j].left = NULL;
		p[j].right = NULL;
		j++;
	}
	// 叶子结点后的结点将用来存放两两结合的huffman tree而产生的新树，此处先初始化
	for(j=n; j<2*n; j++)
	{
		p[j].value = -1;
		p[j].weight = -1;
		p[j].flag = false;
		p[j].left = NULL;
		p[j].right = NULL;
	}
	
	cout<<endl;
	CNode *root = huffmanCoding(p, n);
	int code[15], k=0;
	showHuffmanCode(root, code, k);
	delete [] p;

	return 0;
}

// ~huffman coding
// ~
CNode * huffmanCoding(CNode *p, int len)
{
	int min, secMin;
	int m, sm;
	
	// 从各叶子结点组成huffman tree队列中选出最小+次小结合为新的huffman tree加进队列，
	// 直到只剩一棵huffman tree，即为构造的结果，返回
	while(1)
	{
		// 初始化最小huffman tree树根权值下标，以便检测挑选结果
		m = -1;
		min = -1;
		// 遍历从未访问过的huffman tree中挑选树根权值最小两棵树
		for(int i=0; i<len; i++)
		{
			if(p[i].flag == true)
				continue;
			// 发现更小的权值，当前最小变次小，更新最小，记录下标+权值
			if(m == -1 || min > p[i].weight)
			{
				sm = m;
				secMin = min;
				m = i;
				min = p[i].weight;
			}
			// 最小不变时，检测是否更新次小，换次小同样记录下标+权值
			else if(secMin == -1 || secMin > p[i].weight)
			{
				sm = i;
				secMin = p[i].weight;
			}
		}
		
		// 检测是否挑选出最小+次小两huffman tree，只剩最小时，即为最终huffman tree
		if(m != -1 && sm == -1)
			return &p[m];
			
		// 标记访问过的huffman tree
		p[m].flag = true;
		p[sm].flag = true;
		// 最小+次小两huffman tree，结合出新的huffman tree，放到队列最后
		p[len].weight = p[m].weight + p[sm].weight;
		p[len].left = &p[m];
		p[len].right = &p[sm];
		// 最后记得队列长度自增，把新的huffman tree算进来
		len++;
	}
}

// 用栈结合递归，输出各叶子结点的huffman code
void showHuffmanCode(CNode *p, int *code, int len)
{
	if(p->left == NULL && p->right == NULL)
	{
		showCode(p->value, code, len); // 叶子，输出
		return ;
	}
	if(p->left != NULL)
	{
		code[len++] = 0; // 左方向，0进栈
		showHuffmanCode(p->left, code, len);
		len--; // 出栈
	}
	if(p->right != NULL)
	{
		code[len++] = 1; // 右方向，1进栈
		showHuffmanCode(p->right, code, len);
		len--; // 出栈
	}
}

void showCode(int value, int *code, int len)
{
	if(len == 0)
		return ;
		
	cout<<value<<" : ";
	for(int i=0; i<len; i++)
		cout<<code[i];
	cout<<endl;
}