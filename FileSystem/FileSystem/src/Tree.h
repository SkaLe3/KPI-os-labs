#pragma once
#include <memory>


struct NodeData
{
	char Letter1;
	char Letter2;
	char Digit;
};

struct TreeNode
{
	std::shared_ptr<TreeNode> Left;
	std::shared_ptr<TreeNode> Right;
	NodeData Data;
	size_t Height;
};


class Tree
{
public:
	Tree() : m_Root(nullptr){}

	void Insert(NodeData data);

private:
	std::shared_ptr<TreeNode> m_Root;
};