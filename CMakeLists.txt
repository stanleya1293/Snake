project(Snake)
add_executable(Snake main.c renderer.c snake.c)
add_subdirectory(./lib/glad)
target_link_libraries(Snake PRIVATE glad)
add_subdirectory(./lib/glfw-3.4)
target_link_libraries(Snake glfw)
add_subdirectory(./lib/cglm)
target_link_libraries(Snake PRIVATE cglm)

