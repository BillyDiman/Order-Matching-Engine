#ifndef ORDER_BOOK
#define ORDER_BOOK

#include "ORDER.hpp"
#include "ORDERRESULT.hpp"
#include <ctime>
#include <string>
#include <queue>
#include <map>
#include <unordered_map>


class orderBook {
    private:
        std::map<double, std::deque<Order>> buyOrderMap;                //Price -> FIFO queue
        std::map<double, std::deque<Order>> sellOrderMap;               //Price -> FIFO queue
        int currentOrderID = 0;                                         //To assign orderID's within an orderBook

        std::unordered_map<int, Order> buyOrderIDMap;
        std::unordered_map<int, Order> sellOrderIDMap;

        Order CreateOrder (int volume, double price, std::string clientName, orderSide side);   
    
    public:
        OrderResult PlaceOrder (int volume, double price, std::string clientName, orderSide side);                                   //Returns orderID and whether it completed, is in progress, or couldn't be filled
        int CancelOrder (int ID);                                       //Returns 0 for success, 1 for error
        double GetVolumeAtPrice (double price);                         //Returns volume at price

};

#endif