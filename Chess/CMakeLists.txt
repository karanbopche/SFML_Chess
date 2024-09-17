
set(
    SOURCE_FILES
    Src/Game.cpp
    Src/Config.cpp
    Src/Pieces/Piece.cpp
    Src/Pieces/Pawn.cpp
    Src/Pieces/Bishop.cpp
    Src/Pieces/King.cpp
    Src/Pieces/Knight.cpp
    Src/Pieces/Queen.cpp
    Src/Pieces/Rook.cpp
    Src/ChessStateMachine/ChessStateMachine.cpp
    Src/ChessStateMachine/States/ChessState.cpp
    Src/ChessStateMachine/States/IdleState.cpp
    Src/ChessStateMachine/States/PieceSelectedState.cpp
    Src/ChessStateMachine/States/CheckState.cpp
    Src/ChessStateMachine/States/CheckMateState.cpp
    Src/GameStateMachine/GameStateMachine.cpp
    Src/GameStateMachine/States/ChessState.cpp
    Src/GameStateMachine/States/GameState.cpp
    Src/GameStateMachine/States/MainMenuState.cpp
    Src/GameStateMachine/States/PauseMenuState.cpp
)

set(
    MAIN_SOURCE
    Src/main.cpp
)

# List(
#     FILTER
#     SOURCE_FILES_LIB
#     EXCLUDE
#     REGEX
#     ".*${MAIN_SOURCE}"
# )

# include(CMakePrintHelpers)
# cmake_print_variables(SOURCE_FILES_LIB)

add_library(
    ChessLib
    STATIC
    ${SOURCE_FILES}
)

target_include_directories(
    ChessLib
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Src
)

target_link_libraries(
    ChessLib
    PUBLIC
    sfml-graphics
    sfml-audio
    sfml-system
    sfml-window
)

add_executable(${PROJECT_NAME} ${MAIN_SOURCE})
target_link_libraries(${PROJECT_NAME} PRIVATE ChessLib)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

include(CMakePrintHelpers)
cmake_print_variables(CMAKE_CURRENT_BINARY_DIR)

if(WIN32)
    add_custom_command(
        TARGET ${PROJECT_NAME}
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:${PROJECT_NAME}>
        VERBATIM
    )
endif()

set(ASSETS "${PROJECT_SOURCE_DIR}/Chess/Assets")
add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different ${ASSETS} "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Assets"
    DEPENDS "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Assets"
    COMMENT "Copy assets folder from ${ASSETS} => ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
)
