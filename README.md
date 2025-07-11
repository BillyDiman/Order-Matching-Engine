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
/src <br>
├── ORDERBOOK.cpp # Core order book logic <br>
├── ORDERRESULT.cpp # Order execution result struct <br>
├── TRADE.cpp # Trade logging struct (WIP) <br>
├── ORDER.cpp # Order struct <br>
/include <br>
├── ORDERBOOK.hpp <br>
├── ORDERRESULT.hpp <br>
├── TRADE.hpp <br>
├── ORDER.hpp <br>
main.cpp # Entry point (WIP) <br>
</p>



## Order Lifecycle

1. **PlaceOrder**: Creates and inserts an order into the correct queue, then attempts to fill against opposite book at given price.
3. **Trade Logging**: On match, generates and stores a `Trade`. 
4. **CancelOrder**: Removes an order by ID if unmatched.

## Next Steps

- Add support for **market orders**
- Implement multiple instruments (e.g., AAPL, TSLA)
- Add testing and CLI or GUI interaction layer
