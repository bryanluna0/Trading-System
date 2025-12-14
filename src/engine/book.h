/*
	book.h file for the orderbook specification
*/

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

class OrderBook
{
	private:
		std::map<int64_t price, std::unique_ptr<PriceLevel>, std::greater<>> bids;
		std::map<int64_t price, std::unique_ptr<PriceLevel>, std::less<>> asks;

}

