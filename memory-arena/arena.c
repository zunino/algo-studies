// Naive implementation of an "arena allocator".
//
// Andre Zunino <neyzunino@gmail.com>
// January 2025

#include <stdlib.h>
#include <stdio.h>

typedef struct Arena {
    void *data;
    size_t capacity;
    size_t size;
} Arena;

Arena arena_create(size_t capacity) {
    return (Arena) {
        .data = malloc(capacity),
        .capacity = capacity,
        .size = 0
    };
}

void arena_destroy(Arena *arena) {
    free(arena->data);
    arena->data = NULL;
    arena->size = 0;
    arena->capacity = 0;
}

void *arena_alloc(Arena *arena, size_t size) {
    size_t remaining = arena->capacity - arena->size;
    if (remaining < size) {
        printf("can't allocate\n");
        return NULL;
    }
    void *item = arena->data + arena->size;
    arena->size += size;
    return item;
}

int *arena_int(Arena *arena, int value) {
    int *i = (int *) arena_alloc(arena, sizeof (int));
    *i = value;
    return i;
}

int main() {
    Arena a = arena_create(8);
    // int allocation
    int *n1 = (int *) arena_alloc(&a, sizeof (int));
    *n1 = 10;
    // int allocation with helper function
    int *n2 = arena_int(&a, 20);
    /* int *n3 = arena_int(&a, 30); */
    printf("n1 = %d\n", *n1);
    printf("n2 = %d\n", *n2);
    arena_destroy(&a);
}
