/* 
	types.h file used to hold important types

*/

#ifndef TYPES_H
#define TYPES_H

#include <cstdint>

enum class OrderResult
{
	ADD_ORDER_FAIL,
	BOOK_FULL,
	CANCEL_ORDER_FAIL,
	INVALID_ORDER_TYPE,
	INVALID_PRICE,
	INVALID_QUANTITY,
	MODIFY_ORDER_FAIL,
	ORDER_ALREADY_EXISTS,
	ORDER_NOT_FOUND,
	SUCCESS
};

// TODO: Why is SymbolId different from OrderId?

struct SymbolId
{
	uint64_t value;

	explicit SymbolId(uint64_t v) noexcept : value(v) {}

	bool operator==(const SymbolId& other) const noexcept
	{
		return value == other.value;
	}
	
	bool operator!=(const SymbolId& other) const noexcept
	{
		return value != other.value;
	}
};

// order specific data types

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

struct OrderId 
{
	uint64_t value;
	
	explicit constexpr OrderId(uint64_t v) noexcept : value(v) {}
	
	friend bool operator==(OrderId a, OrderId b) noexcept
	{
		return a.value == b.value;
	}
};

namespace std {
    template<>
    struct hash<OrderId> {
        size_t operator()(const OrderId& id) const noexcept {
            return hash<uint64_t>{}(id.value);
        }
    };
}

#endif // TYPES_H