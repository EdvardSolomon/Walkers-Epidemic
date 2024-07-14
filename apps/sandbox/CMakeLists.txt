file(GLOB SRCS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*"
)

add_executable(sandbox ${SRCS})

# target_link_libraries(sandbox ${GLAD_LIBRARY} ${GLFW_LIBRARY})

# Ссылки на библиотеку babyma
target_link_libraries(sandbox PRIVATE ${BABYMA_DLL})
