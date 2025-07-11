#include "TRADE.hpp"

#include <ctime>
#include <string>



Trade::Trade(int tradeID, int buyOrderID, int sellOrderID, double price, int volumeFilled, std::string buyerName, std::string sellerName, time_t timeStamp):
    tradeID(tradeID),
    buyOrderID(buyOrderID),
    sellOrderID(sellOrderID),
    price(price),
    volumeFilled(volumeFilled),
    buyerName(buyerName),
    sellerName(sellerName),
    timeStamp(timeStamp)
    {}