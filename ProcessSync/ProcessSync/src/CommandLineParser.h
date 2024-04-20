#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "Coin.h"

class CommandLineParser
{
public:
	CommandLineParser(int argc, char* argv[]) : argc(argc), argv(argv) {}

	bool parse()
	{
		for (int i = 1; i < argc; ++i)
		{
			std::string arg = argv[i];

			if (arg == "-c1k")
			{
				if (i + 1 < argc)
				{
					if (int32_t value = atoi(argv[++i]); value >= 0)
						coins.c1k = atoi(argv[i]);
					else
						throw std::invalid_argument("-c1k must be greater than 0");
				}
				else
				{
					throw std::invalid_argument("-c1k requires an argument");
				}
			}
			else if (arg == "-c2k")
			{
				if (i + 1 < argc)
				{
					if (int32_t value = atoi(argv[++i]); value >= 0)
						coins.c2k = atoi(argv[i]);
					else
						throw std::invalid_argument("-c2k must be greater than 0");
				}
				else
				{
					throw std::invalid_argument("-c2k requires an argument");
				}
			}
			else if (arg == "-c5k")
			{
				if (i + 1 < argc)
				{
					if (int32_t value = atoi(argv[++i]); value >= 0)
						coins.c5k = atoi(argv[i]);
					else
						throw std::invalid_argument("-c5k must be greater than 0");
				}
				else
				{
					throw std::invalid_argument("-c5k requires an argument");
				}
			}
			else if (arg == "-c10k")
			{
				if (i + 1 < argc)
				{
					if (int32_t value = atoi(argv[++i]); value >= 0)
						coins.c10k = atoi(argv[i]);
					else
						throw std::invalid_argument("-c10k must be greater than 0");
				}
				else
				{
					throw std::invalid_argument("-c10k requires an argument");
				}
			}
			else if (arg == "-c25k")
			{
				if (i + 1 < argc)
				{
					if (int32_t value = atoi(argv[++i]); value >= 0)
						coins.c25k = atoi(argv[i]);
					else
						throw std::invalid_argument("-c25k must be greater than 0");
				}
				else
				{
					throw std::invalid_argument("-c25k requires an argument");
				}
			}
			else if (arg == "-c50k")
			{
				if (i + 1 < argc)
				{
					if (int32_t value = atoi(argv[++i]); value >= 0)
						coins.c50k = atoi(argv[i]);
					else
						throw std::invalid_argument("-c50k must be greater than 0");
				}
				else
				{
					throw std::invalid_argument("-c50k requires an argument");
				}
			}
			else if (arg == "-c1h")
			{
				if (i + 1 < argc)
				{
					if (int32_t value = atoi(argv[++i]); value >= 0)
						coins.c1h = atoi(argv[i]);
					else
						throw std::invalid_argument("-c1h must be greater than 0");
				}
				else
				{
					throw std::invalid_argument("-c1h requires an argument");
				}
			}
			else
			{
				throw std::invalid_argument("Unknown option '" + arg + "'");
			}
		}
		return true;
	}

	CoinsStack GetCoinsQuantity() { return coins; }

private:
	int argc;
	char** argv;
	CoinsStack coins;
};