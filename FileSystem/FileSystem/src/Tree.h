#pragma once
#include <memory>
#include <string>


struct NodeData
{
	char C1;
	char C2;
	char C3;

	bool operator<(const NodeData& other) const;
	bool operator>(const NodeData& other) const;
	bool operator==(const NodeData& other) const;
};
std::ostream& operator<<(std::ostream& os, const NodeData& obj);

struct TreeNode
{
	std::shared_ptr<TreeNode> Left;
	std::shared_ptr<TreeNode> Right;
	NodeData Data;
	size_t Height;

	TreeNode() : Left(nullptr), Right(nullptr), Data({ 0, 0, 0 }), Height(1) {}
	TreeNode(NodeData data) : Left(nullptr), Right(nullptr), Data(data), Height(1) {}
};

struct SearchResult
{
	NodeData Data;
	size_t Depth;
};

class Tree
{
public:
	Tree() : m_Root(nullptr) {}

	void Insert(NodeData data);
	void Remove(NodeData data);
	SearchResult Search(NodeData data);
	void InOrder();


private:
	std::shared_ptr<TreeNode> Insert(std::shared_ptr<TreeNode> node, NodeData data);
	std::shared_ptr<TreeNode> DeleteNode(std::shared_ptr<TreeNode> node, NodeData data);

	std::shared_ptr<TreeNode> RightRotate(std::shared_ptr<TreeNode> y);
	std::shared_ptr<TreeNode> LeftRotate(std::shared_ptr<TreeNode> x);
	std::shared_ptr<TreeNode> MinValueNode(std::shared_ptr<TreeNode> node);

	uint32_t GetHeight(std::shared_ptr<TreeNode> node);
	int32_t GetBalance(std::shared_ptr<TreeNode> node);

	void UpdateHeight(std::shared_ptr<TreeNode> node);

	void InOrder(std::shared_ptr<TreeNode> node, std::string indent = "", bool last = true);


private:
	std::shared_ptr<TreeNode> m_Root;
};