#include "snake.h"
#include "renderer.h"

Snake* Create_Snake() {
	Snake* snake_head = (Snake *) malloc(sizeof(Snake));
	snake_head->next = NULL;
	snake_head->direction = SNAKE_RIGHT;
	snake_head->x = 10;
	snake_head->y = 10;
	return snake_head;	
}

void Add_Snake(Snake* snake) {
	
}

void Draw_Snake(Snake* snake, Renderer renderer) {
	mat4 snake_translate;
	mat4 snake_scale;
	glm_mat4_identity(snake_translate);
	glm_mat4_identity(snake_scale);
	printf("Snake x: %d", snake->x);
	printf("Snake y: %d", snake->y);
	glm_translate(snake_translate, (vec3) 
			{
			-0.05 + (((float) snake->x - 10) / 10),
		       	-0.05 + (((float) snake->y - 10) / 10),
			0.0f
			}
			);
	glm_scale(snake_scale, (vec3) {0.05f, 0.05f, 0.05f});
	mat4 snake_transform;
	GLint transform_location = glGetUniformLocation(renderer.shader_program, "transform");
	GLint color_location = glGetUniformLocation(renderer.shader_program, "color");
	glm_mat4_mul(snake_translate, snake_scale, snake_transform);
	glUniformMatrix4fv(transform_location, 1, GL_FALSE, snake_transform[0]);
	vec4 snake_color = {0.0f, 1.0f, 0.0f, 1.0f};
	glUniform4fv(color_location, 1, snake_color);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
