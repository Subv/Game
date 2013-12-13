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
	${CMAKE_CURRENT_SOURCE_DIR}/Maps/Tiles/Shapes
	${CMAKE_CURRENT_SOURCE_DIR}/Menu
	${CMAKE_CURRENT_SOURCE_DIR}/Input
	${CMAKE_SOURCE_DIR}/dep/SFML-2.1/include
	${CMAKE_SOURCE_DIR}/dep/Thor/include
	${CMAKE_SOURCE_DIR}/dep/Thor/extlibs/Aurora/include
)

add_executable(Game
	${game_SRCS}
)

target_link_libraries(Game
	sfml-graphics
	sfml-window
	sfml-system
	thor
)

IF (UNIX)
	add_custom_command(TARGET Game POST_BUILD
					   COMMAND ${CMAKE_COMMAND} -E copy_directory
						   ${CMAKE_SOURCE_DIR}/Resources ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Resources)
ELSEIF(WIN32)
	add_custom_command(TARGET Game POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/Resources ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE}/Resources)
ENDIF()