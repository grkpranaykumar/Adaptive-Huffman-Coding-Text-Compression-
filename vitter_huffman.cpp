#include <bits/stdc++.h>
using namespace std;
struct node
{
	char symbol;
	int weight;
	struct node *parent;
	struct node *left;
	struct node *right;
};
int node_count = 127;
struct node* tree[128];
struct node* nyt;
map<char,string> prefix;
map<char,int> present;
void clear()
{
	prefix.clear();
	present.clear();
}
string getbinary(int i)
{
	string code = "";
	int j = 6;	
	while(j>=0)
	{
		char c = i%2+'0';
		code = c + code;
		j--;
		i = i/2;
	}
	return code;
}
void setprefixes()
{
	for(int i=0;i<126;i++)
	{
		prefix.insert(make_pair((char)i,getbinary(i)));
	}
}
struct node* newnode(char a)
{
    struct node* temp = (struct node*)malloc(sizeof(struct node));
	temp->symbol = a;
	temp->value = 0;
	temp->parent = NULL;
	temp->left = NULL;
	temp->right = NULL;	    
    return temp;
}
string getcode(struct node* curr)
{
	if(curr==root)
	{
		return "";
	}
	struct node* temp = curr->parent;
	if(temp->left==curr)
	{
		return getcode(temp)+'0';
	}
	else
	{
		return getcode(temp)+'1';
	}
}
void update(char c)
{
	struct node* leaf = NULL;
	struct node* curr = nyt;
	if(present.find(c)==present.end())
	{
		tree[node_count] = newnode(c);
		curr->right = tree[node_count];
		tree[node_count]->parent = curr;
		leaf = tree[node_count]
		node_count--;
		tree[node_count] = newnode('*');
		curr->left = tree[node_count];
		tree[node_count]->parent = curr;
		nyt = tree[node_count];
		node_count--;
	}
	else
	{
		
	}
}
int main()
{
	clear();
	setprefixes();
	tree[node_count] = newnode('*');
	nyt = tree[node_count];
	node_count--;
	ifstream in("input.txt");
    ofstream out("vitter_output.txt");
    string line;
    int bitcount = 1;
    char byte = 0b00100000;
    clock_t start = clock();
    while(getline(in,line))
    {
    	line += '\n';
    	for(int i=0;i<line.length();i++)
    	{
    		char c = line[i];
    		string code;
    		if(present.find(c)==present.end())
    		{
    			code = getcode(nyt);
    			code += prefix.find(c)->second;
    			update(c);
    		}
    		else
    		{
    			int num = present.find(c)->second;
    			code = getcode(tree[num]);
    			update(c);
    		}
    		for(int j=0;j<code.length();j++)
			{
				bool bit;
				if(code[j]=='1')
				{
					bit = true;
				}
				else 
				{
					bit = false;
				}
				if(bitcount==2)
				{
					byte = byte << 1 | true;
					bitcount++;
				}
				byte = byte << 1 | bit;
				bitcount++;  
				if(bitcount==8)
				{
					out << byte;
					bitcount = 1;
					byte = 0b00100000;
				}
			}
    	}
    }
    out << byte;
    out << bitcount;
    clock_t end = clock();
    in.close();
    out.close();
    printf("%f\n",((double)end-start));
	return 0;
}