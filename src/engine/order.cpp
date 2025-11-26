/* 
	order.cpp file used for orders


*/

#include <bool>
#include <cstdint>
#include <string>

// #define SELL 0
// #define BUY 1

enum side
{
	SELL,
	BUY
};

enum order_type
{
	LIMIT,
	MARKET,
	IOC,
	FOK
};

struct order
{
	std::string symbol;
	unint64_t order_id;
	int64_t price;	
	int64_t quantity;
	int64_t timestamp;	
	order_type order_type;
	side side;
}
