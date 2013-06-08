aux_source_directory(. SRC_LIST)

INCLUDE_DIRECTORIES ("${CMAKE_SOURCE_DIR}/include")

set(CMAKE_CXX_FLAGS -std=c++11)
add_executable(MintTest ${SRC_LIST})

