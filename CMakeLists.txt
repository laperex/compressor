cmake_minimum_required(VERSION 3.0.0)
project(sfjhhsaf VERSION 0.1.0 LANGUAGES C)

include(CTest)
enable_testing()

include_directories(include src)
file(GLOB_RECURSE TARGET_SRC "src/*.cpp" "src/*.c")

add_executable(main ${TARGET_SRC})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
