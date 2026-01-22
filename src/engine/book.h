/*
	book.h file for the orderbook specification
*/

#include <deque>
#include <functional>
#include <map>
#include <memory>
#include "order.h"

struct PriceLevel
{
	int64_t price;
	std::deque<Order*> orders;	
};

stuct SymbolId
{
	uint64_t value;

	explicit SymbolId(uint64_t v) noexcept : value(v) {}

	bool operator==(const SymbolId& other) const
	{
		return this.value == other.value;
	}
	
	bool operator!=(const SymbolId& other) const
	{
		return this.value != other.value;
	}
};

class OrderBook
{
	private:
		SymbolId symbol;
		std::map<int64_t price, std::unique_ptr<PriceLevel>, std::greater<>> bids;
		std::map<int64_t price, std::unique_ptr<PriceLevel>, std::less<>> asks;

	public:
		explicit OrderBook(SymbolId s) noexcept;

		SymbolId getSymbol() const;
};
