project(Snake)
add_executable(Snake snake.c renderer.c)
add_subdirectory(./lib/glad)
target_link_libraries(Snake PRIVATE glad)
add_subdirectory(./lib/glfw-3.4)
target_link_libraries(Snake glfw)
add_subdirectory(./lib/cglm)
target_link_libraries(Snake PRIVATE cglm)

