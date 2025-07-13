# Simple Limit Order Book

This is a basic C++ implementation of a limit order book supporting **limit buy/sell orders**, **order matching**, and **trade logging**.

## Features

- Place limit orders (buy/sell)
- Match orders based on price-time priority
- Cancel orders by ID
- Track and log completed trades
- Return detailed order execution status

## Project Structure


<p>
. <br>
├── README.md <br>
├── include <br>
    ├── BUILD <br>
    ├── ORDER.hpp <br>
    ├── ORDERBOOK.hpp <br>
    ├── ORDERRESULT.hpp <br>
    └── TRADE.hpp <br>
├── main.cpp <br>
└── src <br>
    ├── BUILD <br>
    ├── ORDER.cpp <br>
    ├── ORDERBOOK.cpp <br>
    ├── ORDERRESULT.cpp <br>
    └── TRADE.cpp <br>
</p>



## Order Lifecycle

1. **PlaceOrder**: Creates and inserts an order into the correct queue, then attempts to fill against opposite book at given price.
3. **Trade Logging**: On match, generates and stores a `Trade`. 
4. **CancelOrder**: Removes an order by ID if unmatched.

## Next Steps

- Add support for **market orders**
- Implement multiple instruments (e.g., AAPL, TSLA)
- Add testing and CLI or GUI interaction layer
