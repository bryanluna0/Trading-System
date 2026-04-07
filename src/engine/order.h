/* 
	order.h file used for order specifications

*/

#ifndef ORDER_H
#define ORDER_H

#include <cstdint>
#include <string>

struct OrderId 
{
	uint64_t value;
	
	explicit constexpr OrderId(uint64_t v) noexcept : value(v) {}
	
	friend bool operator==(OrderId a, OrderId b) noexcept
	{
		return a.value == b.value;
	}
};

enum class Side : uint8_t
{
	SELL,
	BUY
};

enum class OrderType : uint8_t 
{
	LIMIT,
	MARKET,
	IOC,
	FOK
};

struct Order
{
//	std::string symbol;
	OrderId order_id;
	int64_t price;	
	int64_t quantity;
	int64_t timestamp;	
	OrderType order_type;
	Side side;

	bool is_valid() const noexcept;
};

#endif // ORDER_H