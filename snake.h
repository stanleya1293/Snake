#ifndef SNAKE_H
#define SNAKE_H

#include <glad/glad.h>
#include <cglm/cglm.h>
#include "renderer.h"

typedef enum {
	SNAKE_UP,
	SNAKE_DOWN,
	SNAKE_RIGHT,
	SNAKE_LEFT
} Direction;

typedef struct snake {
	struct snake* previous;
	struct snake* next;
	Direction direction;
	int x;
	int y;
	struct snake* head;
	struct snake* tail;
} Snake;

Snake* Create_Snake();

void Add_Snake(Snake* snake);

void Update_Snake(Snake* snake);

void Draw_Snake(Snake* snake, Renderer renderer);



#endif
