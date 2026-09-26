add_library(CoreLib STATIC)
target_sources(CoreLib
        PRIVATE core.cpp
        INTERFACE
            FILE_SET HEADERS
            FILES
                core.h)

target_include_directories(CoreLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
