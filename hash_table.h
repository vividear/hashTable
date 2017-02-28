#include <iostream>
#include <string>
using namespace std;
struct Node     
{
	string key;
	int addr;
	Node * next;
};
class hash_table
{
private:
	size_t SDBMHash(string s1);  //hash function
	static const int sizet= 10000;  //table size
	Node * hash_map[sizet];
	int numItem;
public:
	hash_table() {
		numItem = 0;
		for (int i = 0; i < sizet; i++) hash_map[i] = nullptr; } 
        ~hash_table() {
		cout << "Start destruct deletion…" << endl;
		for (int i = 0; i < sizet; i++) 
		if (hash_map[i] != NULL)
		{
			Node* p = hash_map[i];
			while (hash_map[i])
			{
				p = hash_map[i];
				hash_map[i] = p->next;
				delete p;
			}
		}
	 ; }
	void hash_insert(string key, int addr); 
	void hash_insert(Node* New_Node);

	void hash_delete(string _key); //delete an item
	void hash_delete(string _key, bool alldelete); //delete all items with same index

	Node* hash_search(string _key); 
};

void hash_table::hash_insert(string keys, int addr)
{
	Node * New_Node = new Node;
	New_Node->key = keys;
	New_Node->addr = addr;
	hash_insert(New_Node);
}

void hash_table::hash_insert(Node* New_Node)
{
	New_Node->next = hash_map[SDBMHash(New_Node->key)];
	hash_map[SDBMHash(New_Node->key)] = New_Node;
	numItem++;
}

void hash_table::hash_delete(string keys,bool alldelete)
{
	if (alldelete) {
		if (hash_map[SDBMHash(keys)] == nullptr)
			return;
		size_t locat = SDBMHash(keys);
		Node* p = hash_map[locat];
		while (hash_map[locat])
		{
			p = hash_map[locat];
			hash_map[locat] = p->next;
			delete p;
		}
	}
	else hash_delete(keys);
}

void hash_table::hash_delete(string keys)
{
	if (hash_map[SDBMHash(keys)] == nullptr)
		return;
	size_t locat = SDBMHash(keys);
	Node * p = hash_map[locat];
	Node * q = hash_map[locat];
	while (p != nullptr)
	{
		if (p->key == keys)
			break;
		q = p;
		p = p->next;
	}

	if (q == hash_map[locat] && p == q)
		hash_map[locat] = p->next;
	else
		q->next = p->next;
	if (p != nullptr) delete p;
	else cout << "no such delete item" << endl;
}


Node* hash_table::hash_search(string keys)
{
	if (hash_map[SDBMHash(keys)] == nullptr)
	{
		return nullptr;
	}

	Node* p = hash_map[SDBMHash(keys)];
	while (p)
	{
		if (p->key == keys)
			return p;
		p = p->next;
	}
	return nullptr;
}
size_t hash_table::SDBMHash(string s1)
{
	const char *str = s1.c_str();
	register size_t hash = 0;
	while (size_t ch = (size_t)*str++)
	{
		hash = 65599 * hash + ch;
	}
	return hash%this->sizet;
}
