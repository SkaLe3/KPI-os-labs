#include "Tree.h"
#include <iostream>


void Tree::Insert(NodeData data)
{
	m_Root = Insert(m_Root, data);
}

std::shared_ptr<TreeNode> Tree::Insert(std::shared_ptr<TreeNode> node, NodeData data)
{
	if (node == nullptr)
		return std::make_shared<TreeNode>(data);

	if (data < node->Data)
		node->Left = Insert(node->Left, data);
	else if (data > node->Data)
		node->Right = Insert(node->Right, data);
	else
	{
		std::cout << "ERROR: Identifiers collision\n";
		return node;
	}

	UpdateHeight(node);

	int32_t balance = GetBalance(node);

	if (balance > 1 && node->Data > node->Left->Data)
		return RightRotate(node);
	if (balance < -1 && node->Data < node->Right->Data)
		return LeftRotate(node);
	if (balance > 1 && node->Data < node->Left->Data)
	{
		node->Left = LeftRotate(node->Left);
		return RightRotate(node);
	}
	if (balance < -1 && node->Data > node->Right->Data)
	{
		node->Right = RightRotate(node->Right);
		return LeftRotate(node);
	}
	return node;
}

void Tree::InOrder()
{
	InOrder(m_Root);
	std::cout << "\n";
}

void Tree::InOrder(std::shared_ptr<TreeNode> node)
{
	if (node != nullptr)
	{
		InOrder(node->Left);
		std::cout << node->Data.Letter1 << "??" << "\n";
		InOrder(node->Right);
	}
}

std::shared_ptr<TreeNode> Tree::RightRotate(std::shared_ptr<TreeNode> y)
{
	std::shared_ptr<TreeNode> x = y->Left;
	std::shared_ptr<TreeNode> T2 = x->Right;

	x->Right = y;
	y->Left = T2;

	UpdateHeight(y);
	UpdateHeight(x);	
	return x;
}

std::shared_ptr<TreeNode> Tree::LeftRotate(std::shared_ptr<TreeNode> x)
{
	std::shared_ptr<TreeNode> y = x->Right;
	std::shared_ptr<TreeNode> T2 = y->Left;

	y->Left = x;
	x->Right = T2;

	UpdateHeight(x);
	UpdateHeight(y);
	return y;
}

uint32_t Tree::GetHeight(std::shared_ptr<TreeNode> node)
{
	return node ? node->Height : 0;
}

int32_t Tree::GetBalance(std::shared_ptr<TreeNode> node)
{
	return node ? GetHeight(node->Left) - GetHeight(node->Right) : 0;
}

void Tree::UpdateHeight(std::shared_ptr<TreeNode> node)
{
	node->Height = 1 + std::max(GetHeight(node->Left), GetHeight(node->Right));
}

bool NodeData::operator<(const NodeData& other) const
{
	if (Letter1 < other.Letter1)
		return true;
	else if (Letter1 > other.Letter1)
		return false;
	else if (Letter2 < other.Letter2)
		return true;
	else if (Letter2 > other.Letter2)
		return false;
	else if (Digit < other.Digit)
		return true;
	else if (Digit > other.Digit)
		return false;
	else
		return false;
}

bool NodeData::operator>(const NodeData& other) const
{
	if (Letter1 > other.Letter1)
		return true;
	else if (Letter1 < other.Letter1)
		return false;
	else if (Letter2 > other.Letter2)
		return true;
	else if (Letter2 < other.Letter2)
		return false;
	else if (Digit > other.Digit)
		return true;
	else if (Digit < other.Digit)
		return false;
	else
		return false;
}
