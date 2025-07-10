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


int orderBook::PlaceOrder (int volume, double price, std::string clientName, orderSide side){
    Order newOrder = CreateOrder(volume, price, clientName, side);

    //TO-DO, implement order matching algorithm

}

int orderBook::CancelOrder (int ID){
    if(buyOrderIDMap.find(ID) != buyOrderIDMap.end()){
        Order tempOrder = buyOrderIDMap.find(ID)->second;
        std::deque<Order>& priceQueue = buyOrderMap[tempOrder.price];
        auto it = std::find(priceQueue.begin(), priceQueue.end(), tempOrder);
        if(it != priceQueue.end()){
            priceQueue.erase(it);
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
    
    std::cout << "Order succesfully created";
    
    return newOrder;
}