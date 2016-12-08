cmake_minimum_required(VERSION 3.6)
project(SpaceInvader)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp InvadersCl.cpp InvadersCl.h cmake_module/BulletCl.cpp cmake_module/BulletCl.h)
add_executable(SpaceInvader ${SOURCE_FILES})


set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_module")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(SpaceInvader ${SFML_LIBRARIES})
endif()