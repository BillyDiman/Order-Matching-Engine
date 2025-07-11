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

    orderSide oppositeSide;
    orderStatus newOrderStatus = NOT_STARTED;

    if(side == BUY){
        oppositeSide = SELL;
        std::deque<Order>& oppositePriceQueue = sellOrderMap[price];
        if(!oppositePriceQueue.empty()){
            while(!oppositePriceQueue.empty()){
                Order tempOrder = oppositePriceQueue.front();
                oppositePriceQueue.pop_front();

                if(tempOrder.volume >= newOrder.volume){
                    tempOrder.volume -= newOrder.volume;
                    if(tempOrder.volume != 0){
                        oppositePriceQueue.push_front(tempOrder);
                    }
                    CancelOrder(newOrder.orderID);
                    newOrderStatus = COMPLETED;
                    finalVolume = 0;
                    break;
                }else{
                    newOrder.volume -= tempOrder.volume;
                    finalVolume -= tempOrder.volume;
                    sellOrderIDMap.erase(tempOrder.orderID);
                    newOrderStatus = IN_PROGRESS;
                }
            }
            std::cout << "Order placed.";
            OrderResult ret = OrderResult(newOrderID, newOrderStatus, price, (initialVolume - finalVolume), time(nullptr));
            return ret;
        }else{
            std::cout << "Order couldn't be placed at this price.";
            OrderResult ret = OrderResult(newOrderID, newOrderStatus, price, (initialVolume - finalVolume), time(nullptr));
            return ret;
        }
    }else{
        oppositeSide = BUY;
        std::deque<Order>& oppositePriceQueue = buyOrderMap[price];
        if(!oppositePriceQueue.empty()){
            while(!oppositePriceQueue.empty()){
                Order tempOrder = oppositePriceQueue.front();
                oppositePriceQueue.pop_front();

                if(tempOrder.volume >= newOrder.volume){
                    tempOrder.volume -= newOrder.volume;
                    if(tempOrder.volume != 0){
                        oppositePriceQueue.push_front(tempOrder);
                    }
                    CancelOrder(newOrder.orderID);
                    newOrderStatus = COMPLETED;
                    finalVolume = 0;
                    break;
                }else{
                    newOrder.volume -= tempOrder.volume;
                    finalVolume -= tempOrder.volume;
                    buyOrderIDMap.erase(tempOrder.orderID);
                    newOrderStatus = IN_PROGRESS;
                }
            }
            std::cout << "Order placed.";
            OrderResult ret = OrderResult(newOrderID, newOrderStatus, price, (initialVolume - finalVolume), time(nullptr));
            return ret;
        }else{
            std::cout << "Order couldn't be placed at this price.";
            OrderResult ret = OrderResult(newOrderID, newOrderStatus, price, (initialVolume - finalVolume), time(nullptr));
            return ret;
        }
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


double orderBook::GetVolumeAtPrice (double price){

    //Maybe don't need...?
    //Probably change to modify order, but that seems redundant given you can just cancel then create a new one

}