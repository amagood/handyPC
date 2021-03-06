cmake_minimum_required(VERSION 3.1)

set(project_name my-project) ## rename your project here

project(${project_name})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXE_LINKER_FLAGS "-pthread -ldl")

add_library(${project_name}-lib
        src/AppComponent.hpp
        src/controller/MyController.cpp
        src/controller/MyController.hpp
        src/dto/DTOs.hpp
)

## link libs

find_package(oatpp 1.0.0 REQUIRED)
find_package(oatpp-swagger  1.0.0 REQUIRED) # <-- add this

target_link_libraries(${project_name}-lib
        PUBLIC oatpp::oatpp
        PUBLIC oatpp::oatpp-test
        PUBLIC oatpp::oatpp-swagger          # <-- add this
)
add_definitions(
        -DOATPP_SWAGGER_RES_PATH="${OATPP_BASE_DIR}/bin/oatpp-swagger/res"
) # <-- add this


target_include_directories(${project_name}-lib PUBLIC src)

## add executables
include_directories(lib)

add_executable(${project_name}-exe
        src/App.cpp
        test/app/MyApiTestClient.hpp
        lib/json.hpp
        src/errorLog.h src/serverLogicFunctions.cpp src/serverLogicFunctions.h
        src/sqlite3.h src/sqlite3.c src/sqlite3ext.h
        )

target_link_libraries(${project_name}-exe ${CMAKE_DL_LIBS})
target_link_libraries(${project_name}-exe ${project_name}-lib)
add_dependencies(${project_name}-exe ${project_name}-lib)

add_executable(${project_name}-test
        test/tests.cpp
        lib/json.hpp
        test/app/TestComponent.hpp
        test/app/MyApiTestClient.hpp
        test/MyControllerTest.cpp
        test/MyControllerTest.hpp
        src/errorLog.h
)

target_link_libraries(${project_name}-test ${project_name}-lib)
add_dependencies(${project_name}-test ${project_name}-lib)

set_target_properties(${project_name}-lib ${project_name}-exe ${project_name}-test PROPERTIES
        CXX_STANDARD 11
        CXX_EXTENSIONS OFF
        CXX_STANDARD_REQUIRED ON
)

enable_testing()
add_test(project-tests ${project_name}-test)
