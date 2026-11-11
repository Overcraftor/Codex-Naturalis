add_library(CoreLib STATIC)
target_sources(CoreLib
        PRIVATE cards/Face.cpp cards/Coin.cpp cards/Carte.cpp scoring/RegleDePoints.cpp board/Manuscrit.cpp engine/Pioche.cpp cards/CardFactory.cpp
        INTERFACE
        FILE_SET HEADERS
        FILES
            cards/Face.h
            cards/Coin.h
            cards/Carte.h
            Types.h
            scoring/RegleDePoints.h
            scoring/Objectif.h
            board/Manuscrit.h
            engine/Pioche.h)

target_include_directories(CoreLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
