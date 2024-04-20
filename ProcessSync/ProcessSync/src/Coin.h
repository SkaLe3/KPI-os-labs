#pragma once
#include <string>


template <typename T>
constexpr auto operator+(T e) noexcept
-> std::enable_if_t<std::is_enum<T>::value, std::underlying_type_t<T>>
{
	return static_cast<std::underlying_type_t<T>>(e);
}

enum class ECoinDenom : uint8_t
{
	_1k = 1, _2k = 2, _5k = 5, _10k = 10, _25k = 25, _50k = 50, _1h = 100
};

struct Coin
{
	operator std::string() const
	{
		switch (Denomination)
		{
		case ECoinDenom::_1k:
			return "1k";
		case ECoinDenom::_2k:
			return "2k";
		case ECoinDenom::_5k:
			return "5k";
		case ECoinDenom::_10k:
			return "10k";
		case ECoinDenom::_25k:
			return "25k";
		case ECoinDenom::_50k:
			return "50k";
		case ECoinDenom::_1h:
			return "1h";
		default:
			return "";
		}
	}

	ECoinDenom Denomination;
};


struct CoinsStack
{
	uint32_t c1k = 50;
	uint32_t c2k = 50;
	uint32_t c5k = 50;
	uint32_t c10k = 50;
	uint32_t c25k = 50;
	uint32_t c50k = 50;
	uint32_t c1h = 50;
};