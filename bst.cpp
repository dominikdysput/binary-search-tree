#include <iostream>	
#include <stdio.h>
#include <time.h>
#include <fstream>
#include <string>
using namespace std;
struct tree {
	int key;
	char tab[10];
	struct tree *left, *right;
};
tree *Create(tree *&HEAD, int value);
void Insert(tree *&HEAD, int value);
tree *Find(tree *HEAD, int value);
void InsertMany(tree *&HEAD, int value);
int DisplayPostOrder(tree *HEAD);
int DisplayInOrder(tree *HEAD);
int DisplayPreOrder(tree *HEAD);
void Delete(tree *&HEAD, int value);
int static VisitedNodesPreOrder = 0;
int static VisitedNodesInOrder = 0;
int static VisitedNodesPostOrder = 0;

int main()
{
	srand(time(NULL));
	int k1, k2, k3, k4, x;
	clock_t begin, end;
	double time_spent;
	begin = clock();
	std::string name = "inlab03.txt";
	std::ifstream file;
	file.open(name.c_str());
	if (!file.good()) return -3;
	else
		file >> x >> k1 >> k2 >> k3 >> k4;
	file.close();
	tree *Tree = nullptr;
	Delete(Tree, k1);
	Insert(Tree, k1);
	InsertMany(Tree, x);
	cout << "INORDER ____________________________" << endl;
	DisplayInOrder(Tree);
	cout << "Visited nodes: " << VisitedNodesInOrder << endl;
	VisitedNodesInOrder = 0;
	cout << "PREORDER____________________________" << endl;
	DisplayPreOrder(Tree);
	cout << "Visited nodes: " << VisitedNodesPreOrder << endl;
	VisitedNodesPreOrder = 0;
	Insert(Tree, k2);
	cout << "INORDER ____________________________" << endl;
	DisplayInOrder(Tree);
	cout << "Visited nodes: " << VisitedNodesInOrder << endl;
	VisitedNodesInOrder = 0;
	Insert(Tree, k3);
	Insert(Tree, k4);
	Delete(Tree, k1);
	cout << "preRDER ____________________________" << endl;
	DisplayPreOrder(Tree);
	cout << "Visited nodes: " << VisitedNodesPreOrder << endl;
	VisitedNodesPreOrder = 0;
	Find(Tree, k1);
	Delete(Tree, k2);
	cout << "INORDER ____________________________" << endl;
	DisplayInOrder(Tree);
	cout << "Visited nodes: " << VisitedNodesInOrder << endl;
	VisitedNodesInOrder = 0;
	Delete(Tree, k3);
	Delete(Tree, k4);
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	cout << "The running time of the algorithm: " << time_spent << endl;
	return 0;
}
tree *Create(tree *&HEAD, int value)
{
	if (HEAD == nullptr)
	{
		HEAD = (tree*)malloc(sizeof(tree));
		HEAD->key = value;
		string s = to_string(value);
		for (int i = 0; i < s.size(); i++) {
			if (i >= 10)
			{
				break;
			}
			HEAD->tab[i] = s[i];
		}
		HEAD->left = nullptr;
		HEAD->right = nullptr;
	}
	return HEAD;
}
void Insert(tree*&HEAD, int value)
{
	tree *temp = HEAD;

	if (HEAD == nullptr)
	{
		Create(temp, value);
		HEAD = temp;
		return;
	}
	else if (temp->key == value)
	{
		cout << "Element exist and is root" << endl;
		return;
	}
	else
	{
		while (1)
		{
			if (temp->key > value)
			{
				if (temp->left == NULL)
				{
					tree *lisc = Create(temp->left, value);
					temp->left = lisc;
					break;
				}
				temp = temp->left;

			}
			else if (temp->key < value)
			{
				if (temp->right == NULL)
				{
					tree *lisc = Create(temp->right, value);
					temp->right = lisc;
					break;
				}
				temp = temp->right;
			}
			else if (temp->key == value)
			{
				cout << "This key already exist" << endl;
				break;
			}
		}
		return;
	}
	HEAD = temp;
	return;
}
void InsertMany(tree *&HEAD, int value)
{
	tree *temp = nullptr;
	tree *temp1 = HEAD;
	if (HEAD == nullptr)
	{
		Create(temp1, rand() % 20000 - 10000);
	}
	for (int i = 1; i < value; i++) {
		int rnd = rand() % 20000 - 10000;
		while (temp)
		{
			temp = Find(temp1, rnd);
		}
		Insert(temp1, rnd);
	}
	HEAD = temp1;
}
tree *Find(tree * HEAD, int value)
{
	tree *lisc = HEAD;
	if (HEAD == nullptr)
	{
		cout << "Tree is empty" << endl;
		return 0;
	}
	else if (lisc->key == value)
	{
		cout << "Found in root! " << lisc->key << endl;
		return lisc;
	}
	while (1)
	{
		if (lisc != NULL && lisc->key != value)
		{
			if (lisc->key > value)
			{
				lisc = lisc->left;
			}
			else if (lisc->key < value)
			{
				lisc = lisc->right;
			}
		}
		else if (lisc != NULL && lisc->key == value)
		{
			cout << "Found!" << endl;
			break;
		}
		else
		{
			cout << "Did'n find element!" << endl;
			break;
		}
	}
	return lisc;
}
int DisplayPostOrder(tree *HEAD)
{
	if (HEAD == NULL)
	{
		return 0;
	}
	DisplayPostOrder(HEAD->left);
	DisplayPostOrder(HEAD->right);
	cout << HEAD->key << " ";
	cout << endl;
	return VisitedNodesPostOrder++;
}
int DisplayInOrder(tree *HEAD)
{
	if (HEAD == nullptr)
	{
		return 0;
	}
	DisplayInOrder(HEAD->left);
	cout << HEAD->key << " ";
	cout << endl;
	DisplayInOrder(HEAD->right);
	return VisitedNodesInOrder++;
}
int DisplayPreOrder(tree *HEAD)
{
	tree *temp = HEAD;
	if (HEAD == NULL)
	{
		return 0;
	}
	cout << HEAD->key << " ";
	cout << endl;
	DisplayPreOrder(HEAD->left);
	DisplayPreOrder(HEAD->right);
	return VisitedNodesPreOrder++;
}
void Delete(tree *&HEAD, int value)
{
	tree *temp = HEAD;
	if (HEAD == nullptr)
	{
		cout << "Tree is empty, the element cannot be deleted" << endl;
		return;
	}
	if (!Find(HEAD, value))
	{
		return;
	}
	if (HEAD->left == nullptr && HEAD->right == nullptr && HEAD->key == value) //head doesn't have children, but its the element
	{
		delete HEAD;
		HEAD = nullptr;
		cout << "W drzewie byl tylko 1 element, ktory byl value i zostal skasowany" << endl;
		cout << "In tree was only 1 element, and is deleted" << endl;
		return;
	}
	tree *toDeleted = Find(HEAD, value);
	tree *prev = nullptr;
	while (temp && temp->key != value)
	{
		prev = temp;
		if (value < temp->key)
		{
			temp = temp->left;
		}
		else if (value > temp->key)
		{
			temp = temp->right;
		}
	}
	// delete last element, who's doesn't have children
	if (toDeleted->left == nullptr && toDeleted->right == nullptr)
	{
		if (prev->left == temp)
			prev->left = nullptr;
		else
			prev->right = nullptr;
		delete toDeleted;
		cout << "Deleting item : " << value << " is complited!" << endl;
		return;
	}
	//delete with only 1 child
	if ((toDeleted->left != nullptr && toDeleted->right == nullptr) || (toDeleted->left == nullptr && toDeleted->right != nullptr))
	{
		if (toDeleted->left == nullptr && toDeleted->right != nullptr)// right child
		{
			if (prev->left == toDeleted)
			{
				prev->left = toDeleted->right;
				delete toDeleted;
				toDeleted = nullptr;
				cout << "Deleting item : " << value << " is complited!" << endl;
				return;
			}
			else
			{
				prev->right = toDeleted->right;
				delete toDeleted;
				toDeleted = nullptr;
				cout << "Deleting item : " << value << " is complited!" << endl;
				return;
			}
		}
		else if (toDeleted->left != nullptr && toDeleted->right == nullptr) //has 1 child, whos left
		{
			if (prev->left == toDeleted)
			{
				prev->left = toDeleted->left;
				delete toDeleted;
				toDeleted = nullptr;
				cout << "Deleting item : " << value << " is complited!" << endl;
				return;
			}
			else if (prev->right == toDeleted)
			{
				prev->right = toDeleted->left;
				delete toDeleted;
				toDeleted = nullptr;
				cout << "Deleting item : " << value << " is complited!" << endl;
				return;
			}
		}
	}
	if (toDeleted->left != nullptr && toDeleted->right != nullptr)
	{
		if (toDeleted->right->right == nullptr && toDeleted->right->left == nullptr)
		{
			prev->left = toDeleted->right;
			prev->left->left = toDeleted->left;
			delete toDeleted;
			cout << "Deleting item : " << value << " is complited!" << endl;
			return;
		}
		else
		{
			tree* parentTmp = nullptr;
			tree* childTmp = toDeleted->left;
			while (childTmp != nullptr)			
			{
				if (childTmp->right == nullptr)
					break;
				parentTmp = childTmp;						
				childTmp = parentTmp->right;				
			}
			if (childTmp)
			{
				if (prev)
				{
					if (prev->left == toDeleted)
					{
						prev->left = childTmp;
						delete toDeleted;
						return;
					}
					else
					{
						prev->right = childTmp;
						delete toDeleted;
						return;
					}
				}
				else
				{
					childTmp->right = temp->right;
					childTmp->left = temp->left;
					parentTmp->right = NULL;
					delete HEAD;
					HEAD = childTmp;
				}
			}
		}
	}
	return;
}

