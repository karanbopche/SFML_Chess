enable_testing()

set(
    TEST_SOURCE
    ChessStateMachine/test_IdleState.cpp
    Pieces/test_Bishop.cpp
    Pieces/test_Config.cpp
    Pieces/test_King.cpp
    Pieces/test_Knight.cpp
    Pieces/test_Pawn.cpp
    Pieces/test_Piece.cpp
    Pieces/test_Queen.cpp
    Pieces/test_Rook.cpp
)

add_executable(
    UNIT_TESTS
    ${TEST_SOURCE}
)

target_link_libraries(
    UNIT_TESTS
    GTest::gtest_main
    GTest::gmock_main
    ChessLib
)

target_include_directories(
    UNIT_TESTS
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

include(GoogleTest)
gtest_discover_tests(UNIT_TESTS)

set(ASSETS "${CMAKE_SOURCE_DIR}/Chess/Assets")
add_custom_command(
    TARGET UNIT_TESTS
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different ${ASSETS} "${CMAKE_CURRENT_BINARY_DIR}/Assets/"
    DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/Assets/"
    COMMENT "Copy assets folder from ${ASSETS} => ${CMAKE_CURRENT_BINARY_DIR}/Assets/"
)