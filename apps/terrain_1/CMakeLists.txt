file(GLOB SRCS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*"
)

add_executable(terrain_1 ${SRCS})
target_link_libraries(terrain_1 ${GLAD_LIBRARY} ${GLFW_LIBRARY})

# set(SOURCE_RESOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/resources)
# set(TARGET_RESOURCES_DIR ${CMAKE_CURRENT_BINARY_DIR}/resources)

# add_custom_command(
# TARGET terrain_0 POST_BUILD
# COMMAND ${CMAKE_COMMAND} -E copy_directory
# ${SOURCE_RESOURCES_DIR} ${TARGET_RESOURCES_DIR}
# )
