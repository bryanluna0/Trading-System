/*
	book.h file for the orderbook specification
*/

#pragma once
#ifndef BOOK_H
#define BOOK_H

#include <deque>
#include <functional>
#include <map>
#include <unordered_map>
#include <memory>

#include "types/types.h"
#include "engine/order/order.h"

const int64_t MAX_ORDERS = 100000;

// stores a deque of orders at a given price point
struct PriceLevel
{
	explicit PriceLevel(int64_t price) : price(price) {}
	int64_t price;
	std::deque<Order*> orders;	
};

class OrderBook
{
	private:
		SymbolId symbol;

		std::unordered_map<OrderId, Order> orders;
		
		// key price 
		std::map<int64_t, std::unique_ptr<PriceLevel>, std::greater<int64_t>> bids;
		std::map<int64_t, std::unique_ptr<PriceLevel>, std::less<int64_t>> asks;

	public:
		explicit OrderBook(SymbolId s) noexcept;

		SymbolId getSymbol() const noexcept;

		void addOrder(const Order& order);
		void cancelOrder(const OrderId order_id);
		void modifyQuantity(const OrderId OrderId, const int64_t new_quantity);
		void modifyPrice(const OrderId order_id, const int64_t new_price);
};

#endif // BOOK_H