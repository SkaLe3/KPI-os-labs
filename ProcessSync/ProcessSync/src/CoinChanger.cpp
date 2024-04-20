#include "CoinChanger.h"
#include "Log.h"

#include <iostream>
#include <string>
#include <random>
#include <conio.h>
#include <thread>



void CoinChanger::FillCoins(CoinsStack cs)
{
	for (size_t i = 0; i < cs.c1k; i++)
		stack1k.push_back(std::make_unique<Coin>(ECoinDenom::_1k));
	for (size_t i = 0; i < cs.c2k; i++)
		stack2k.push_back(std::make_unique<Coin>(ECoinDenom::_2k));
	for (size_t i = 0; i < cs.c5k; i++)
		stack5k.push_back(std::make_unique<Coin>(ECoinDenom::_5k));
	for (size_t i = 0; i < cs.c10k; i++)
		stack10k.push_back(std::make_unique<Coin>(ECoinDenom::_10k));
	for (size_t i = 0; i < cs.c25k; i++)
		stack25k.push_back(std::make_unique<Coin>(ECoinDenom::_25k));
	for (size_t i = 0; i < cs.c50k; i++)
		stack50k.push_back(std::make_unique<Coin>(ECoinDenom::_50k));
	for (size_t i = 0; i < cs.c1h; i++)
		stack1h.push_back(std::make_unique<Coin>(ECoinDenom::_1h));
}

void CoinChanger::Start()
{
	LOG_TRACE("Coin changer started");


	std::thread accepter(&CoinChanger::AcceptCoins, this);
	std::thread changer(&CoinChanger::GiveChange, this);

	accepter.join();
	changer.join();

}

std::unique_ptr<Coin> CoinChanger::AskForCoin()
{
	std::unique_ptr<Coin> newCoin;

	std::cout << "\nPress Enter to insert a coin...\n";
	getch();

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<uint16_t> distribution(0, 6);
	uint16_t coinDenom = distribution(gen);

	switch (coinDenom)
	{
	case 0:
		return std::make_unique<Coin>(ECoinDenom::_1k);
	case 1:
		return std::make_unique<Coin>(ECoinDenom::_2k);
	case 2:
		return std::make_unique<Coin>(ECoinDenom::_5k);
	case 3:
		return std::make_unique<Coin>(ECoinDenom::_10k);
	case 4:
		return std::make_unique<Coin>(ECoinDenom::_25k);
	case 5:
		return std::make_unique<Coin>(ECoinDenom::_50k);
	case 6:
		return std::make_unique<Coin>(ECoinDenom::_1h);
	default:
		LOG_ERROR("Unknown coin!");
	}

	return nullptr;
}

Coin CoinChanger::GetRequest(const std::string& denom)
{
	LOG_TRACE("You inserted a", denom, "coin");
	while (true)
	{
		std::cout << "\nPlease select a desired denomination!\nDenominations: [ 1k | 2k | 5k | 10k | 25k | 50k | 1h ]\n";
		std::cout << "Answer: ";

		std::string coinDenom;
		std::cin >> coinDenom;
		std::cout << "\n";

		if (coinDenom == "1k")
			return Coin(ECoinDenom::_1k);
		else if (coinDenom == "2k")
			return Coin(ECoinDenom::_2k);
		else if (coinDenom == "5k")
			return Coin(ECoinDenom::_5k);
		else if (coinDenom == "10k")
			return Coin(ECoinDenom::_10k);
		else if (coinDenom == "25k")
			return Coin(ECoinDenom::_25k);
		else   if (coinDenom == "50k")
			return Coin(ECoinDenom::_50k);
		else	if (coinDenom == "1h")
			return Coin(ECoinDenom::_1h);
		else
		{
			LOG_ERROR("Unknown coin!");
			continue;
		}
		break;
	}
}

void CoinChanger::InsertCoin(std::unique_ptr<Coin> coin)
{
	switch (coin->Denomination)
	{
	case ECoinDenom::_1k:
		stack1k.push_back(std::move(coin));
		break;
	case ECoinDenom::_2k:
		stack2k.push_back(std::move(coin));
		break;
	case ECoinDenom::_5k:
		stack5k.push_back(std::move(coin));
		break;
	case ECoinDenom::_10k:
		stack10k.push_back(std::move(coin));
		break;
	case ECoinDenom::_25k:
		stack25k.push_back(std::move(coin));
		break;
	case ECoinDenom::_50k:
		stack50k.push_back(std::move(coin));
		break;
	case ECoinDenom::_1h:
		stack1h.push_back(std::move(coin));
		break;
	default:
		LOG_ERROR("Can't insert coin");
		return;
	}
	LOG_TRACE("Coin accepted");
}

void CoinChanger::ExtractCoins(ECoinDenom denom, uint32_t quantity)
{
	switch (denom)
	{
	case ECoinDenom::_1k:
		for (int i = 0; i < quantity; ++i)
			stack1k.pop_back();
		break;
	case ECoinDenom::_2k:
		for (int i = 0; i < quantity; ++i)
			stack2k.pop_back();
		break;
	case ECoinDenom::_5k:
		for (int i = 0; i < quantity; ++i)
			stack5k.pop_back();
		break;
	case ECoinDenom::_10k:
		for (int i = 0; i < quantity; ++i)
			stack10k.pop_back();
		break;
	case ECoinDenom::_25k:
		for (int i = 0; i < quantity; ++i)
			stack25k.pop_back();
		break;
	case ECoinDenom::_50k:
		for (int i = 0; i < quantity; ++i)
			stack50k.pop_back();
		break;
	case ECoinDenom::_1h:
		for (int i = 0; i < quantity; ++i)
			stack1h.pop_back();
		break;
	}
}

bool CoinChanger::CheckExchangeAbility(uint32_t inserted, Coin requested)
{
	if (inserted % +requested.Denomination == 0)
	{
		uint32_t coinsCount = inserted / +requested.Denomination;
		if (CheckCoinsPresence(requested.Denomination, coinsCount))
			return true;
		else
		{
			LOG_STATE("Not enough coins in machine");
			return false;

		}
	}
	LOG_STATE("Not possible to exchange the inserted coin for coins of the selected denomination");
	return false;
}

bool CoinChanger::CheckCoinsPresence(ECoinDenom denom, uint32_t quantity)
{
	switch (denom)
	{
	case ECoinDenom::_1k:
		return stack1k.size() >= quantity;
	case ECoinDenom::_2k:
		return stack2k.size() >= quantity;
	case ECoinDenom::_5k:
		return stack5k.size() >= quantity;
	case ECoinDenom::_10k:
		return stack10k.size() >= quantity;
	case ECoinDenom::_25k:
		return stack25k.size() >= quantity;
	case ECoinDenom::_50k:
		return stack50k.size() >= quantity;
	case ECoinDenom::_1h:
		return stack1h.size() >= quantity;
	}
	return false;
}

uint32_t CoinChanger::GetCoinsQuantity(uint32_t inserted, Coin requested)
{
	return inserted / +requested.Denomination;
}

void CoinChanger::ShowAvailableCoins()
{
	std::cout << "Coins Available:\n";
	std::cout << "1k: " << stack1k.size() << "\n";
	std::cout << "2k: " << stack2k.size() << "\n";
	std::cout << "5k: " << stack5k.size() << "\n";
	std::cout << "10k: " << stack10k.size() << "\n";
	std::cout << "25k: " << stack25k.size() << "\n";
	std::cout << "50k: " << stack50k.size() << "\n";
	std::cout << "1h: " << stack1h.size() << "\n\n";
}

void CoinChanger::AcceptCoins()
{	
	while (true)
	{
		tasLock.lock();

		ShowAvailableCoins();
		newCoin = AskForCoin();
		requestedCoin = GetRequest((std::string)(*newCoin));

		tasLock.unlock();
	}
}

void CoinChanger::GiveChange()
{
	while (true)
	{
		tasLock.lock();

		if (CheckExchangeAbility(+newCoin->Denomination, requestedCoin))
		{
			uint32_t coins = GetCoinsQuantity(+newCoin->Denomination, requestedCoin);
			InsertCoin(std::move(newCoin));
			ExtractCoins(requestedCoin.Denomination, coins);

			LOG_TRACE("Exchange completed. You get", coins, (std::string)requestedCoin, "coins");
		}
		else
			LOG_ERROR("Exchange refused");   

		tasLock.unlock();

	}
}


