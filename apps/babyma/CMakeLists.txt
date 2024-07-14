# file(GLOB SRCS
# "${CMAKE_CURRENT_SOURCE_DIR}/src/*"
# )

# # add_executable(babyma ${SRCS})
# add_library(babyma SHARED ${SRCS})

# # target_link_libraries(babyma ${GLAD_LIBRARY} ${GLFW_LIBRARY})

file(GLOB SRCS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# Создаем библиотеку
add_library(babyma SHARED ${SRCS})

# Устанавливаем макрос для компиляции DLL
target_compile_definitions(babyma PRIVATE BUILDING_DLL)
