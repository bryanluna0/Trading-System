/*
	book.h file for the orderbook specification
*/

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
	std::deque<const Order*> orders;	
};

class OrderBook
{
	private:
		std::unordered_map<OrderId, Order> orders;
		
		// key price 
		// buy orders go here
		std::map<int64_t, std::unique_ptr<PriceLevel>, std::greater<int64_t>> bids;
		// sell orders go here
		std::map<int64_t, std::unique_ptr<PriceLevel>, std::less<int64_t>> asks;

		// helper functions
		void removeFromPriceLevel(const Order* order);
		void addToPriceLevel(const Order* order);

	public:
		const SymbolId symbol;

		explicit OrderBook(SymbolId s) noexcept;

		OrderResult addOrder(const Order& order);
		OrderResult cancelOrder(const OrderId order_id);
		OrderResult modifyQuantity(const OrderId order_id, const int64_t new_quantity);
		OrderResult modifyPrice(const OrderId order_id, const int64_t new_price);

		size_t getOrderCount() const noexcept;
		size_t getBidCount() const noexcept;
		size_t getAskCount() const noexcept;
 		std::optional<const PriceLevel*> getBestBid() const;
		std::optional<const PriceLevel*> getBestAsk() const;
};

#endif // BOOK_H