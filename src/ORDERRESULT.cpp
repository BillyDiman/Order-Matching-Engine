#include "ORDERRESULT.hpp"

#include <ctime>
#include <string>



OrderResult::OrderResult(int orderID, orderStatus status, double price, int volumeFilled, time_t timeStamp):
    orderID(orderID),
    status(status),
    price(price),
    volumeFilled(volumeFilled),
    timeStamp(timeStamp)
    {}