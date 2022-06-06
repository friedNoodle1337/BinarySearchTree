#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP

#include <iostream>
#include <queue>
#include <stack>

template < class T >
class BinarySearchTree
{
public:
	BinarySearchTree();
	BinarySearchTree(const BinarySearchTree< T >& other) = delete;
	BinarySearchTree(BinarySearchTree< T >&& other) noexcept;
	virtual ~BinarySearchTree();

	BinarySearchTree& operator=(const BinarySearchTree< T >& other) = delete;
	BinarySearchTree& operator=(BinarySearchTree< T >&& other) noexcept;

	bool iterativeSearch(const T& key) const;
	bool insert(const T& key);
	bool deleteKey(const T& key);
	void print(std::ostream& out = std::cout) const;
	int getCount() const;
	int getHeight() const;
	void iterativeInorderWalk() const;
	void inorderWalk() const;

private:
	struct Node
	{
		T key_;
		Node* left_;
		Node* right_;
		Node* p_;

		Node(T key, Node* left = nullptr, Node* right = nullptr, Node* p = nullptr):
			key_(key), left_(left), right_(right), p_(p) {}
	};

	Node* root_;

	Node* iterariveSearchNode(const T& key) const
	{
		Node* current = root_;

		while (current != nullptr && current->key_ != key)
		{
			if (key > current->key_)
			{
				current = current->right_;
			}
			else
			{
				current = current->left_;
			}
		}

		return current;
	}

	bool insertNode(Node* newNode)
	{
		if (newNode == nullptr)
		{
			return false;
		}

		if (root_ == nullptr)
		{
			root_ = newNode;

			return true;
		}

		Node* current = root_;

		while (true)
		{
			if (newNode->key_ == current->key_)
			{
				return false;
			}
			else if (newNode->key_ < current->key_)
			{
				if (current->left_ == nullptr)
				{
					current->left_ = newNode;
					newNode->p_ = current;

					return true;
				}
				current = current->left_;
			}
			else if (newNode->key_ > current->key_)
			{
				if (current->right_ == nullptr)
				{
					current->right_ = newNode;
					newNode->p_ = current;

					return true;
				}
				current = current->right_;
			}
		}
	}

	bool deleteNode(const T& key)
	{
		Node* current = iterariveSearchNode(key);
		Node* parentOfCurrent = current->p_;

		if (current == nullptr)
		{
			return false;
		}

		if (current->left_ == nullptr && current->right_ == nullptr)
		{
			if (parentOfCurrent->left_ == current)
			{
				parentOfCurrent->left_ = nullptr;
			}
			else
			{
				parentOfCurrent->right_ = nullptr;
			}
			delete current;

			return true;
		}
		else if (current->left_ != nullptr && current->right_ != nullptr)
		{
			Node* min = current->right_;
			bool check = false;
			while (min->left_ != nullptr)
			{
				min = min->left_;
				check = true;
			}
			current->key_ = min->key_;
			min->right_->p_ = min->p_;
			if (check == true)
			{
				min->p_->left_ = min->right_;
			}
			else
			{
				min->p_->right_ = min->right_;
			}
			delete min;

			return true;
		}
		else if (current->left_ == nullptr)
		{
			current->right_->p_ = parentOfCurrent;
			if (parentOfCurrent->left_ == current)
			{
				parentOfCurrent->left_ = current->right_;
			}
			else
			{
				parentOfCurrent->right_ = current->right_;
			}
			delete current;

			return true;
		}
		else
		{
			current->left_->p_ = parentOfCurrent;
			if (parentOfCurrent->left_ == current)
			{
				parentOfCurrent->left_ = current->left_;
			}
			else
			{
				parentOfCurrent->right_ = current->left_;
			}
			delete current;

			return true;
		}


		//It is another method downstairs
		//else if (current->left_ != nullptr)
		//{
		//	Node* leftNode = current->left_;

		//	current->key_ = leftNode->key_;
		//	current->left_ = leftNode->left_;
		//	if (leftNode->right_ != nullptr && current->right_ != nullptr)
		//	{
		//		Node* temp = current->right_;
		//		current->right_ = leftNode->right_;
		//		insertNode(temp);
		//	}
		//	else if (leftNode->right_ != nullptr && current->right_ == nullptr)
		//	{
		//		current->right_ = leftNode->right_;
		//	}
		//	delete leftNode;

		//	return true;
		//}
		//else
		//{
		//	Node* rightNode = current->right_;

		//	current->key_ = rightNode->key_;
		//	current->right_ = rightNode->right_;
		//	if (rightNode->left_ != nullptr)
		//	{
		//		current->left_ = rightNode->left_;
		//	}
		//	delete rightNode;

		//	return true;
		//}
	}

	void printTree(std::ostream& out) const
	{
		std::queue< Node* > nodes;
		if (root_->left_ != nullptr)
		{
			nodes.push(root_->left_);
		}
		if (root_->right_ != nullptr)
		{
			nodes.push(root_->right_);
		}

		if (root_ != nullptr)
		{
			Node* current = nullptr;
			Node* next = root_;
			while (nodes.empty() == false)
			{
				current = next;
				next = nodes.front();
				nodes.pop();
				out << current->key_;
				bool check = false;
				if (next->key_ < current->key_ || next == current->right_)
				{
					out << "\n";
					check = true;
				}
				if (check == false)
				{
					out << " ";
				}
				if (next->left_ != nullptr)
				{
					nodes.push(next->left_);
				}
				if (next->right_ != nullptr)
				{
					nodes.push(next->right_);
				}
			}
			out << next->key_ << "\n";
		}
	}

	int getCount(Node* node) const
	{
		if (node == nullptr)
		{
			return 0;
		}

		return 1 + getCount(node->right_) + getCount(node->left_);
	}

	int getHeight(Node* node) const
	{
		if (node == nullptr)
		{
			return 0;
		}

		int left = getHeight(node->left_);
		int right = getHeight(node->right_);
		if (left > right)
		{
			return left + 1;
		}
		else
		{
			return right + 1;
		}
	}

	void iterativeInorderWalk(Node* node) const
	{
		std::stack< Node* > nodes;
		Node* current = node;
		bool check = false;
		while (current != nullptr || nodes.empty() == false)
		{
			if (!nodes.empty())
			{
				current = nodes.top();
				nodes.pop();
				if (check == false)
				{
					std::cout << current->key_;
					check = true;
				}
				else
				{
					std::cout << " " << current->key_;
				}
				if (current->right_ != nullptr)
				{
					current = current->right_;
				}
				else
				{
					current = nullptr;
				}
			}
			while (current != nullptr)
			{
				nodes.push(current);
				current = current->left_;
			}
		}
	}

	void inorderWalk(Node* node) const
	{
		if (node != nullptr)
		{
			inorderWalk(node->left_);
			std::cout << node->key_ << " ";
			inorderWalk(node->right_);
		}
	}
};

template < class T >
BinarySearchTree< T >::BinarySearchTree():
	root_(nullptr)
{}

template < class T >
BinarySearchTree< T >::BinarySearchTree(BinarySearchTree&& other) noexcept:
	root_(other.root_)
{
	other.root_ = nullptr;
}

template < class T >
BinarySearchTree< T >::~BinarySearchTree()
{
	Node* current = nullptr;
	Node* next = root_;

	while (next != nullptr)
	{
		if (next->left_ != nullptr)
		{
			current = next;
			next = next->left_;
		}
		else if (next->right_ != nullptr)
		{
			current = next;
			next = next->right_;
		}
		else
		{
			if (current != nullptr && current->right_ == next)
			{
				current->right_ = nullptr;
			}
			else if (current != nullptr)
			{
				current->left_ = nullptr;
			}
			delete next;
			next = current;
			if (current != nullptr)
			{
				current = current->p_;
			}
		}
	}
	root_ = nullptr;
}

template < class T >
BinarySearchTree< T >& BinarySearchTree< T >::operator=(BinarySearchTree&& other) noexcept
{
	if (this != &other)
	{
		std::swap(root_, other.root_);
	}

	return *this;
}

template < class T >
bool BinarySearchTree< T >::iterativeSearch(const T& key) const
{
	return iterariveSearchNode(key) != nullptr;
}

template < class T >
bool BinarySearchTree< T >::insert(const T& key)
{
	return insertNode(new Node(key));
}

template < class T >
bool BinarySearchTree< T >::deleteKey(const T& key)
{
	return deleteNode(key);
}

template < class T >
void BinarySearchTree< T >::print(std::ostream& out) const
{
	printTree(out);
}

template < class T >
int BinarySearchTree< T >::getCount() const
{
	return getCount(root_);
}

template < class T >
int BinarySearchTree< T >::getHeight() const
{
	return getHeight(root_);
}

template < class T >
void BinarySearchTree< T >::iterativeInorderWalk() const
{
	iterativeInorderWalk(root_);
	std::cout << "\n";
}

template < class T >
void BinarySearchTree< T >::inorderWalk() const
{
	inorderWalk(root_);
	std::cout << "\n";
}

#endif
