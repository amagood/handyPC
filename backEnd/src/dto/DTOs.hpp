//
//  MyDto.hpp
//  crud
//
//  Created by Leonid on 3/13/18.
//  Copyright © 2018 oatpp. All rights reserved.
//

#ifndef DTOs_hpp
#define DTOs_hpp

#include "oatpp/core/data/mapping/type/Object.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)
/**
 *  Data Transfer Object. Object containing fields only.
 *  Used in API for serialization/deserialization and validation
 */

//https://oatpp.io/docs/components/dto/#declaration
class MyDto : public oatpp::data::mapping::type::Object {

DTO_INIT(MyDto, Object)

    DTO_FIELD(Int32, statusCode);
    DTO_FIELD(String, message);
    DTO_FIELD(Int64, timestamp);

};

class TimeDto : public oatpp::data::mapping::type::Object {

DTO_INIT(TimeDto, Object)

    DTO_FIELD(Int32, statusCode);
    DTO_FIELD(Int64, timestamp);

};

class GeneralDto : public oatpp::data::mapping::type::Object {

DTO_INIT(GeneralDto, Object)

    DTO_FIELD(Int32, statusCode);
    DTO_FIELD(Int64, timestamp);
    DTO_FIELD(String, dataString);

};
#include OATPP_CODEGEN_END(DTO)

#endif /* DTOs_hpp */
