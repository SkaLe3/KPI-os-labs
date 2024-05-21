#pragma once
#include <memory>


struct NodeData
{
	char Letter1;
	char Letter2;
	char Digit;

	bool operator<(const NodeData& other) const;
	bool operator>(const NodeData& other) const;

};

struct TreeNode
{
	std::shared_ptr<TreeNode> Left;
	std::shared_ptr<TreeNode> Right;
	NodeData Data;
	size_t Height;

	TreeNode() : Left(nullptr), Right(nullptr), Data({ 0, 0, 0 }), Height(1) {}
	TreeNode(NodeData data) : Left(nullptr), Right(nullptr), Data(data), Height(1) {}
};


class Tree
{
public:
	Tree() : m_Root(nullptr){}

	void Insert(NodeData data);
	void InOrder();


private:
	std::shared_ptr<TreeNode> Insert(std::shared_ptr<TreeNode> node, NodeData data);

	std::shared_ptr<TreeNode> RightRotate(std::shared_ptr<TreeNode> y);
	std::shared_ptr<TreeNode> LeftRotate(std::shared_ptr<TreeNode> x);

	uint32_t GetHeight(std::shared_ptr<TreeNode> node);
	int32_t GetBalance(std::shared_ptr<TreeNode> node);

	void UpdateHeight(std::shared_ptr<TreeNode> node);

	void InOrder(std::shared_ptr<TreeNode> node);


private:
	std::shared_ptr<TreeNode> m_Root;
};