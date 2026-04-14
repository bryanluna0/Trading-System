#include <gtest/gtest.h>
#include "engine/order/order.h"

// Valid Tests
TEST(OrderTest, ValidOrderIsCreated)
{
    SymbolId symbol_id{0};
    int64_t price = 1;
    int64_t quantity = 1;
    OrderType order_type = OrderType::LIMIT;
    Side side = Side::BUY;

    auto order_opt = Order::createOrder(symbol_id, price, quantity, order_type, side);

    ASSERT_TRUE(order_opt.has_value());

    auto order = order_opt.value();

    EXPECT_EQ(order.symbol_id, symbol_id);
    EXPECT_EQ(order.getPrice(), price);
    EXPECT_EQ(order.getQuantity(), quantity);
    EXPECT_EQ(order.order_type, order_type);
    EXPECT_EQ(order.side, side);
}

// Boundary Tests
TEST(OrderTest, InvalidPriceZeroReturnsNullopt)
{
    SymbolId symbol_id{0};
    int64_t price = 0; // invalid
    int64_t quantity = 1; // valid
    OrderType order_type = OrderType::LIMIT;
    Side side = Side::BUY;

    auto order_opt = Order::createOrder(symbol_id, price, quantity, order_type, side);

    ASSERT_FALSE(order_opt.has_value());
}

TEST(OrderTest, InvalidQuantityZeroReturnsNullopt)
{
    SymbolId symbol_id{0};
    int64_t price = 1; // valid
    int64_t quantity = 0; // invalid
    OrderType order_type = OrderType::FOK;
    Side side = Side::BUY;

    auto order_opt = Order::createOrder(symbol_id, price, quantity, order_type, side);

    ASSERT_FALSE(order_opt.has_value());
}

// Invalid Tests
TEST(OrderTest, InvalidPriceNegativeReturnsNullopt)
{
    SymbolId symbol_id{0};
    int64_t price = -1; // invalid
    int64_t quantity = 1; // valid
    OrderType order_type = OrderType::FOK;
    Side side = Side::BUY;

    auto order_opt = Order::createOrder(symbol_id, price, quantity, order_type, side);

    ASSERT_FALSE(order_opt.has_value());
}

TEST(OrderTest, InvalidQuantityNegativeReturnsNullopt)
{
    SymbolId symbol_id{0};
    int64_t price = 1; // valid
    int64_t quantity = -1; // invalid
    OrderType order_type = OrderType::FOK;
    Side side = Side::BUY;

    auto order_opt = Order::createOrder(symbol_id, price, quantity, order_type, side);

    ASSERT_FALSE(order_opt.has_value());
}

// Unique id

TEST(OrderTest, UniqueOrderIdsGenerated)
{
    SymbolId symbol_id{0};
    int64_t price = 1; 
    int64_t quantity = 1; 
    OrderType order_type = OrderType::FOK;
    Side side = Side::BUY;

    auto order_opt_1 = Order::createOrder(symbol_id, price, quantity, order_type, side);
    auto order_opt_2 = Order::createOrder(symbol_id, price, quantity, order_type, side);

    ASSERT_TRUE(order_opt_1.has_value());
    ASSERT_TRUE(order_opt_2.has_value());

    auto order_1 = order_opt_1.value();
    auto order_2 = order_opt_2.value();
    EXPECT_FALSE(order_1.order_id == order_2.order_id);
}