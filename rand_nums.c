#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

int *create_rand_nums(int num_elements)
{
  srand(time(NULL));
  int *rand_nums = (int *)malloc(sizeof(int) * num_elements);
  assert(rand_nums != NULL);
  int i;
  for (i = 0; i < num_elements; i++)
  {
    rand_nums[i] = rand() % 100; //numeros aleatórios até 100
  }
  return rand_nums;
}

int main(int argc, char const *argv[])
{

  int number_of_elements = atoi(argv[1]);

  int *rand_nums = create_rand_nums(number_of_elements);

  printf("number_of_elements: %d \n", number_of_elements);

  // confere os numeros aleatorios
  for (size_t i = 0; i < number_of_elements; i++)
  {
    printf("rand_num: %d \n", rand_nums[i]);
  }

  return 0;
}
