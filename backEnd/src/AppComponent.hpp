//
//  AppComponent.hpp
//  oatpp-web-starter
//
//  Created by Leonid on 3/2/18.
//  Copyright © 2018 lganzzzo. All rights reserved.
//

#ifndef AppComponent_hpp
#define AppComponent_hpp

#include "oatpp/web/server/HttpConnectionHandler.hpp"

#include "oatpp/network/server/SimpleTCPConnectionProvider.hpp"

#include "oatpp/parser/json/mapping/ObjectMapper.hpp"

#include "oatpp/core/macro/component.hpp"
#include "oatpp-swagger/Model.hpp"
#include "oatpp-swagger/Resources.hpp"

/**
 *  Class which creates and holds Application components and registers components in oatpp::base::Environment
 *  Order of components initialization is from top to bottom
 */
class AppComponent {
public:
  
  /**
   *  Create ConnectionProvider component which listens on the port
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, serverConnectionProvider)([] {
    return oatpp::network::server::SimpleTCPConnectionProvider::createShared(25565);   //PORT
  }());
  
  /**
   *  Create Router component
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, httpRouter)([] {
    return oatpp::web::server::HttpRouter::createShared();
  }());
  
  /**
   *  Create ConnectionHandler component which uses Router component to route requests
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::server::ConnectionHandler>, serverConnectionHandler)([] {
    OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router); // get Router component
    return oatpp::web::server::HttpConnectionHandler::createShared(router);
  }());
  
  /**
   *  Create ObjectMapper component to serialize/deserialize DTOs in Contoller's API
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, apiObjectMapper)([] {
    return oatpp::parser::json::mapping::ObjectMapper::createShared();
  }());

  /**
 *  General API docs info
 */
OATPP_CREATE_COMPONENT(
  std::shared_ptr<oatpp::swagger::DocumentInfo>, 
  swaggerDocumentInfo
)([] {
  
  oatpp::swagger::DocumentInfo::Builder builder;
  builder
   .setTitle("My Demo Service with Swagger-UI")
   .setDescription("C++/oat++ Web Service with Swagger-UI")
   .setVersion("1.0")
   .setContactName("Mr. Developer")
   .setContactUrl("https://oatpp.io/")
   .setLicenseName("Apache License, Version 2.0")
   .setLicenseUrl("http://www.apache.org/licenses/LICENSE-2.0")
   .addServer("http://amagood1.no-ip.org:25565", "server on localhost");    //設定網址
   return builder.build();
}());
/**
 *  Swagger-Ui Resources
 */
OATPP_CREATE_COMPONENT(
  std::shared_ptr<oatpp::swagger::Resources>, 
  swaggerResources
)([] {
  return oatpp::swagger::Resources::loadResources(
    OATPP_SWAGGER_RES_PATH
  );
}());
};

#endif /* AppComponent_hpp */
