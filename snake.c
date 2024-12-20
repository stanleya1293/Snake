#include "snake.h"
#include "renderer.h"

Snake* Create_Snake() {
	Snake* snake_head = (Snake *) malloc(sizeof(Snake));
	snake_head->previous = NULL;
	snake_head->next = NULL;
	snake_head->direction = SNAKE_RIGHT;
	snake_head->x = 10;
	snake_head->y = 10;
	snake_head->tail = snake_head;
	snake_head->head = snake_head;
	return snake_head;	
}

void Add_Snake(Snake* snake) {
	if (snake->next == NULL) {
		snake->next = (Snake *) malloc(sizeof(Snake));
		Snake* new_snake = snake->next;
		new_snake->previous = snake;
		new_snake->next = NULL;
		new_snake->x = snake->x;
		new_snake->y = snake->y;
		new_snake->direction = snake->direction;
		new_snake->head = snake->head;
		new_snake->head->tail = new_snake;
	}
	else {
		Add_Snake(snake->next);
	}
}

bool Check_Snake_Collision(Snake* snake) {
	Snake* current_snake = snake->tail;
	while (current_snake != snake && current_snake != snake->next) {
		if (snake->x == current_snake->x && snake->y == current_snake->y) {
			return true;	
		}
		current_snake = current_snake->previous; 
	}
	return false;
	
}

void Update_Snake(Snake* snake) {
	Snake* snek = snake->tail;
	while (snek->previous != NULL) {
		snek->x = snek->previous->x;
		snek->y = snek->previous->y;
		snek->direction = snek->previous->direction;
		snek = snek->previous;
	}
	switch (snake->direction) {
		case SNAKE_UP:
			snake->y = snake->y + 1;
			break;
		case SNAKE_DOWN:
			snake->y = snake->y - 1;
			break;
		case SNAKE_RIGHT:
			snake->x = snake->x + 1;
			break;
		case SNAKE_LEFT:
			snake->x = snake->x - 1;
			break;
		default:
			break;
	}
}

void Draw_Snake(Snake* snake, Renderer renderer) {
	mat4 snake_translate;
	mat4 snake_scale;
	glm_mat4_identity(snake_translate);
	glm_mat4_identity(snake_scale);
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
	if (snake->next != NULL) {
		Draw_Snake(snake->next, renderer);
	}
}
