#pragma once
#include "SystemUI.h"
#include "Tree.h"

class Controller
{
public:
	void Run();

private:
	SystemUI m_UI;
	Tree m_Tree;

};