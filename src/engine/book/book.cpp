/*
	book.cpp file used for the book

*/

#include "book.h"

OrderBook::OrderBook(SymbolId s) noexcept : symbol(s)
{
	orders.reserve(100000);
}

SymbolId OrderBook::getSymbol() const noexcept
{
	return symbol;
}

void OrderBook::addOrder(Order& order) 
{
	// add order to orders unordered_map
	orders[order.order_id] = order;

	if (order.side == Side::SELL)
	{
		if (!asks.contains(order.price))
		{
			asks[order.price] = std::make_unique<PriceLevel>(order.price);
		}
		(asks[order.price])->orders.push_back(&orders[order.order_id]);
	}
	else
	{
		if (!bids.contains(order.price))
		{
			bids[order.price] = std::make_unique<PriceLevel>(order.price);
		}
		(bids[order.price])->orders.push_back(&orders[order.order_id]);
	}
}
