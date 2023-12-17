CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules)

set(LIB_MAJOR_VERSION "0")
set(LIB_MINOR_VERSION "1")
set(LIB_PATCH_VERSION "0")
set(LIB_VERSION_STRING "${LIB_MAJOR_VERSION}.${LIB_MINOR_VERSION}.${LIB_PATCH_VERSION}")

project(rapidjson_macros VERSION "${LIB_VERSION_STRING}" LANGUAGES CXX)

# set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install")
set(CMAKE_INSTALL_DOCDIR "${CMAKE_INSTALL_PREFIX}/doc")

################################################################################
# Build

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>)

################################################################################
# Tests

OPTION(RAPIDJSON_MACROS_BUILD_TESTS "Build rapidjson_macros test suite" ON)

if(RAPIDJSON_MACROS_BUILD_TESTS)
    enable_testing()
    include(CTest)
    add_subdirectory(test)
endif()

################################################################################
# Examples

OPTION(RAPIDJSON_MACROS_BUILD_EXAMPLES "Build rapidjson_macros examples" ON)

if(RAPIDJSON_MACROS_BUILD_EXAMPLES)
    add_subdirectory(example)
    install(DIRECTORY example/
            DESTINATION "${CMAKE_INSTALL_DOCDIR}/examples")
endif()

################################################################################
# Install

install(TARGETS ${PROJECT_NAME} 
    EXPORT ${PROJECT_NAME}Targets)

install(EXPORT ${PROJECT_NAME}Targets
        DESTINATION "lib/cmake/${PROJECT_NAME}")

include(CMakePackageConfigHelpers)
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION "lib/cmake/${PROJECT_NAME}")
install(FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        DESTINATION "lib/cmake/${PROJECT_NAME}")

install(DIRECTORY "${PROJECT_SOURCE_DIR}/include" DESTINATION ${CMAKE_INSTALL_PREFIX})
