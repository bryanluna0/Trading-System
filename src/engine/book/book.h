/*
	book.h file for the orderbook specification
*/

#ifndef BOOK_H
#define BOOK_H

#include <deque>
#include <functional>
#include <map>
#include <memory>

#include "../types/types.h"
#include "order.h"

// stores a deque of orders at a given price point
struct PriceLevel
{
	int64_t price;
	std::deque<Order*> orders;	
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