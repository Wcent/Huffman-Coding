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

CNode * huffmanCoding(CNode *p, int len); //����huffman��������������huffman code
void showHuffmanCode(CNode *p, int *code, int len);
void showCode(int value, int *code, int len);

int main()
{
	char str[100];
	cout<<"please input a sequence of number :";
	cin>>str;
	
	// ͳ������0-9���ֵĴ�������Ȩ��
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
	
	// ͳһ����2n����㣬n��Ҷ�ӣ�����Ķ�����������2n���
	CNode *p = new CNode[2*n];
	// ��ͳ�ƹ�����ָ����ֵ�huffman tree��㣬����ʼ��
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
	// Ҷ�ӽ���Ľ�㽫�������������ϵ�huffman tree���������������˴��ȳ�ʼ��
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
	
	// �Ӹ�Ҷ�ӽ�����huffman tree������ѡ����С+��С���Ϊ�µ�huffman tree�ӽ����У�
	// ֱ��ֻʣһ��huffman tree����Ϊ����Ľ��������
	while(1)
	{
		// ��ʼ����Сhuffman tree����Ȩֵ�±꣬�Ա�����ѡ���
		m = -1;
		min = -1;
		// ������δ���ʹ���huffman tree����ѡ����Ȩֵ��С������
		for(int i=0; i<len; i++)
		{
			if(p[i].flag == true)
				continue;
			// ���ָ�С��Ȩֵ����ǰ��С���С��������С����¼�±�+Ȩֵ
			if(m == -1 || min > p[i].weight)
			{
				sm = m;
				secMin = min;
				m = i;
				min = p[i].weight;
			}
			// ��С����ʱ������Ƿ���´�С������Сͬ����¼�±�+Ȩֵ
			else if(secMin == -1 || secMin > p[i].weight)
			{
				sm = i;
				secMin = p[i].weight;
			}
		}
		
		// ����Ƿ���ѡ����С+��С��huffman tree��ֻʣ��Сʱ����Ϊ����huffman tree
		if(m != -1 && sm == -1)
			return &p[m];
			
		// ��Ƿ��ʹ���huffman tree
		p[m].flag = true;
		p[sm].flag = true;
		// ��С+��С��huffman tree����ϳ��µ�huffman tree���ŵ��������
		p[len].weight = p[m].weight + p[sm].weight;
		p[len].left = &p[m];
		p[len].right = &p[sm];
		// ���ǵö��г������������µ�huffman tree�����
		len++;
	}
}

// ��ջ��ϵݹ飬�����Ҷ�ӽ���huffman code
void showHuffmanCode(CNode *p, int *code, int len)
{
	if(p->left == NULL && p->right == NULL)
	{
		showCode(p->value, code, len); // Ҷ�ӣ����
		return ;
	}
	if(p->left != NULL)
	{
		code[len++] = 0; // ����0��ջ
		showHuffmanCode(p->left, code, len);
		len--; // ��ջ
	}
	if(p->right != NULL)
	{
		code[len++] = 1; // �ҷ���1��ջ
		showHuffmanCode(p->right, code, len);
		len--; // ��ջ
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