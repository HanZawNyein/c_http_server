cmake_minimum_required(VERSION 3.28)
project(sample C)

set(CMAKE_C_STANDARD 11)

add_executable(sample main.c
        http/constants.h
        http/response.h
        controllers/home.h
        routes.h
        http/logging.h
        http/request.h
)
