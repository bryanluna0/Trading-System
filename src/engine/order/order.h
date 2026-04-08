/* 
	order.h file used for order specifications

*/

#ifndef ORDER_H
#define ORDER_H

#include <string>

#include "../types/types.h"

struct Order
{
	OrderId order_id;
	int64_t price;	
	int64_t quantity;
	int64_t timestamp;	
	OrderType order_type;
	Side side;

	bool is_valid() const noexcept;
};

#endif // ORDER_H