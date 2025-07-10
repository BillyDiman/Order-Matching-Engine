#include "ORDER.hpp"

#include <ctime>
#include <string>



Order::Order(int volume, double price, std::string clientName, int orderID, time_t timeStamp, orderSide side):
    volume(volume),
    price(price),
    clientName(clientName),
    orderID(orderID),
    timeStamp(timeStamp),
    side(side)
    {}

bool Order::operator==(const Order& other) const{
    return volume == other.volume &&
            price == other.price &&
            clientName == other.clientName &&
            orderID == other.orderID &&
            timeStamp == other.timeStamp &&
            side == other.side;
}