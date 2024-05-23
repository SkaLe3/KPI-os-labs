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

	if (balance > 1 && data < node->Left->Data)
		return RightRotate(node);
	if (balance < -1 && data > node->Right->Data)
		return LeftRotate(node);
	if (balance > 1 && data > node->Left->Data)
	{
		node->Left = LeftRotate(node->Left);
		return RightRotate(node);
	}
	if (balance < -1 && data < node->Right->Data)
	{
		node->Right = RightRotate(node->Right);
		return LeftRotate(node);
	}
	return node;
}

std::shared_ptr<TreeNode> Tree::DeleteNode(std::shared_ptr<TreeNode> node, NodeData data)
{
	if (node == nullptr)
		return node;

	if (data < node->Data)
		node->Left = DeleteNode(node->Left, data);
	else if (data > node->Data)
		node->Right = DeleteNode(node->Right, data);
	else
	{
		if (node->Left == nullptr || node->Right == nullptr)
		{
			std::shared_ptr<TreeNode> temp = node->Left ? node->Left : node->Right;

			if (temp == nullptr)
			{
				temp = node;
				node = nullptr;
			}
			else
				*node = *temp;
		}
		else
		{
			std::shared_ptr<TreeNode> temp = MinValueNode(node->Right);
			node->Data = temp->Data;
			node->Right = DeleteNode(node->Right, temp->Data);
		}
	}
	if (node == nullptr)
		return node;

	UpdateHeight(node);

	int32_t balance = GetBalance(node);

	if (balance > 1 && GetBalance(node->Left) >= 0)
		return RightRotate(node);
	if (balance > 1 && GetBalance(node->Left) < 0)
	{
		node->Left = LeftRotate(node->Left);
		return RightRotate(node);
	}
	if (balance < -1 && GetBalance(node->Right) <= 0)
		return LeftRotate(node);
	if (balance < -1 && GetBalance(node->Right) > 0)
	{
		node->Right = RightRotate(node->Right);
		return LeftRotate(node);
	}
	return node;
}

void Tree::Remove(NodeData data)
{
	m_Root = DeleteNode(m_Root, data);
}

SearchResult Tree::Search(NodeData data)
{
	SearchResult result({ 0, 0, 0 }, -1);
	int32_t depth = 0;
	std::shared_ptr<TreeNode> current = m_Root;
	while (current != nullptr)
	{
		if (data == current->Data)
		{
			result.Data = data;
			result.Depth = depth;
			return result;
		}
		else if (data < current->Data)
		{
			current = current->Left;
			depth++;
		}
		else
		{
			current = current->Right;
			depth++;
		}
	}
	return result;
}

void Tree::InOrder()
{
	InOrder(m_Root);
	std::cout << "\n";
}

void Tree::InOrder(std::shared_ptr<TreeNode> node, std::string indent, bool last)
{
	if (node == m_Root)
	{
		std::cout << "Tree:\n";
	}
	if (node != nullptr)
	{
		std::cout << indent;
		if (node == m_Root)
		{
			indent += "      ";
		}
		else if (last)
		{
			std::cout << "R----";
			indent += "      ";
		}
		else
		{
			std::cout << "L----";
			indent += "|     ";
		}
		std::cout << " [" << node->Data << "]" << "\n";
		InOrder(node->Left, indent, false);
		InOrder(node->Right, indent, true);
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


std::shared_ptr<TreeNode> Tree::MinValueNode(std::shared_ptr<TreeNode> node)
{
	std::shared_ptr<TreeNode> current = node;
	while (current->Left != nullptr)
		current = current->Left;
	return current;
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
	if (C1 < other.C1)
		return true;
	else if (C1 > other.C1)
		return false;
	else if (C2 < other.C2)
		return true;
	else if (C2 > other.C2)
		return false;
	else if (C3 < other.C3)
		return true;
	else if (C3 > other.C3)
		return false;
	else
		return false;
}

bool NodeData::operator>(const NodeData& other) const
{
	if (C1 > other.C1)
		return true;
	else if (C1 < other.C1)
		return false;
	else if (C2 > other.C2)
		return true;
	else if (C2 < other.C2)
		return false;
	else if (C3 > other.C3)
		return true;
	else if (C3 < other.C3)
		return false;
	else
		return false;
}

bool NodeData::operator==(const NodeData& other) const
{
	return C1 == other.C1 && C2 == other.C2 && C3 == other.C3;
}

std::ostream& operator<<(std::ostream& os, const NodeData& obj)
{
	os << obj.C1 << obj.C2 << obj.C3;
	return os;
}
