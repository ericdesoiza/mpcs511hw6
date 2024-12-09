#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "heap.h"

Heap* create_heap(int max_size) {
    Heap* heap = malloc(sizeof(Heap));
    heap->length = 0;
    heap->max_size = max_size;
    heap->arr = malloc(max_size * sizeof(HeapNode));

    return heap;
}

void heappush(Heap* heap, int vertex, int distance) {
  if (heap->length >= heap->max_size - 1) {
    heap->arr = realloc(heap->arr, 2 * (heap->max_size) * sizeof(HeapNode));
    heap->max_size = heap->max_size * 2;
  }

  heap->length++;
  heap->arr[heap->length - 1] = (HeapNode) {vertex, distance};

  HeapNode new_element, parent;
  int start, position, parent_position;

  new_element = heap->arr[heap->length - 1];
  start = 0; 
  position = heap->length - 1;

  while (position > start) {
    parent_position = (position - 1) >> 1;
    parent = heap->arr[parent_position];
    if (new_element.distance < parent.distance) {
      heap->arr[position] = parent;
      position = parent_position;
      continue;
    }
    break;
  }
  heap->arr[position] = new_element;
}

HeapNode heappop(Heap* heap) {
  if (heap->length == 0) {
    printf("Popping from an empty heap\n");
    return (HeapNode) {-1 , -1};
  }

  int left_child_index, right_child_index, smallest_child_index, parent_index;
  HeapNode temp;

  HeapNode smallest = heap->arr[0];
  HeapNode last_node = heap->arr[heap->length - 1];
  heap->length--;

  if (heap->length > 0) {
    heap->arr[0] = last_node;

    parent_index = 0;

    while (true) {
      left_child_index = 2 * parent_index + 1;
      right_child_index = 2 * parent_index + 2;
      smallest_child_index = parent_index;

      if ((left_child_index < heap->length) && (heap->arr[left_child_index].distance < heap->arr[smallest_child_index].distance)) 
        smallest_child_index = left_child_index;

      if ((right_child_index < heap->length) && (heap->arr[right_child_index].distance < heap->arr[smallest_child_index].distance)) 
        smallest_child_index = right_child_index;

      if (smallest_child_index != parent_index) {
        temp = heap->arr[parent_index];
        heap->arr[parent_index] = heap->arr[smallest_child_index];
        heap->arr[smallest_child_index] = temp;
        parent_index = smallest_child_index;
      } else {
        break;
      }
    }
  }
  return smallest;
}

TopKHeap* create_topkheap(int k) {
    TopKHeap* heap = malloc(sizeof(TopKHeap));
    heap->length = 0;
    heap->max_size = k;
    heap->arr = calloc(k, sizeof(TopKHeapNode));

    return heap;
}

void topkheappush(TopKHeap* heap, int u, int v, int distance) {
  if (heap->length == heap->max_size) {
    heap->arr = realloc(heap->arr, 2 * (heap->max_size) * sizeof(TopKHeap));
    heap->max_size = heap->max_size * 2;
  }

  heap->length++;
  heap->arr[heap->length - 1] = (TopKHeapNode) {u, v, distance};

  TopKHeapNode new_element, parent;
  int start, position, parent_position;

  new_element = heap->arr[heap->length - 1];
  start = 0; 
  position = heap->length - 1;

  while (position > start) {
    parent_position = (position - 1) >> 1;
    parent = heap->arr[parent_position];
    if (new_element.distance < parent.distance) {
      heap->arr[position] = parent;
      position = parent_position;
      continue;
    }
    break;
  }
  heap->arr[position] = new_element;
}

TopKHeapNode topkheappop(TopKHeap* heap) {
  if (heap->length == 0) {
    printf("Popping from an empty heap\n");
    return (TopKHeapNode) {-1 , -1, -1};
  }

  int left_child_index, right_child_index, smallest_child_index, parent_index;
  TopKHeapNode temp;

  TopKHeapNode smallest = heap->arr[0];
  TopKHeapNode last_node = heap->arr[heap->length - 1];
  heap->length--;

  if (heap->length > 0) {
    heap->arr[0] = last_node;

    parent_index = 0;

    while (true) {
      left_child_index = 2 * parent_index + 1;
      right_child_index = 2 * parent_index + 2;
      smallest_child_index = parent_index;

      if ((left_child_index < heap->length) && (heap->arr[left_child_index].distance < heap->arr[smallest_child_index].distance)) 
        smallest_child_index = left_child_index;

      if ((right_child_index < heap->length) && (heap->arr[right_child_index].distance < heap->arr[smallest_child_index].distance)) 
        smallest_child_index = right_child_index;

      if (smallest_child_index != parent_index) {
        temp = heap->arr[parent_index];
        heap->arr[parent_index] = heap->arr[smallest_child_index];
        heap->arr[smallest_child_index] = temp;
        parent_index = smallest_child_index;
      } else {
        break;
      }
    }
  }
  return smallest;
}