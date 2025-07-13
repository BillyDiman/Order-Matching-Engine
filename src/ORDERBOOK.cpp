#include "ORDERBOOK.hpp"

#include <ctime>
#include <queue>
#include <map>
#include <iostream>
#include <algorithm>

orderBook::orderBook():
    buyOrderMap(),
    sellOrderMap() 
    {}


OrderResult orderBook::PlaceOrder (int volume, double price, std::string clientName, orderSide side){
    Order newOrder = CreateOrder(volume, price, clientName, side);
    int newOrderID = newOrder.orderID;
    int initialVolume = volume;
    int finalVolume = volume;

    orderStatus newOrderStatus = NOT_STARTED;

    bool done = false;

    if(side == BUY){
        for(auto it = sellOrderMap.begin(); it != sellOrderMap.end() && it->first <= price; ++it){
            std::deque<Order>& oppositePriceQueue = sellOrderMap[it->first];
            while(!oppositePriceQueue.empty()){
                Order tempOrder = oppositePriceQueue.front();
                oppositePriceQueue.pop_front();

                if(tempOrder.volume >= newOrder.volume){
                    tempOrder.volume -= newOrder.volume;
                    if(tempOrder.volume != 0){
                        oppositePriceQueue.push_front(tempOrder);
                        sellOrderIDMap[tempOrder.orderID] = tempOrder;
                    }
                    Trade tempTrade = Trade(++currentTradeID, newOrderID, tempOrder.orderID, tempOrder.price, newOrder.volume, newOrder.clientName, tempOrder.clientName, time(nullptr));
                    tradeLog.push_back(tempTrade);
                    CancelOrder(newOrder.orderID);
                    newOrderStatus = COMPLETED;
                    finalVolume = 0;
                    done = true;
                    break;
                }else{
                    newOrder.volume -= tempOrder.volume;
                    Trade tempTrade = Trade(++currentTradeID, newOrderID, tempOrder.orderID, tempOrder.price, tempOrder.volume, newOrder.clientName, tempOrder.clientName, time(nullptr));
                    tradeLog.push_back(tempTrade);
                    finalVolume -= tempOrder.volume;
                    sellOrderIDMap.erase(tempOrder.orderID);
                    newOrderStatus = IN_PROGRESS;
                }
            }
            if(done == true){
                break;
            }
        }
        std::cout << "Order placed.";
        OrderResult ret = OrderResult(newOrderID, newOrderStatus, price, (initialVolume - finalVolume), time(nullptr));
        return ret;
    }else{
        for(auto it = buyOrderMap.rbegin(); it != buyOrderMap.rend() && it->first >= price; ++it){
            std::deque<Order>& oppositePriceQueue = buyOrderMap[it->first];
            while(!oppositePriceQueue.empty()){
                Order tempOrder = oppositePriceQueue.front();
                oppositePriceQueue.pop_front();

                if(tempOrder.volume >= newOrder.volume){
                    tempOrder.volume -= newOrder.volume;
                    if(tempOrder.volume != 0){
                        oppositePriceQueue.push_front(tempOrder);
                        buyOrderIDMap[tempOrder.orderID] = tempOrder;
                    }
                    Trade tempTrade = Trade(++currentTradeID, tempOrder.orderID, newOrderID, tempOrder.price, newOrder.volume, tempOrder.clientName, newOrder.clientName, time(nullptr));
                    tradeLog.push_back(tempTrade);
                    CancelOrder(newOrder.orderID);
                    newOrderStatus = COMPLETED;
                    finalVolume = 0;
                    done = true;
                    break;
                }else{
                    newOrder.volume -= tempOrder.volume;
                    Trade tempTrade = Trade(++currentTradeID, tempOrder.orderID, newOrderID, tempOrder.price, tempOrder.volume, tempOrder.clientName, newOrder.clientName, time(nullptr));
                    tradeLog.push_back(tempTrade);
                    finalVolume -= tempOrder.volume;
                    buyOrderIDMap.erase(tempOrder.orderID);
                    newOrderStatus = IN_PROGRESS;
                }
            }
            if(done == true){
                break;
            }
        }
            std::cout << "Order placed.";
            OrderResult ret = OrderResult(newOrderID, newOrderStatus, price, (initialVolume - finalVolume), time(nullptr));
            return ret;
    }
}


//Helper function for PlaceOrder
Order orderBook::CreateOrder (int volume, double price, std::string clientName, orderSide side){
    Order newOrder(volume, price, clientName, ++currentOrderID, time(nullptr), side);
    

    if(side == BUY){
        buyOrderIDMap[currentOrderID] = newOrder;

        std::deque<Order>& priceQueue = buyOrderMap[price];
        priceQueue.push_back(newOrder);
    }else{
        sellOrderIDMap[currentOrderID] = newOrder;

        std::deque<Order>& priceQueue = sellOrderMap[price];
        priceQueue.push_back(newOrder);
    }
    
    std::cout << "Order successfully created";
    
    return newOrder;
}


int orderBook::CancelOrder (int ID){
    if(buyOrderIDMap.find(ID) != buyOrderIDMap.end()){
        Order tempOrder = buyOrderIDMap.find(ID)->second;
        std::deque<Order>& priceQueue = buyOrderMap[tempOrder.price];
        auto it = std::find(priceQueue.begin(), priceQueue.end(), tempOrder);
        if(it != priceQueue.end()){
            priceQueue.erase(it);
            buyOrderIDMap.erase(ID);
            std::cout << "Order successfully erased";
            return 0;
        }

        std::cout << "Order couldn't be erased";
        return 1;

    }else if(sellOrderIDMap.find(ID) != sellOrderIDMap.end()){
        Order tempOrder = sellOrderIDMap.find(ID)->second;
        std::deque<Order>& priceQueue = sellOrderMap[tempOrder.price];
        auto it = std::find(priceQueue.begin(), priceQueue.end(), tempOrder);
        if(it != priceQueue.end()){
            priceQueue.erase(it);
            sellOrderIDMap.erase(ID);
            std::cout << "Order successfully erased";
            return 0;
        }

        std::cout << "Order couldn't be erased";
        return 1;
    }else{
        std::cout << "That order does not exist...";

        return 1;

    }
}


std::vector<Trade> orderBook::GetTradeLog (){

    return tradeLog;
}