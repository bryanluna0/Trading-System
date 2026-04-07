/*
	book.h file for the orderbook specification
*/

#ifndef BOOK_H
#define BOOK_H

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

struct SymbolId
{
	uint64_t value;

	explicit SymbolId(uint64_t v) noexcept : value(v) {}

	bool operator==(const SymbolId& other) const noexcept
	{
		return value == other.value;
	}
	
	bool operator!=(const SymbolId& other) const noexcept
	{
		return value != other.value;
	}
};

class OrderBook
{
	private:
		SymbolId symbol;
		std::map<int64_t, std::unique_ptr<PriceLevel>, std::greater<int64_t>> bids;
		std::map<int64_t, std::unique_ptr<PriceLevel>, std::less<int64_t>> asks;

	public:
		explicit OrderBook(SymbolId s) noexcept;

		SymbolId getSymbol() const noexcept;

		void addOrder(Order& order) noexcept;
};

#endif // BOOK_H