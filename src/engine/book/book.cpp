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

OrderResult OrderBook::addOrder(const Order& order) 
{
	if (orders.contains(order.order_id))
	{
		return OrderResult::ORDER_ALREADY_EXISTS;
	}

	if (order.order_type != OrderType::LIMIT)
	{
		return OrderResult::INVALID_ORDER_TYPE;
	}

	if (orders.size() >= MAX_ORDERS)
	{
		return OrderResult::BOOK_FULL;
	}

	// add order to orders unordered_map
	orders.emplace(order.order_id, order);
	addToPriceLevel(&orders.at(order.order_id));
	return OrderResult::SUCCESS;
}

OrderResult OrderBook::cancelOrder(const OrderId order_id) 
{
	// TODO: return error codes
	if (!orders.contains(order_id))
	{
		return OrderResult::ORDER_NOT_FOUND;
	}
	
	Order* order = &(orders.at(order_id));
	// TODO: ensure that if orders has an order, so does the pricelevel 
	// 		 might have desync between maps maybs 
	// TODO: ensure we access element and do not add to map
	// access deque of orders based on side
	removeFromPriceLevel(order);
	orders.erase(order_id);

	return OrderResult::SUCCESS;
}

// TODO: add different behavior increasing vs decerasing quantity
OrderResult OrderBook::modifyQuantity(const OrderId order_id, const int64_t new_quantity)
{
	if (!orders.contains(order_id))
	{
		return OrderResult::ORDER_NOT_FOUND;
	}

	if (new_quantity <= 0)
	{
		return OrderResult::INVALID_QUANTITY;
	}

	orders.at(order_id).quantity = new_quantity;

	return OrderResult::SUCCESS;
}

OrderResult OrderBook::modifyPrice(const OrderId order_id, const int64_t new_price)
{
	if (!orders.contains(order_id))
	{
		return OrderResult::ORDER_NOT_FOUND;
	}

	if (new_price <= 0)
	{
		return OrderResult::INVALID_PRICE;
	}

	Order* order = &(orders.at(order_id));

	removeFromPriceLevel(order);
	order->price = new_price;
	addToPriceLevel(order);

	return OrderResult::SUCCESS;
}

// helpers

void OrderBook::removeFromPriceLevel(const Order* order)
{
	auto price_orders = (order->side == Side::SELL) ? &asks[order->price]->orders : &bids[order->price]->orders;
	// TODO: optimize order serach: currently O(n) 
	// serach through deque for order
	auto it = std::find_if(price_orders->begin(), price_orders->end(), [&](const Order* price_order){ return price_order->order_id == order->order_id; });
	if (it != price_orders->end())
	{
		price_orders->erase(it);
	}

	if ((price_orders)->empty())
	{
		// remove PriceLevel if there is no orders at that price 
		(order->side == Side::SELL) ? asks.erase(order->price) : bids.erase(order->price);
	}

}

void OrderBook::addToPriceLevel(const Order* order)
{
	if (order->side == Side::SELL)
	{
		if (!asks.contains(order->price))
		{
			asks[order->price] = std::make_unique<PriceLevel>(order->price);
		}
		asks[order->price]->orders.push_back(order);
	}
	else
	{
		if (!bids.contains(order->price))
		{
			bids[order->price] = std::make_unique<PriceLevel>(order->price);
		}
		bids[order->price]->orders.push_back(order);
	}
}

size_t OrderBook::getOrderCount() const noexcept
{
	return orders.size();
}

size_t OrderBook::getBidCount() const noexcept
{
	return bids.size();
}

size_t OrderBook::getAskCount() const noexcept
{
	return asks.size();
}

std::optional<const PriceLevel*> OrderBook::getBestBid() const
{
	// add error code based on error
	if (bids.size() < 1)
	{
		return {};
	}

	return &(*bids.begin()->second);
}

std::optional<const PriceLevel*> OrderBook::getBestAsk() const
{
	if (asks.size() < 1)
	{
		return {};
	}

	return &(*asks.begin()->second);
}