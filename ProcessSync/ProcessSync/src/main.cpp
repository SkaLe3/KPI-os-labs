#include "CommandLineParser.h"
#include "CoinChanger.h"
#include "Log.h"


int main(int argc, char* argv[])
{
	try
	{
		Log::Init();

		CommandLineParser parser(argc, argv);
		parser.parse();

		CoinChanger coinChanger;
		coinChanger.FillCoins(parser.GetCoinsQuantity());
		coinChanger.Start();


	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
		return 1;
	}

	return 0;
}