/* 
	order.h file used for order specifications

*/

#include <bool>
#include <cstdint>
#include <string>

enum Side
{
	SELL,
	BUY
};

enum OrderType 
{
	LIMIT,
	MARKET,
	IOC,
	FOK
};

struct Order
{
	std::string symbol;
	unint64_t order_id;
	int64_t price;	
	int64_t quantity;
	int64_t timestamp;	
	OrderType order_type;
	Side side;

	std::bool is_valid() const noexcept;
};
