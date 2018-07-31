#include <iostream>


using namespace std;

class Node {
public:
	static Node* root;
	int m_data;
	Node(int data) :m_data(data) { next = NULL; }
	Node * next;
};

Node* Node::root = NULL;

Node *reversenode(Node * node)
{
	if (node->next == NULL)
	{
		Node::root = node;
		return node;
	}
	else {
		reversenode(node->next)->next = node;
	}
	return node;
}



int main()
{
	Node a(0);
	Node b(1);  a.next = &b;
	Node c(2);  b.next = &c;
	Node d(3);  c.next = &d;
	Node e(4);  d.next = &e;
	Node f(5);  e.next = &f;
	Node g(6);  f.next = &g;

	reversenode(&a)->next = NULL;
	auto begin = &g;
	for (; begin != NULL; begin = begin->next)
	{
		cout << begin->m_data << endl;
	}


}