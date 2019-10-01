#include "mergesort.h"

#include <stdlib.h>

bool needs_sorting(int range_size) {
  return range_size >= 2;
}

void merge_ranges(int * values, int start_index, int midpoint, int end_index) {
  //declare the variables we will need
  const int range_size = end_index - start_index;
  int * destination = (int * ) calloc(range_size, sizeof(int));
  int first_index = start_index;
  int second_index = midpoint;
  int copy_index = 0;

  //shuffle greatest off each half into destination in a loop
  while (first_index < midpoint && second_index < end_index) {
    if (values[first_index] < values[second_index]) {
      destination[copy_index] = values[first_index];
      first_index++;
    } else {
      destination[copy_index] = values[second_index];
      second_index++;
    }
    copy_index++;
  }
  //copy remaining in first half
  while (first_index < midpoint) {
    destination[copy_index] = values[first_index];
    copy_index++;
    first_index++;
  }
  //copy remaining in second half
  while (second_index < end_index) {
    destination[copy_index] = values[second_index];
    copy_index++;
    second_index++;
  }
  for (int i = 0; i < range_size; i++) {
    values[i + start_index] = destination[i];
  }
  free(destination);
}

void mergesort_range(int * values, int start_index, int end_index) {
  const int range_size = end_index - start_index;
  if (needs_sorting(range_size)) {
    int midpoint = (start_index + end_index) / 2;
    mergesort_range(values, start_index, midpoint);
    mergesort_range(values, midpoint, end_index);
    merge_ranges(values, start_index, midpoint, end_index);

  }
}

void mergesort(int size, int * values) {
  // This obviously doesn't actually do any *sorting*, so there's
  // certainly work still to be done.
  mergesort_range(values, 0, size);

}
