#include <stdio.h>
#include <stdlib.h>

#define MAX_IN_LINE 128
#define MAX_LINES 8192

struct node {
  int key;
  int value;
  struct node *next;
};

struct hashMap {
  int num_elements;
  int capacity;
  struct node **arr;
};

int hashFunction(struct hashMap *hm, int key) { return key % hm->capacity; }

void increment(struct hashMap *hm, int key) {
  int digest = hashFunction(hm, key);

  struct node *node = (struct node *)malloc(sizeof(struct node));

  node->key = key;
  node->value++;
  node->next = NULL;

  if (hm->arr[digest] == NULL) {
    hm->arr[digest] = node;
  } else {
    node->next = hm->arr[digest];
    hm->arr[digest] = node;
  }

  return;
}

int search(struct hashMap *hm, int key) {

  int digest = hashFunction(hm, key);
  struct node *head = hm->arr[digest];

  while (head != NULL) {
    if (head->key == key) {
      return head->value;
    }
    head = head->next;
  }
  return -1;
}

int compare(const void *a, const void *b) { return (*(int *)a - *(int *)b); }

int main(int argc, char *argv[]) {

  // Part 1
  char *buffer = malloc(sizeof(char) * MAX_IN_LINE);
  int *array1 = malloc(sizeof(int) * MAX_LINES);
  int *array2 = malloc(sizeof(int) * MAX_LINES);

  int line_counter = 0;
  while (fgets(buffer, MAX_IN_LINE, stdin)) {
    sscanf(buffer, "%d %d", &array1[line_counter], &array2[line_counter]);
    line_counter++;
  }

  qsort(array1, line_counter, sizeof(int), compare);
  qsort(array2, line_counter, sizeof(int), compare);

  int result = 0;

  for (int i = 0; i < line_counter; i++) {
    result += abs(array1[i] - array2[i]);
  }

  printf("Here is part 1: %d\n", result);

  // Part 2
  struct hashMap *hm = (struct hashMap *)malloc(sizeof(struct hashMap));
  hm->capacity = 10000;
  hm->num_elements = 0;

  hm->arr = (struct node **)calloc(hm->capacity, sizeof(struct node *));

  int j = 0;
  for (int i = 0; i < line_counter; i++) {
    for (; j < line_counter; j++) {
      if (array1[i] < array2[j]) {
        break;
      } else if (array1[i] == array2[j]) {
        increment(hm, array1[i]);
      }
    }
  }

  result = 0;
  for (int i = 0; i < hm->capacity; i++) {
    struct node *node = hm->arr[i];
    struct node *temp_node;
    while (node != NULL) {
      result += node->key * node->value;
      temp_node = node->next;
      free(node);
      node = temp_node;
    }
  }

  printf("Here is part 2: %d\n", result);

  free(hm->arr);
  free(hm);

  free(buffer);
  free(array1);
  free(array2);

  return 0;
}
