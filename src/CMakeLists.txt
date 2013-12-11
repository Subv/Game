file(GLOB_RECURSE sources *.cpp *.h)

SET(game_SRCS
	${game_SRCS}
	${sources}
)

include_directories(
	${CMAKE_BINARY_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/Common
	${CMAKE_CURRENT_SOURCE_DIR}/Entities
	${CMAKE_CURRENT_SOURCE_DIR}/Logging
	${CMAKE_CURRENT_SOURCE_DIR}/Maps
	${CMAKE_CURRENT_SOURCE_DIR}/Maps/Tiles
	${CMAKE_CURRENT_SOURCE_DIR}/Menu
	${CMAKE_SOURCE_DIR}/dep/SFML-2.1/include
)

add_executable(Game
	${game_SRCS}
)

target_link_libraries(Game
	sfml-main
	sfml-graphics
	sfml-window
	sfml-system
)