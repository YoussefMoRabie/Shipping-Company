#pragma once
template<class Type>
class TreeNode
{
private:
	Type item;
	TreeNode<Type>* Left;
	TreeNode<Type>* Right;
public:
	TreeNode()
	{
		Left = nullptr;
		Right = nullptr;
	}
	TreeNode(const Type anitem)
	{
		item = anitem;
		Left = nullptr;
		Right = nullptr;
	}
	TreeNode(const Type anitem, TreeNode<Type>* l, TreeNode<Type>* r)
	{
		item = anitem;
		Left = l;
		Right = r;
	}
	
	void set_item(const Type anitem)
	{
		item = anitem;
	}
	void set_left(TreeNode<Type>* l)
	{
		Left = l;
	}
	void set_right(TreeNode<Type>* r)
	{
		Right = r;
	}


	Type get_item()const { return item; }
	TreeNode<Type>* get_left()const { return Left; }
	TreeNode<Type>* get_right()const { return Right; }
	

};
