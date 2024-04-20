#pragma once
#include <vector>
#include <memory>

#include "Coin.h"
#include "TestAndSetLock.h"


class CoinChanger
{
public:
	void FillCoins(CoinsStack cs);

	void Start();
	std::unique_ptr<Coin> AskForCoin();
	Coin GetRequest(const std::string& denom);
	void InsertCoin(std::unique_ptr<Coin> coin);
	void ExtractCoins();
	bool CheckExchangeAbility(uint32_t inserted, Coin requested);
	bool CheckCoinsPresence(ECoinDenom denom, uint32_t quantity );
	uint32_t GetAvailableCoins(ECoinDenom denom, uint32_t quantity);

	uint32_t GetCoinsQuantity(uint32_t inserted, Coin requested);

	void ShowAvailableCoins();

	void AcceptCoins();
	void GiveChange();

private:
	std::vector<std::unique_ptr<Coin>> stack1k;
	std::vector<std::unique_ptr<Coin>> stack2k;
	std::vector<std::unique_ptr<Coin>> stack5k;
	std::vector<std::unique_ptr<Coin>> stack10k;
	std::vector<std::unique_ptr<Coin>> stack25k;
	std::vector<std::unique_ptr<Coin>> stack50k;
	std::vector<std::unique_ptr<Coin>> stack1h;

	std::unique_ptr<Coin> newCoin;
	Coin requestedCoin;
	std::vector<std::pair<uint32_t, Coin>> change;

	TestAndSetLock tasLock;
};