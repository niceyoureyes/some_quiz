cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_INSTALL_PREFIX "../Some Quiz")

project(some_quiz VERSION 0.1.0)

set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

find_package(Boost 1.62.0 COMPONENTS date_time system regex REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS}) 

add_subdirectory(client)
add_subdirectory(server)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# set install rules (windows only)
if(WIN32)
    if(MSVC)
        install(TARGETS some_quiz_server some_quiz_client DESTINATION bin COMPONENT binaries)
    endif(MSVC)
endif(WIN32)
