#pragma once
#include "Tree.h"
#include <string>
#include <functional>

class SystemUI
{
public:
	void DisplayMenu();
	void DisplayTree(Tree& tree);
	void DisplaySearchResult(SearchResult res);
	void Exit();
	void Notify(const std::string& message);

	uint32_t RequestOption();
	bool RequestData(NodeData& data);

private:
	bool ReadCharacter(char& c, uint32_t& lets, uint32_t& digs);
};