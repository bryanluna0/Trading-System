/* 
	order.cpp file used for orders

*/

#include "order.h"

bool Order::is_valid() const noexcept
{
	return price > 0 && quantity > 0 && timestamp >= 0;
}
