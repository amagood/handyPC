//
// Created by amagood on 2020/5/9.
//

#include "serverLogicFunctions.h"
#include "json.hpp"

using json = nlohmann::json;
json getProductById(int id)
{
    //TODO: interact with the database
    json result;
    result["productId"] = id;
    result["productName"] = "INvidiAmd Core i9-3990X super ti(1024C/4096T) 128MHz(TURBO 10.3GHz)/1T/35W ";
    result["category"] = 1;
    result["price"] = 5000;
    result["description"] = "(1024C/4096T) 128MHz(TURBO 10.3GHz)/1T/35W";
    result["unboxingDiscussion"] = "http://amagood1.no-ip.org:25565";
    result["picture"] = "https://www.amd.com/system/files/2020-02/415625-threadripper-3990X-campagin-promo-1260x709_0.jpg";

    return result;
}
json getProductDetailsById(int id)
{
    json result;
    //TODO ...
    return result;
}
json getCategoryById(int id)
{
    json result;
    //TODO ...
    return result;
}
json getEvaluationById(int id)
{
    json result;
    //TODO ...
    return result;
}
int  createEvaluationByIds(std::vector<int> productIds)
{
    //TODO
    return -1;
}

bool deleteEvaluationById(int id)
{
    //TODO
    return false;
}