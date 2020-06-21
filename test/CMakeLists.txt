cmake_minimum_required (VERSION 3.8)

set(BINARY ${CMAKE_PROJECT_NAME}_test)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES true
	*.h 
	*.cc
)
set(SOURCES
	${TEST_SOURCES}
)
add_executable(${BINARY} ${SOURCES})

# The idea is that gtest runs my library testing the code
target_link_libraries(${BINARY} PUBLIC
	gtest_main 
	${CMAKE_PROJECT_NAME}_lib
)

add_test(
	NAME ${BINARY} 
	COMMAND ${BINARY}
)

# Copy assets on post build
# Just here to suppress any warnings when grabbing assets
add_custom_command(TARGET ${BINARY} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/src/assets $<TARGET_FILE_DIR:${BINARY}>/assets
)