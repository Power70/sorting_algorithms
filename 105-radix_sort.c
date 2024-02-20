#include <stdio.h>
#include <stdlib.h>

int getMax(int arr[], int n) {
  int mx = arr[0];
  int i;
  for (i = 1; i < n; i++)
    if (arr[i] > mx)
      mx = arr[i];
  return mx;
}

void countSort(int arr[], int n, int exp) {
  // static: fixed size, malloc: dynamic allocation
  // static int output[100]; /* example of fixed size */
  int *output = (int *)malloc(n * sizeof(int)); /* example of dynamic allocation */
  if (output == NULL) {
    // handle memory allocation failure
    return;
  }

  int i, count[10] = {0};

  // store count of occurrences in count[]
  for (i = 0; i < n; i++)
    count[(arr[i] / exp) % 10]++;

  // change count[i] so that count[i] now contains actual
  // position of this digit in output array
  for (i = 1; i < 10; i++)
    count[i] += count[i - 1];

  // build the output array
  for (i = n - 1; i >= 0; i--) {
    output[count[(arr[i] / exp) % 10] - 1] = arr[i];
    count[(arr[i] / exp) % 10]--;
  }

  // copy the output array to arr[], so that arr[] now
  // contains sorted numbers according to current digit
  for (i = 0; i < n; i++)
    arr[i] = output[i];

  /* if using dynamic allocation, free memory */
  free(output);
}

void radixSort(int arr[], int n) {
  // Modified to use the getMax function
  int m = getMax(arr, n);

  int exp;
  for (exp = 1; m / exp > 0; exp *= 10)
    countSort(arr, n, exp);
}

void print(int arr[], int n) {
  int i;
  for (i = 0; i < n; i++)
    printf("%d ", arr[i]);
  printf("\n");
}

int main() {
  int numOfElements = 0, i;
  printf("Enter number of elements in the array > \n");
  scanf("%d", &numOfElements);

  // static: fixed size, malloc: dynamic allocation
  // static int arr[100]; /* example of fixed size */
  int *arr = (int *)malloc(numOfElements * sizeof(int)); /* example of dynamic allocation */
  if (arr == NULL) {
    // handle memory allocation failure
    return 1;
  }

  for (i = 0; i < numOfElements; i++) {
    printf("Enter element %d > ", i + 1);
    scanf("%d", &arr[i]);
  }

  radixSort(arr, numOfElements);
  printf("Sorted array: ");
  print(arr, numOfElements);

  /* if using dynamic allocation, free memory */
  free(arr);

  return 0;
}

