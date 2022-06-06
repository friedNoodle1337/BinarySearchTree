#include "BinarySearchTree.hpp"

int main()
{
	BinarySearchTree< int > tree;
	BinarySearchTree< int > tree3;

	std::cout << "Inserting... ";
	tree.insert(10);
	tree.insert(5);
	tree.insert(8);
	tree.insert(6);
	BinarySearchTree< int > tree2(std::move(tree));
	tree2.insert(7);
	tree2.insert(2);
	tree2.insert(12);
	tree3 = std::move(tree2);
	tree3.insert(11);
	tree3.insert(0);
	tree3.insert(1);
	std::cout << "Completed!\n";

  std::cout << "\nPrint tree: \n";
	tree3.print(std::cout);

	std::cout << "\nThere are " << tree3.getCount() << " keys\n";
	std::cout << "Its height is " << tree3.getHeight() << "\n";

	std::cout << "\nIterative Inorder Walk: \n";
	tree3.iterativeInorderWalk();

	std::cout << "\nInorder walk: \n";
	tree3.inorderWalk();

	std::cout << "\nBreadth walk: \n";
	tree3.breadthWalk();

	std::cout << "\nDeleting keys... (Output using inorder walk)\nDeleting key \"2\"\n";
	tree3.deleteKey(2);
	tree3.inorderWalk();
	std::cout << "Deleting key \"5\"\n";
	tree3.deleteKey(5);
	tree3.inorderWalk();
	std::cout << "Deleting key \"12\"\n";
	tree3.deleteKey(12);
	tree3.inorderWalk();
	std::cout << "\nDeleting completed!\n";

	std::cout << "\nIterative Inorder Walk again: \n";
	tree3.iterativeInorderWalk();

	std::cout << "\nPrint tree again: \n";
	tree3.print(std::cout);

	std::cout << "\nThere are " << tree3.getCount() << " keys\n";
	std::cout << "Its height is " << tree3.getHeight() << "\n";

	std::cout << "\nBreadth walk again: \n";
	tree3.breadthWalk();

	BinarySearchTree< int > tree4;
	tree4.insert(10);
	tree4.insert(6);
	tree4.insert(11);
	tree4.insert(0);
	tree4.insert(8);
	tree4.insert(1);
	tree4.insert(7);
	std::cout << "\nAnother tree: \n";
	tree4.print();

	std::cout << "\nAre trees similar?\n";
	if (tree4.isSimilarTree(tree3) == true)
	{
		std::cout << "Yes\n";
	}
	else
	{
		std::cout << "No\n";
	}

	std::cout << "\nDo they have similar keys?\n";
	if (tree4.isSimilarKeys(tree3) == true)
	{
		std::cout << "Yes\n";
	}
	else
	{
		std::cout << "No\n";
	}

	std::cout << "\nEverything is working good!\n";
	
	return 0;
}
