/* 
	order.cpp file used for orders

*/

#include "order.h"

std::atomic<uint64_t> Order::next_id = 0;

Order::Order(SymbolId symbol_id, int64_t price, int64_t quantity, OrderType order_type, Side side) : 
		symbol_id(symbol_id)
		,order_id(OrderId(next_id.fetch_add(1)))
		,price(price)
		,quantity(quantity)
		// get time stamp in ns
		,timestamp((std::chrono::nanoseconds(std::chrono::steady_clock::now().time_since_epoch())).count())
		,order_type(order_type), side(side) 
{}

std::optional<Order> Order::createOrder(SymbolId symbol_id, int64_t price, int64_t quantity, OrderType order_type, Side side)
{
	// TODO: check that symbol id is valid
	// TODO: return error code based on error
	if (price <= 0 || quantity <= 0)
	{
		return {};
	}

	return Order(symbol_id, price, quantity, order_type, side);
}

int64_t Order::getPrice() const
{
	return price;
}

int64_t Order::getQuantity() const
{
	return quantity;
}