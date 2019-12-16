#ifndef TREE_MANAGEMENT_H
#define TREE_MANAGEMENT_H

using namespace std;

template<class T>
class binaryTree;

template<class T>
class Node
{
    public:
        T value;
		int position;
        int height;
        Node *left;
        Node *right;
        Node(T x, int pos);
        ~Node();
        friend class binaryTree<T>;
};

template<class T>
class binaryTree
{
    public:
		int count = 0;
        binaryTree();
        ~binaryTree();
        void insertValue(T key);
        void prePrint();
        void inPrint();
        void postPrint();
        bool searchTree(T key);
        int getHeight(Node<T> *leaf);
        int maxHeight(int lhs, int rhs);
        int countNodes();
        void removeVal(T data);
    private:
        Node<T> *root;
        Node<T> *rotateWithLeftChild(Node<T> *l2);
        Node<T> *doubleWithLeftChild(Node<T> *l1);
        Node<T> *rotateWithRightChild(Node<T> *l3);
        Node<T> *doubleWithRightChild(Node<T> *l1);
        void destroyTree(Node<T> *leaf);
        Node<T> *insertLeaf(T key, Node<T> *leaf);
        bool searchLeaf(T key, Node<T> *leaf);
        void preOrderPrint(Node<T> *leaf);
        void inOrderPrint(Node<T> *leaf);
        void postOrderPrint(Node<T> *leaf);
        int countNodes(Node<T> *r);
        Node<T>* FindMin(Node<T>* leaf);
        Node<T>* deleteVal(Node<T> *leaf, T data);
        friend class Node<T>;
};

template<class T>
Node<T>::Node(T x, int pos)
{
    //std::cout<<"Node()"<<std::endl;
    left = NULL;
    right = NULL;
    value = x;
	position = pos;
    height = 0;
}

template<class T>
Node<T>::~Node()
{
    //std::cout<<"~Node()"<<std::endl;
}

template<class T>
binaryTree<T>::binaryTree()
{
    //std::cout<<"binaryTree()"<<std::endl;
    root = NULL;
}

template<class T>
binaryTree<T>::~binaryTree()
{
    //std::cout<<"~binaryTree()"<<std::endl;
    destroyTree(root);
}

template<class T>
Node<T>* binaryTree<T>::insertLeaf(T key, Node<T> *leaf)
{
    if(leaf == NULL)
	{
        leaf = new Node<T>(key, count);
		count++;
	}
    else if(key < leaf->value)
    {
        leaf->left = insertLeaf(key, leaf->left);
        if(getHeight(leaf->left) - getHeight(leaf->right) == 2)
        {
            if(key < leaf->left->value)
                leaf = rotateWithLeftChild(leaf);
            else
                leaf = doubleWithLeftChild(leaf);
        }
    }
    else if(key >= leaf->value)
    {
        leaf->right = insertLeaf(key, leaf->right);
        if(getHeight(leaf->right) - getHeight(leaf->left) == 2)
        {
            if(key >= leaf->right->value)
                leaf = rotateWithRightChild(leaf);
            else
                leaf = doubleWithRightChild(leaf);
        }
    }
    leaf->height = maxHeight(getHeight(leaf->left), getHeight(leaf->right)) + 1;
    return leaf;
}

template<class T>
void binaryTree<T>::insertValue(T key)
{
        root = insertLeaf(key, root);
}

template<class T>
Node<T>* binaryTree<T>::rotateWithLeftChild(Node<T> *l2)
{
    Node<T> *l1 = l2->left;
    l2->left = l1->right;
    l1->right = l2;
    l1->height = maxHeight(getHeight(l1->left), getHeight(l1->right)) + 1;
    l2->height = maxHeight(getHeight(l2->left), l2->height) + 1;
    return l1;
}
template<class T>
Node<T>* binaryTree<T>::rotateWithRightChild(Node<T> *l1)
{
    Node<T> *l2 = l1->right;
    l1->right = l2->left;
    l2->left = l1;
    l1->height = maxHeight(getHeight(l1->left), getHeight(l1->right)) + 1;
    l2->height = maxHeight(getHeight(l2->left), l1->height) + 1;
    return l2;
}
template<class T>
Node<T>* binaryTree<T>::doubleWithLeftChild(Node<T> *l3)
{
    l3->left = rotateWithRightChild(l3->left);
    return rotateWithLeftChild(l3);
}
template<class T>
Node<T>* binaryTree<T>::doubleWithRightChild(Node<T> *l1)
{
    l1->right = rotateWithLeftChild(l1->right);
    return rotateWithRightChild(l1);
}

template<class T>
void binaryTree<T>::destroyTree(Node<T> *leaf)
{
    if(leaf)
    {
        destroyTree(leaf->left);
        destroyTree(leaf->right);
        delete leaf;
    }
}

template<class T>
int binaryTree<T>::getHeight(Node<T> *leaf)
{
    return ((leaf == NULL) ? -1 : leaf->height);
}
template<class T>
int binaryTree<T>::maxHeight(int lhs, int rhs)
{
    return (lhs > rhs ? lhs : rhs);
}

template<class T>
void binaryTree<T>::preOrderPrint(Node<T> *leaf)
{
    if(leaf)
    {
        cout<<leaf->value<<" ";
        preOrderPrint(leaf->left);
        preOrderPrint(leaf->right);
    }
}
template<class T>
void binaryTree<T>::prePrint()
{
    preOrderPrint(root);
    cout<<endl;
}
template<class T>
void binaryTree<T>::inOrderPrint(Node<T> *leaf)
{
    if(leaf)
    {
        inOrderPrint(leaf->left);
        cout<<leaf->value<<" ";
        inOrderPrint(leaf->right);
    }
}
template<class T>
void binaryTree<T>::inPrint()
{
    inOrderPrint(root);
    cout<<endl;
}
template<class T>
void binaryTree<T>::postOrderPrint(Node<T> *leaf)
{
    if(leaf)
    {
        postOrderPrint(leaf->left);
        postOrderPrint(leaf->right);
        cout<<leaf->value<<" ";
    }
}
template<class T>
void binaryTree<T>::postPrint()
{
    postOrderPrint(root);
    cout<<endl;
}

template<class T>
bool binaryTree<T>::searchTree(T key)
{
    return searchLeaf(key, root);
}

template<class T>
bool binaryTree<T>::searchLeaf(T key, Node<T> *leaf)
{
        if(leaf == NULL)
        {
            return false;
        }
        else if(key == leaf->value)
        {
            return true;
        }
        else if(key < leaf->value)
        {
            return searchLeaf(key, leaf->left);
        }
        else if(key > leaf->value)
        {
            return searchLeaf(key, leaf->right);
        }
        return false;
}

template<class T>
int binaryTree<T>::countNodes()
{
    return countNodes(root);
}

template<class T>
int binaryTree<T>::countNodes(Node<T> *r)
{
    if (r == NULL)
        return 0;
    else
    {
        int l = 1;
        l += countNodes(r->left);
        l += countNodes(r->right);
        return l;
    }
}

template<class T>
Node<T>* binaryTree<T>::FindMin(Node<T>* leaf)
{
	while(leaf->left != NULL) leaf = leaf->left;
	return leaf;
}

template<class T>
Node<T>* binaryTree<T>::deleteVal(Node<T> *leaf, T data)
{
	if(leaf == NULL) return leaf;
	else if(data < leaf->value) leaf->left = deleteVal(leaf->left, data);
	else if (data > leaf->value) leaf->right = deleteVal(leaf->right, data);
	// element to delete found
	else {
		// Case 1: No child
		if(leaf->left == NULL && leaf->right == NULL)
		{
			delete leaf;
			leaf = NULL;
		}
		//Case 2: One child
		else if(leaf->left == NULL)
		{
			Node<T> *temp = leaf;
			leaf = leaf->right;
			delete temp;
		}
		else if(leaf->right == NULL)
		{
			Node<T> *temp = leaf;
			leaf = leaf->left;
			delete temp;
		}
		// case 3: 2 children
		else
		{
			Node<T> *temp = FindMin(leaf->right);
			leaf->value = temp->value;
			leaf->right = deleteVal(leaf->right, temp->value);
		}
	}
	return leaf;
}

template<class T>
void binaryTree<T>::removeVal(T data)
{
    while(searchTree(data) == 1)
    {
        root = deleteVal(root, data);
    }
}

#endif
