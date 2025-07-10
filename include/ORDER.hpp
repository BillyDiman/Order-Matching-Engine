#ifndef ORDER
#define ORDER

#include <ctime>
#include <string>


enum orderSide{
    BUY,
    SELL
};

struct Order {

        int volume;
        double price;
        std::string clientName;
        int orderID;
        time_t timeStamp;
        orderSide side;

        Order(int volume, double price, std::string clientName, int orderID, time_t timeStamp, orderSide side);
        bool operator==(const Order& other) const;

};

#endif