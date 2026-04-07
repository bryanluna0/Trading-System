/* 
	order.cpp file used for orders

*/

#include "order.h"

bool Order::is_valid() const noexcept
{
	return order_id.value >= 0 && price > 0 && quantity > 0 && timestamp >= 0;
}
