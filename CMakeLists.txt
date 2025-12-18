cmake_minimum_required(VERSION 3.15)
project(ArcadiaEngine)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
endif()

include(FetchContent)

add_library(lib
    src/IntventorySystem/InventoryPacker/InventoryPacker.cpp
    src/Navigator/TeleporterNetwork.cpp
    src/ArcadiaEngine.cpp
    src/LeaderBoard/LeaderBoard.h
    src/AuctionTree/AuctionTree.h
    src/PlayerTable/PlayerTable.h
    src/IntventorySystem/InventorySystem.cpp
    src/ServerKernel/ServerKernel.cpp
    src/Navigator/WorldNavigator.cpp
)

target_include_directories(lib PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/src)


add_executable(ArcadiaEngine src/main_test_students.cpp)

target_link_libraries(ArcadiaEngine PRIVATE lib)

enable_testing()

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

FetchContent_MakeAvailable(googletest)

add_executable(runTests
    src/IntventorySystem/InventoryPacker/InventoryPacker.test.cpp
    src/Navigator/TeleporterNetwork.test.cpp
)

target_link_libraries(runTests
    lib
    gtest_main
)

target_include_directories(runTests PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/src)

include(GoogleTest)
gtest_discover_tests(runTests)