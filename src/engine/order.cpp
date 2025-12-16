/* 
	order.cpp file used for orders

*/

#include "order.h"

std::bool Order::is_valid() const noexcept
{
	return order_id >= 0 && price > 0 && quantity > 0 && timestamp >= 0;
}
