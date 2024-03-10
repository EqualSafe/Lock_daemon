cmake_minimum_required(VERSION 3.8)
project(lock_sys CXX)

set(SRC_FILES
    src/main.cpp
    src/utils/CommandLineUtils.cpp
    src/utils/MqttWrapper.cpp
    src/lock/Deadlock.cpp
)

add_executable(${PROJECT_NAME} ${SRC_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17) 

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX /wd4068)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

find_package(aws-crt-cpp REQUIRED)

target_link_libraries(${PROJECT_NAME} pigpio AWS::aws-crt-cpp)
