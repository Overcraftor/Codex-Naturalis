add_executable(Codex_Console)
target_sources(Codex_Console
        PRIVATE main.cpp)

target_link_libraries(Codex_Console PRIVATE CoreLib)