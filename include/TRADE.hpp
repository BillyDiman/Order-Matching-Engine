#ifndef TRADE
#define TRADE

#include <ctime>
#include <string>


struct Trade {

        int tradeID;
        int buyOrderID;
        int sellOrderID;
        double price;
        int volumeFilled;
        std::string buyerName;
        std::string sellerName;
        time_t timeStamp;

        Trade(int tradeID, int buyOrderID, int sellOrderID, double price, int volumeFilled, std::string buyerName, std::string sellerName, time_t timeStamp);

};

#endif