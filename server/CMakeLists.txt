cmake_minimum_required(VERSION 3.0.0)

set(SOURCES main.cpp server.cpp server.h data.cpp data.h)

add_executable(some_quiz_server ${SOURCES})
