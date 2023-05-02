cmake_minimum_required(VERSION 3.21)
project(ManagePasswords)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost REQUIRED archive serialization)

add_executable(ManagePasswords main.cpp entry.h entry.cc)

target_link_libraries(ManagePasswords Boost::archive Boost::serialization)