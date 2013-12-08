file(GLOB sources *.cpp *.h)

SET(game_SRCS
	${game_SRCS}
	${sources}
)

include_directories(
	${CMAKE_BINARY_DIR}
	${CMAKE_SOURCE_DIR}/dep/SFML-2.1/include
	#${CMAKE_SOURCE_DIR}/dep/SFGUI/include
)

add_executable(Game
	${game_SRCS}
)

target_link_libraries(Game
	sfml-main
	sfml-graphics
	sfml-window
	sfml-system
	#sfgui
)