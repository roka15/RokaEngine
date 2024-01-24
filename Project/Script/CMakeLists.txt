# 현재 디렉토리에 있는 모든 파일을 SRC_FILES 변수에 추가한다.
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)



add_library(Script MODULE ${SRC_FILES})

#C/C++ 플래그 지정
target_compile_definitions(Script PRIVATE
    $<$<CONFIG:Debug>:
        _DEBUG=1
    >
)


#전처리기
add_definitions(-DSCRIPTDLL_EXPORTS -DUNICODE -D_UNICODE -D_LIB -D_DEBUG=1)

#라이브러리 디렉토리 지정
link_directories(${CMAKE_SOURCE_DIR}/../../External/Dll/ ${CMAKE_SOURCE_DIR}/../../External/Lib/Script/Debug/)

# shape 의 include 경로 지정
target_include_directories(Script PUBLIC ${CMAKE_SOURCE_DIR}/ ${CMAKE_SOURCE_DIR}/../../External/Include/ ${CMAKE_SOURCE_DIR}/../../External/Include/openssl/Debug/)

#Library 찾기
find_library(EngineLib
     NAMES Engine
     HINTS "${CMAKE_SOURCE_DIR}/../../External/Dll/Engine/Debug"
)
find_library(StlLib
     NAMES RokaSTL_Lib
     HINTS "${CMAKE_SOURCE_DIR}/../../External/Lib/Debug/RokaSTL"
)

#Lib Link
target_link_libraries(Script PUBLIC ${EngineLib} ${StlLib})

#출력 경로 설정
set_target_properties(Script PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../../External/Dll/Script
ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../../External/Dll/Script)

#미리 컴파일된 헤더
#target_precompile_headers(Script PRIVATE pch.h)

# shape 의 컴파일 옵션 지정
#target_compile_options(Script PRIVATE -Wall -Werror)

# shape 를 C++ 17 로 컴파일
target_compile_features(Script PRIVATE cxx_std_17)

# FetchContent 를 사용하기 위해 include.
#include(FetchContent)

# fmt 라이브러리를 불러온다.
#FetchContent_Declare(
#  Fmt
#  GIT_REPOSITORY "https://github.com/fmtlib/fmt"
#  GIT_TAG "7.1.3"
#  )
#FetchContent_MakeAvailable(Fmt)

# shape 에 링크
#target_link_libraries(shape PRIVATE fmt)