cmake_minimum_required(VERSION 3.27)
project(calc CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED on)

FILE(GLOB_RECURSE SRC_FILES "./src/*.cpp")
FILE(GLOB_RECURSE INC_FILES "./src/*.hpp")

add_executable(${PROJECT_NAME} ${SRC_FILES} ${INC_FILES})

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    include(GNUInstallDirs)
    install(TARGETS ${PROJECT_NAME}
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
endif()
