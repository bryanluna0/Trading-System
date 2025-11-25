/* 
	order.cpp file used for orders


*/

#include <bool>
#include <string>
#define BUY 0
#define SELL 1

struct order
{
	unint64 order_id;
	std::string symbol;
	std::bool side;
	int64 ticks price;	
}

