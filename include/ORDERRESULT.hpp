#ifndef ORDER_RESULT
#define ORDER_RESULT

#include <ctime>
#include <string>


enum orderStatus{
    COMPLETED,
    IN_PROGRESS,
    NOT_STARTED
};


struct OrderResult {

        int orderID;
        orderStatus status;
        double price;
        int volumeFilled;
        time_t timeStamp;

        OrderResult(int orderID, orderStatus status, double price, int volumeFilled, time_t timeStamp);

};

#endif