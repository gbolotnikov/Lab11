cmake_minimum_required(VERSION 3.10)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(join_server VERSION ${PROJECT_VESRION})

find_package(Boost COMPONENTS COMPONENTS program_options REQUIRED)
find_package(Threads)
find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(join_server main.cpp
    Server.cpp
    Session.cpp
    SessionController.cpp
    DataBaseController.cpp
 )

set_target_properties(join_server PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(join_server PRIVATE "${CMAKE_BINARY_DIR}")

if(WIN32)
target_link_libraries(join_server PRIVATE 
    ws2_32
    wsock32 
    ${Boost_LIBRARIES} 
    ${CMAKE_THREAD_LIBS_INIT}
    Boost::program_options 
    stdc++fs)
else()
target_link_libraries(join_server PRIVATE 
    ${Boost_LIBRARIES} 
    ${CMAKE_THREAD_LIBS_INIT}
    Boost::program_options 
    stdc++fs)
endif()



install(TARGETS join_server RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)