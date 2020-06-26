//
//  MyController.hpp
//  web-starter-project
//
//  Created by Leonid on 2/12/18.
//  Copyright © 2018 oatpp. All rights reserved.
//

#ifndef MyController_hpp
#define MyController_hpp

#include <chrono>
#include <cstdio>
#include <errorLog.h>
#include <serverLogicFunctions.h>

#include "dto/DTOs.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "json.hpp"

using json = nlohmann::json;




/**
 * Sample Api Controller.
 */
class MyController : public oatpp::web::server::api::ApiController {
public:
    /**
     * Constructor with object mapper.
     * @param objectMapper - default object mapper used to serialize/deserialize DTOs.
     */
    MyController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
            : oatpp::web::server::api::ApiController(objectMapper)
    {}
public:

/**
 *  Begin ENDPOINTs generation ('ApiController' codegen)
 */
#include OATPP_CODEGEN_BEGIN(ApiController)

    ENDPOINT("GET", "/", root) {
        auto dto = MyDto::createShared();
        dto->statusCode = 200;
        dto->message = "Hello World!";
        unsigned long long ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        dto->timestamp = (long long int) ms;
        return createDtoResponse(Status::CODE_200, dto);
    }

    //OwO是在設定(宣告)這個API的變數名
    ENDPOINT_INFO(OwO) {
        info->summary = "Echo endpoint with custom message";
        info->addResponse<MyDto::ObjectWrapper>(
                Status::CODE_200,
                "application/json"  //回傳值為JSON
        );
    }
    /*
     *
     * "POST"代表HTTP POST "/echo/status/{status}"代表網址列的敘述  OwO是這個API的變數名
     * PATH(Int32 整數, status變數名), BODY_STRING POST單純字串(String字串型態, message叫做MESSAGE))  這行都是輸入(打到SERVER)
     * DTO 是回傳用的變數
     */
    ENDPOINT("POST", "/OwO/status/{status}", OwO,
             PATH(Int32, status), BODY_STRING(String, message)) {
        auto dto = MyDto::createShared();
        dto->statusCode = status;
        dto->message = message;
        unsigned long long ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        dto->timestamp = (long long int) ms;
        return createDtoResponse(Status::CODE_200, dto);
    }


    ENDPOINT_INFO(getTime) {
        info->summary = "get time in unix time format";
        info->addResponse<GeneralDto::ObjectWrapper>(
                Status::CODE_200,
                "application/json"
        );
    }
    /*
     * DTO 是 DATA TRANSFER OBJECT 在DTOs.hpp設定
     *
     * */
    ENDPOINT("GET", "/api/getTime", getTime) {
        auto dto = GeneralDto::createShared();

        json returnJson;
        returnJson["status"] = 500;
        dto->statusCode = 500;
        unsigned long long ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        dto->timestamp = (long long int) ms;

        returnJson["timestamp"] = ms;
        returnJson["status"] = 200;
        dto->dataString = returnJson.dump().c_str();

        dto->statusCode = 200;
        return createDtoResponse(Status::CODE_200, dto);
    }


    // TODO Insert Your endpoints here !!!
    ENDPOINT_INFO(getViewNumber) {
        info->summary = "get the number of views and increase by 1";
        info->addResponse<GeneralDto::ObjectWrapper>(
                Status::CODE_200,
                "application/json"
        );
    }
    ENDPOINT("GET", "/api/getViewNumber", getViewNumber) {
        using namespace Error;
        auto dto = GeneralDto::createShared();
        dto->statusCode = 200;
        unsigned long long ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        dto->timestamp = (long long int) ms;
        info(unixTime2Str(ms)),info(" Info: "), info(" getViewNumber\n");
        //dto->dataString = "HI";
        json returnJson;
        // TODO set returnJson["ViewNumber"]
        FILE *saveFile;
        saveFile = fopen("saveViewNumber.dat", "r");
        if(saveFile == nullptr)
        {
            ///exception
            ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            error(unixTime2Str(ms)),error(" Error: "), error(" saveViewNumber.dat cannot found\n");
            returnJson["status"] = 500;
            returnJson["error"] = "saveViewNumber.dat cannot found";
            dto->timestamp = (long long int) ms;
            dto->dataString = returnJson.dump().c_str();
            return createDtoResponse(Status::CODE_200, dto);
        }

        unsigned int visitorN;
        fscanf(saveFile, "%d", &visitorN);
        fclose(saveFile);

        saveFile = fopen("saveViewNumber.dat", "w");
        if(saveFile == nullptr)
        {
            ///exception
            ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            error(unixTime2Str(ms)),error(" Error: "), error(" saveViewNumber.dat cannot write\n");
            returnJson["status"] = 500;
            returnJson["error"] = "saveViewNumber.dat cannot write";
            dto->timestamp = (long long int) ms;
            dto->dataString = returnJson.dump().c_str();
            return createDtoResponse(Status::CODE_200, dto);
        }
        fprintf(saveFile, "%d", visitorN+1);
        fclose(saveFile);
        debug(unixTime2Str(ms)), debug(" Debug: "), debug(" saved ViewNumber = "), debug(visitorN+1), debug("\n");
        returnJson["status"] = 200;
        returnJson["viewNumber"] = visitorN+1;
        ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();



        dto->dataString = returnJson.dump().c_str();
        dto->timestamp = (long long int) ms;
        return createDtoResponse(Status::CODE_200, dto);
    }

    ENDPOINT_INFO(getProduct) {
        info->summary = "Get the details of a product by ID";
        info->addResponse<GeneralDto::ObjectWrapper>(
                Status::CODE_200,
                "application/json"
        );
    }
    /*
     * DTO 是 DATA TRANSFER OBJECT 在DTOs.hpp設定
     *
     * */
    ENDPOINT("GET", "/api/getProduct/{productId}", getProduct, PATH(Int32, productId)) {
        auto dto = GeneralDto::createShared();

        json returnJson;
        returnJson["status"] = 500;
        dto->statusCode = 500;
        unsigned long long ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        dto->timestamp = (long long int) ms;


        using namespace Error;
        info(ms, "getProduct("), info(productId), info(")\n");

        returnJson = getProductById(productId);
        debug(ms, "returnJson: "),debug(returnJson.dump(1).c_str()), debug("\n");
        if(returnJson.empty()) ///ID cannot find
        {
            ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            dto->timestamp = (long long int) ms;
            error(ms,"ID not found\n");
            returnJson["timestamp"] = ms;
            returnJson["status"] = 404;
            returnJson["error"] = "ID not found";
            dto->statusCode = 200;
            dto->dataString = returnJson.dump().c_str();
            return createDtoResponse(Status::CODE_200, dto);
        }

        ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        dto->timestamp = (long long int) ms;
        returnJson["timestamp"] = ms;
        returnJson["status"] = 200;
        dto->dataString = returnJson.dump().c_str();


        dto->statusCode = 200;
        return createDtoResponse(Status::CODE_200, dto);
    }

    ENDPOINT_INFO(getProductDetails) {
        info->summary = "Get the details of a product by ID";
        info->addResponse<GeneralDto::ObjectWrapper>(
                Status::CODE_200,
                "application/json"
        );
    }
    ENDPOINT("GET", "/api/getProductDetails/{productId}", getProductDetails, PATH(Int32, productId)) {
        auto dto = GeneralDto::createShared();

        json returnJson;
        returnJson["status"] = 500;
        dto->statusCode = 500;
        unsigned long long ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        dto->timestamp = (long long int) ms;


        using namespace Error;
        info(ms, "getProductDetails("), info(productId), info(")\n");

        returnJson = getProductDetailsById(productId);
        debug(ms, "returnJson: "),debug(returnJson.dump(1).c_str()), debug("\n");
        if(returnJson.empty()) ///ID cannot find
        {
            ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            dto->timestamp = (long long int) ms;
            error(ms,"ID not found\n");
            returnJson["timestamp"] = ms;
            returnJson["status"] = 404;
            returnJson["error"] = "ID not found";
            dto->statusCode = 200;
            dto->dataString = returnJson.dump().c_str();
            return createDtoResponse(Status::CODE_200, dto);
        }

        ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        dto->timestamp = (long long int) ms;
        returnJson["timestamp"] = ms;
        returnJson["status"] = 200;
        dto->dataString = returnJson.dump().c_str();


        dto->statusCode = 200;
        return createDtoResponse(Status::CODE_200, dto);
    }

    ENDPOINT_INFO(getCategory) {
        info->summary = "Get the info of a category by categoryId";
        info->addResponse<GeneralDto::ObjectWrapper>(
                Status::CODE_200,
                "application/json"
        );
    }
    ENDPOINT("GET", "/api/getCategory/{categoryId}", getCategory, PATH(Int32, categoryId)) {
        auto dto = GeneralDto::createShared();

        json returnJson;
        returnJson["status"] = 500;
        dto->statusCode = 500;
        unsigned long long ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        dto->timestamp = (long long int) ms;


        using namespace Error;
        info(ms, "getCategory("), info(categoryId), info(")\n");

        returnJson = getCategoryById(categoryId);
        debug(ms, "returnJson: "),debug(returnJson.dump(1).c_str()), debug("\n");
        if(returnJson.empty()) ///ID cannot find
        {
            ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            dto->timestamp = (long long int) ms;
            error(ms,"ID not found\n");
            returnJson["timestamp"] = ms;
            returnJson["status"] = 404;
            returnJson["error"] = "ID not found";
            dto->statusCode = 200;
            dto->dataString = returnJson.dump().c_str();
            return createDtoResponse(Status::CODE_200, dto);
        }

        ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        dto->timestamp = (long long int) ms;
        returnJson["timestamp"] = ms;
        returnJson["status"] = 200;
        dto->dataString = returnJson.dump().c_str();


        dto->statusCode = 200;
        return createDtoResponse(Status::CODE_200, dto);
    }

    ENDPOINT_INFO(getEvaluation) {
        info->summary = "Get an exist evaluation by evaluationId";
        info->addResponse<GeneralDto::ObjectWrapper>(
                Status::CODE_200,
                "application/json"
        );
    }
    ENDPOINT("GET", "/api/getEvaluation/{evaluationId}", getEvaluation, PATH(Int32, evaluationId)) {
        auto dto = GeneralDto::createShared();

        json returnJson;
        returnJson["status"] = 500;
        dto->statusCode = 500;
        unsigned long long ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        dto->timestamp = (long long int) ms;


        using namespace Error;
        info(ms, "getEvaluation("), info(evaluationId), info(")\n");

        returnJson = getEvaluationById(evaluationId);
        debug(ms, "returnJson: "),debug(returnJson.dump(1).c_str()), debug("\n");
        if(returnJson.empty()) ///ID cannot find
        {
            ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            dto->timestamp = (long long int) ms;
            error(ms,"ID not found\n");
            returnJson["timestamp"] = ms;
            returnJson["status"] = 404;
            returnJson["error"] = "ID not found";
            dto->statusCode = 200;
            dto->dataString = returnJson.dump().c_str();
            return createDtoResponse(Status::CODE_200, dto);
        }

        ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        dto->timestamp = (long long int) ms;
        returnJson["timestamp"] = ms;
        returnJson["status"] = 200;
        dto->dataString = returnJson.dump().c_str();


        dto->statusCode = 200;
        return createDtoResponse(Status::CODE_200, dto);
    }

    ENDPOINT_INFO(createEvaluation) {
        info->summary = "Create an evaluation with given products.";
        info->addResponse<GeneralDto::ObjectWrapper>(
                Status::CODE_200,
                "application/json"  //回傳值為JSON
        );
    }
    ENDPOINT("POST", "/createEvaluation", createEvaluation,
             BODY_STRING(String, message)) {
        using namespace Error;
        json inputJson;
        json  returnJson;
        auto dto = GeneralDto::createShared();
        dto->statusCode = 500;
        std::string inputStr = message->std_str();
        inputJson = json::parse(inputStr);
        unsigned long long ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();


        info(ms,"createEvaluation: inputJson:"),info(inputJson.dump().c_str()), info("\n");
        std::vector<int> productIds = inputJson["productIds"];
        debug(ms, "productIds vector = ");
        for(auto i:productIds)
            debug(i), debug(", ");
        debug("\n");
        if(productIds.empty())
        {
            ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            returnJson["status"] = 404;
            returnJson["timestamp"] =ms;
            returnJson["error"] = "productIds is empty";
            error(ms, "productIds is empty\n");
            dto->timestamp = (long long int) ms;
            dto->statusCode = 200;
            dto->dataString = returnJson.dump().c_str();
            return createDtoResponse(Status::CODE_200, dto);
        }



        int newId = createEvaluationByIds(productIds);
        if(newId < 0) //failes
        {
            ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            returnJson["status"] = 500;
            returnJson["timestamp"] =ms;
            returnJson["error"] = "Unknown error at createEvaluationByIds(productIds)";
            error(ms, "createEvaluationByIds(productIds) failed\n");
            dto->timestamp = (long long int) ms;
            dto->statusCode = 200;
            dto->dataString = returnJson.dump().c_str();
            return createDtoResponse(Status::CODE_200, dto);
        }
        returnJson["status"] = 200;
        returnJson["evaluationId"] = newId;
        ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        returnJson["timestamp"] =ms;
        dto->timestamp = (long long int) ms;
        dto->statusCode = 200;
        dto->dataString = returnJson.dump().c_str();
        info(ms, "Success createEvaluation, evaluationId = "), info(newId), info('\n');
        return createDtoResponse(Status::CODE_200, dto);
    }

    ENDPOINT_INFO(deleteEvaluation) {
        info->summary = "Delete an evaluation by Id.";
        info->addResponse<GeneralDto::ObjectWrapper>(
                Status::CODE_200,
                "application/json"  //回傳值為JSON
        );
    }
    ENDPOINT("POST", "/deleteEvaluation", deleteEvaluation,
             BODY_STRING(String, message)) {
        using namespace Error;
        json inputJson, returnJson;
        auto dto = GeneralDto::createShared();
        dto->statusCode = 500;
        std::string inputStr = message->std_str();
        inputJson = json::parse(inputStr);
        unsigned long long ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

        info(ms,"createEvaluation: inputJson:"),info(inputJson.dump().c_str()), info("\n");

        if(!inputJson.contains("evaluationId"))
        {
            ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            returnJson["status"] = 404;
            returnJson["timestamp"] =ms;
            returnJson["error"] = "evaluationId not found";
            error(ms, "evaluationId not found\n");
            dto->timestamp = (long long int) ms;
            dto->statusCode = 200;
            dto->dataString = returnJson.dump().c_str();
            return createDtoResponse(Status::CODE_200, dto);
        }
        int deleteId = inputJson["evaluationId"];



        if(!deleteEvaluationById(deleteId)) //failes
        {
            ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            returnJson["status"] = 500;
            returnJson["timestamp"] =ms;
            returnJson["error"] = "Unknown error at deleteEvaluationById(deleteId)";
            error(ms, "deleteEvaluationById(deleteId) failed\n");
            dto->timestamp = (long long int) ms;
            dto->statusCode = 200;
            dto->dataString = returnJson.dump().c_str();
            return createDtoResponse(Status::CODE_200, dto);
        }
        returnJson["status"] = 200;
        ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        returnJson["timestamp"] =ms;
        dto->timestamp = (long long int) ms;
        dto->statusCode = 200;
        dto->dataString = returnJson.dump().c_str();
        info(ms, "Success deleteEvaluation"), info('\n');
        return createDtoResponse(Status::CODE_200, dto);
    }


/**
 *  Finish ENDPOINTs generation ('ApiController' codegen)
 */
#include OATPP_CODEGEN_END(ApiController)

};

#endif /* MyController_hpp */
