# CMake 프로그램 최소 버전
cmake_minimum_required(VERSION 3.28.1)

# 프로젝트 정보
project(
    RokaProj
    VERSION 0.1
    DESCRIPTION "CMAKE 예제"
    LANGUAGES CXX)

add_executable (program CMakeMain.cpp)