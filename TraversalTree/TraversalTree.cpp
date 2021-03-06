// TraversalTree.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

struct Node
{
	int data;
	Node* lchild;
	Node* rchild;

	Node(int _data)
	{
		data = _data;
		lchild = rchild = NULL;
	}
};

void createTree(Node*& _node, const int* _data, int _num, int _id = 1)
{
	if (_id > _num) return;
	if (_data[_id] < 0) return;

	_node = new Node(_data[_id]);

	createTree(_node->lchild, _data, _num, _id * 2);
	createTree(_node->rchild, _data, _num, _id * 2 + 1);
}

void DlrRcursive(Node* _root)
{
	cout << _root->data << " ";
	if (_root->lchild)
		DlrRcursive(_root->lchild);
	if (_root->rchild)
		DlrRcursive(_root->rchild);
}

void DlrNonRcursive(Node* _root)
{
	stack<Node*> _stack;
	while (_root != NULL || !_stack.empty())
	{
		while (_root != NULL)
		{
			cout << _root->data << " ";
			_stack.push(_root);
			_root = _root->lchild;
		}

		if (!_stack.empty())
		{
			_root = _stack.top();
			_stack.pop();
			_root = _root->rchild;
		}
	}
	cout << endl;
}

void LdrRcursive(Node* _root)
{
	if (_root->lchild)
		LdrRcursive(_root->lchild);
	cout << _root->data << " ";
	if (_root->rchild)
		LdrRcursive(_root->rchild);

}

void LdrNonRcursive(Node* _root)
{
	stack<Node*> _stack;
	while (_root != NULL || !_stack.empty())
	{
		while (_root != NULL)
		{
			_stack.push(_root);
			_root = _root->lchild;
		}

		if (!_stack.empty())
		{
			_root = _stack.top();
			_stack.pop();
			cout << _root->data << " ";
			_root = _root->rchild;
		}
	}
	cout << endl;
}

void LrdRcursive(Node* _root)
{
	if (_root->lchild)
		LrdRcursive(_root->lchild);
	if (_root->rchild)
		LrdRcursive(_root->rchild);
	cout << _root->data << " ";
}

void LrdNonRcursive(Node* _root)
{
	if (!_root) return;

	stack<Node*> _stack;
	while (true)
	{
		while (_root->lchild)  //深入左子树，找到最左侧的节点
		{
			_stack.push(_root);
			_root = _root->lchild;
		}

		if (_root->rchild)  //如果最左侧的节点有右孩子，则进入右孩子进行处理
		{
			_stack.push(_root);
			_root = _root->rchild;
			continue;
		}

		while (true)
		{
			cout << _root->data << " ";  //输出叶子节点
			if (_stack.empty())
			{
				cout << endl;
				return;			//栈空，结束
			}

			Node* _node = _stack.top();
			if (_node->lchild == _root && _node->rchild)  //判断当前叶子节点是那一侧的孩子，如果是左孩子且父节点有右孩子，则进入右孩子处理										
			{
				_root = _node->rchild;
				break;
			}

			_root = _stack.top();	//如果是左孩子且父节点没有右孩子，或者已经是右孩子，说明需要输出父节点了，把父节点设为当前节点
			_stack.pop();
		}
	}
}

void Bfs(Node* _root)
{
	queue<Node*> _queue;
	if (!_root) return;

	_queue.push(_root);
	while (!_queue.empty())
	{
		_root = _queue.front();
		_queue.pop();
		cout << _root->data << " ";
		if (_root->lchild) _queue.push(_root->lchild);
		if (_root->rchild) _queue.push(_root->rchild);
	}
	cout << endl;
}

int main()
{
	int data[] = { 0, 35, 20, 40, 15, 29, -1, 50, -1, 16, 28, 30, -1, -1, 45, 55 };   //格式：从根节点到最后一个节点，编号1开始，按照完全二叉树描述，节点不存在用负值标识。

	Node* tree = NULL;
	createTree(tree, data, 15);

	DlrRcursive(tree); cout << endl;
	DlrNonRcursive(tree);
	cout << endl;

	LdrRcursive(tree); cout << endl;
	LdrNonRcursive(tree);
	cout << endl;

	LrdRcursive(tree); cout << endl;
	LrdNonRcursive(tree);
	cout << endl;

	Bfs(tree);
	cout << endl;
	return 0;
}



