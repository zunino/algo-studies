// In these times of AI-assisted development, I decided to write some code
// on my own. I thought about writing a simple linked-list with an arena
// allocator. It was fun.
//
// Andre Zunino <neyzunino@gmail.com>
// April 2026

#include <stdlib.h>
#include <stdio.h>

typedef struct {
  size_t capacity;
  size_t size;
  void *data;
} Arena;

Arena arena_create(size_t capacity) {
  return (Arena) {
    .capacity = capacity,
    .size = 0,
    .data = malloc(capacity)
  };
}

void arena_destroy(Arena *arena) {
  free(arena->data);
  arena->data = NULL;
  arena->size = 0;
  arena->capacity = 0;
}

void *arena_alloc(Arena *arena, size_t size) {
  if (arena->size + size > arena->capacity) {
    return NULL;
  }
  void *ptr = arena->data + arena->size;
  arena->size += size;
  return ptr;
}

typedef struct Node {
  int value;
  struct Node *next;
} Node;

Node *arena_alloc_node(Arena *arena, int value, Node *next) {
  void *ptr = arena_alloc(arena, sizeof (Node));
  if (ptr == NULL) {
    return NULL;
  }
  Node *node = (Node *) ptr;
  node->value = value;
  node->next = next;
  return node;
}

void print_list(Node *node) {
  while (node) {
    printf("%d", node->value);
    node = node->next;
    if (node != NULL) printf(" -> ");
  }
  putchar('\n');
}

void print_arena_details(const Arena *const arena) {
  printf("size: %ld | capacity: %ld\n", arena->size, arena->capacity);
}

int main(void) {
  Arena arena = arena_create(64 * sizeof (Node));

  Node *n5 = arena_alloc_node(&arena, 50, NULL);
  Node *n4 = arena_alloc_node(&arena, 40, n5);
  Node *n3 = arena_alloc_node(&arena, 30, n4);
  Node *n2 = arena_alloc_node(&arena, 20, n3);
  Node *n1 = arena_alloc_node(&arena, 10, n2);

  print_arena_details(&arena);
  print_list(n1);

  arena_destroy(&arena);
}
