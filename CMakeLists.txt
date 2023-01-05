
cmake_minimum_required(VERSION 3.10)

if(IDF_VERSION_MAJOR GREATER_EQUAL 4)

    idf_component_register( SRCS_DIR src
                            INCLUDE_DIRS include)

else()

    project(AW9523
            LANGUAGES C
            DESCRIPTION "A Hardware Agnostic driver for the AW9523 LED Driver chip")

    file(GLOB SOURCES "src/*.c")
    add_library(${PROJECT_NAME} STATIC ${SOURCES})
    target_include_directories(${PROJECT_NAME} PUBLIC include)
    
    if(MSVC)
        target_compile_options(${PROJECT_NAME} PRIVATE /W4)
    else()
        target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
    endif()

endif()
