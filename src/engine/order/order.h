/* 
	order.h file used for order specifications

*/

#ifndef ORDER_H
#define ORDER_H

#include <atomic>
#include <chrono>
#include <optional>
#include <string>

#include "types/types.h"

// TODO: ensure all variables are instantiated before they are used
class Order
{
	friend class OrderBook;
private:
	int64_t price;	
	int64_t quantity;

	static std::atomic<uint64_t	> next_id;
	
	Order(SymbolId symbol_id, int64_t price, int64_t quantity, OrderType order_type, Side side);
public:
	const SymbolId symbol_id;
	const OrderId order_id;
	const int64_t timestamp;
	const OrderType order_type;
	const Side side;

	static std::optional<Order> createOrder(SymbolId symbol_id, int64_t price, int64_t quantity, OrderType order_type, Side side);
};

#endif // ORDER_H