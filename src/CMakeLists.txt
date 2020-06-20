set(BINARY ${CMAKE_PROJECT_NAME})

include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_BINARY_DIR}")

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cc)
set(SOURCES ${SOURCES})
set(EXECUTABLE_NAME ${BINARY})
add_executable(${EXECUTABLE_NAME} ${SOURCES})

# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)

# Link sfml
target_link_libraries(${BINARY} sfml-graphics sfml-audio)

# Copy assets on post build
add_custom_command(TARGET ${BINARY} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/src/assets $<TARGET_FILE_DIR:${BINARY}>/assets)