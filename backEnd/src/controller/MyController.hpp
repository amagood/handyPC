//
//  MyController.hpp
//  web-starter-project
//
//  Created by Leonid on 2/12/18.
//  Copyright © 2018 oatpp. All rights reserved.
//

#ifndef MyController_hpp
#define MyController_hpp

#include "dto/DTOs.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"

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
        return createDtoResponse(Status::CODE_200, dto);
    }


    ENDPOINT_INFO(getTime) {
        info->summary = "get time in unix time format";
        info->addResponse<MyDto::ObjectWrapper>(
                Status::CODE_200,
                "application/json"
        );
    }
    /*
     * DTO 是 DATA TRANSFER OBJECT 在DTOs.hpp設定
     *
     * */
    ENDPOINT("GET", "/getTime", getTime) {
        auto dto = TimeDto::createShared();
        dto->statusCode = 200;
        dto->timestamp = time(0);
        return createDtoResponse(Status::CODE_200, dto);
    }


  // TODO Insert Your endpoints here !!!

/**
 *  Finish ENDPOINTs generation ('ApiController' codegen)
 */
#include OATPP_CODEGEN_END(ApiController)
  
};

#endif /* MyController_hpp */
