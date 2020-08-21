#include <iostream>

struct Tree {
	Tree *left;
	Tree *right;
	int key;

	Tree(int Key = -1) {
		left = right = nullptr;
		key = Key;
	}
	~Tree() { 
		if (left) delete left;
		if (right) delete right;
	}
};

void PrintTree(Tree*, int);
void AddNode(Tree**, int);
void DeleteNode(Tree**, int);
void DelNodeWith2Son(Tree**, Tree**);

int main()
{
	Tree *root = nullptr;		
	int x, number = 0;

	std::cout << "Enter the list of keys with a space:  (When done, type \"y\" and press \"enter\")\n";
	while (std :: cin >> x) {
		AddNode(&root, x);
	}
	std::cin.clear();
	std::cin.ignore();
	std::cout << "\nGood! The tree has been built\n\n";
	std::cout << "What to do ? \n1) Add node\n2) Delete node\n3) Print the tree\n4) Close program\n";
	while (true) {
		std::cout << "\nEnter number: " ;
		std:: cin >> number;
		switch (number){
			case 1: std::cout << "Enter the number to add: ";  std::cin >> x; AddNode(&root, x); break;
			case 2: std::cout << "Enter the number to delete: ";  std::cin >> x; DeleteNode(&root, x); break;
			case 3: PrintTree(root, 0); break;
			case 4: delete root; return 0;
			default:  std::cout << "invalid input, try again:)\n";break;
		}
	}
}

void PrintTree(Tree *root, int level) {
	if (root == nullptr) return;
	PrintTree(root->right, level + 1);
	for (int i = 0; i < level; i++)
		std::cout << "     ";
	std::cout << root->key << "\n";
	PrintTree(root->left, level + 1);
}

void AddNode(Tree **root, int x) {
	if (*root == nullptr) {
		*root = new Tree(x);
		return;
	}
	if (x < (*root)->key)
		AddNode(&(*root)->left, x);
	else AddNode(&(*root)->right, x);
}

void DeleteNode(Tree **root, int x)
{
	if (*root == nullptr) {
		std::cout << "No element";
		return;
	}
	if (x < (*root)->key) DeleteNode(&(*root)->left, x);
	else if (x >(*root)->key) DeleteNode(&(*root)->right, x);
	else {
		Tree* delNode = *root;
		if (delNode->right == nullptr) *root = delNode->left;
		else if (delNode->left == nullptr) *root = delNode->right;
		else DelNodeWith2Son(&delNode, &delNode->right);

		delNode->left = delNode->right = nullptr;
		delete delNode;
	}
}

void DelNodeWith2Son(Tree **node, Tree **rightNode) {
	if ((*rightNode)->left != nullptr)
		DelNodeWith2Son(&(*node), &(*rightNode)->left);
	else {
		(*node)->key = (*rightNode)->key;
		*node = *rightNode;
		*rightNode = (*rightNode)->right;
	}
}