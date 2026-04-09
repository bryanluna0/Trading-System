/*
	book.cpp file used for the book

*/

#include "book.h"

OrderBook::OrderBook(SymbolId s) noexcept : symbol(s)
{
	
}

SymbolId OrderBook::getSymbol() const noexcept
{
	return symbol;
}

void OrderBook::addOrder(Order& order) noexcept
{
	if(order.side == Side::SELL)
	{
		// asks.push_back(
	}
}
