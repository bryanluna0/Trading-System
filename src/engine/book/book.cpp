/*
	book.cpp file used for the book

*/

#include <algorithm>    

#include "book.h"

OrderBook::OrderBook(SymbolId s) noexcept : symbol(s)
{
	// TODO: be aware that this does not set a hard limit but addOrder does
	orders.reserve(MAX_ORDERS);
}

SymbolId OrderBook::getSymbol() const noexcept
{
	return symbol;
}

// TODO: limit number of orders, dont add order if order already in bool
void OrderBook::addOrder(const Order& order) 
{
	if (orders.size() >= MAX_ORDERS)
	{
		return;
	}

	// add order to orders unordered_map
	orders.emplace(order.order_id, order);


	if (order.side == Side::SELL)
	{
		if (!asks.contains(order.price))
		{
			asks[order.price] = std::make_unique<PriceLevel>(order.price);
		}
		
		// add order to PriceLevel deque
		(asks[order.price])->orders.push_back(&orders[order.order_id]);
	}
	else
	{
		if (!bids.contains(order.price))
		{
			bids[order.price] = std::make_unique<PriceLevel>(order.price);
		}

		// add order to PriceLevel deque
		(bids[order.price])->orders.push_back(&orders[order.order_id]);
	}
}

void OrderBook::cancelOrder(const OrderId order_id) 
{
	// TODO: return error codes
	if (!orders.contains(order_id))
	{
		return;
	}
	
	Order* order = &(orders[order_id]);
	// TODO: ensure that if orders has an order, so does the pricelevel 
	// 		 might have desync between maps maybs 
	// TODO: ensure we access element and do not add to map
	// access deque of orders based on side
	auto price_orders = (order->side == Side::SELL) ? &asks[order->price]->orders : &bids[order->price]->orders;
	
	// TODO: optimize order serach: currently O(n) 
	// serach through deque for order
	auto it = std::find_if(price_orders->begin(), price_orders->end(), [&](Order* price_order){ return price_order->order_id == order_id; });
	if (it != price_orders->end())
	{
		price_orders->erase(it);
	}
	
	if ((price_orders)->empty())
	{
		// remove PriceLevel if there is no orders at that price 
		(order->side == Side::SELL) ? asks.erase(asks.find(order->price)) : bids.erase(bids.find(order->price));
	}
	orders.erase(orders.find(order_id));

}

// TODO: add different behavior increasing vs decerasing quantity
void OrderBook::modifyQuantity(const OrderId order_id, const int64_t new_quantity)
{
	if (!orders.contains(order_id))
	{
		return;
	}

	if (new_quantity <= 0)
	{
		return;
	}

	orders[order_id].quantity = new_quantity;

}