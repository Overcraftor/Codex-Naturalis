add_library(CoreLib STATIC)
target_sources(CoreLib
        PRIVATE core.cpp cards/Face.cpp cards/Coin.cpp cards/Carte.cpp
        INTERFACE
        FILE_SET HEADERS
        FILES
            core.h
            cards/Face.h
            cards/Coin.h
            cards/Carte.h
            Types.h)

target_include_directories(CoreLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
