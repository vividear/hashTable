#include "hash_table.h"

void main()
{
	hash_table hashtable;
	hashtable.hash_insert("google16/blog24", 3);
	Node* p=hashtable.hash_search("google16/blog24");
	cout << p->addr << endl;
	system("pause");
}