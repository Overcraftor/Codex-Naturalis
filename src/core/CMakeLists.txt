add_library(CoreLib STATIC)
target_sources(CoreLib
        PRIVATE cards/Face.cpp cards/Coin.cpp cards/Carte.cpp scoring/RegleDePoints.cpp board/Manuscrit.cpp engine/Pioche.cpp
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


include(FetchContent)
FetchContent_Declare(
        json
        URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz
        DOWNLOAD_EXTRACT_TIMESTAMP true
)
FetchContent_MakeAvailable(json)

# json reader
target_link_libraries(CoreLib PRIVATE nlohmann_json::nlohmann_json)

target_include_directories(CoreLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
