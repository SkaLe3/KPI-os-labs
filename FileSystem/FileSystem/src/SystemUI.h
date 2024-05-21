#pragma once
#include "Tree.h"
#include <string>
#include <functional>

class SystemUI
{
public:
	void DisplayMenu();
	void DisplayTree();
	void Exit();
	void Notify(const std::string& message);

	uint32_t RequestOption();
	void RequestData(NodeData& data);

private:
	void ReadCharacter(char& c, const std::function<bool(int)>& function);
};