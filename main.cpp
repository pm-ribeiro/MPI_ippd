#include <stdio.h>
#include <ctime>   // For time()
#include <cstdlib> // For srand() and rand()
#include <assert.h>
#include <math.h>
#include <mpi.h>

int *create_rand_nums(int num_elements)
{
  printf("- Vetor de aleatorios -\n");
  int *rand_nums = (int *)malloc(sizeof(int) * num_elements);
  assert(rand_nums != NULL);
  int i;
  for (i = 0; i < num_elements; i++)
  {
    rand_nums[i] = 1 + rand() % 100; //numeros aleatórios até 100
    printf("rand_nums[%d] = %d\n", i, rand_nums[i]);
  }
  printf("-----------------------------------------------\n");
  return rand_nums;
}

float compute_avg(int *array, int num_elements)
{
  float avg = 0;
  int sum = 0;
  int i;
  for (i = 0; i < num_elements; i++)
  {
    sum += array[i];
  }

  avg = sum / num_elements;

  // printf("Media parcial %f\n", avg);

  return avg;
}

float max_value(int *array, int num_elements)
{
  int i;
  int max = array[0];
  for (i = 0; i < num_elements; i++)
  {
    if (array[i] > max)
    {
      max = array[i];
    }
  }

  // printf("Maior parcial %d\n", max);

  return max;
}

float min_value(int *array, int num_elements)
{
  int i;
  int min = array[0];
  for (i = 0; i < num_elements; i++)
  {
    if (array[i] < min)
    {
      min = array[i];
    }
  }

  // printf("Menor parcial %d\n", min);

  return min;
}

int main(int argc, char const *argv[])
{
  int number_of_elements = atoi(argv[1]);

  int max, min;
  int maxF, minF;

  float media, mediaF;

  srand(time(NULL));
  MPI_Init(NULL, NULL);

  int myRank, worldSize;

  MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
  MPI_Comm_size(MPI_COMM_WORLD, &worldSize); //total of ranks in the comunicator

  // checa se a quantidade de aleatorios pode ser dividida pela quantidade de processos

  if (number_of_elements % worldSize != 0)
  {
    if (myRank == 0)
    {
      printf("A quantidade de números aleatórios deve ser divisivel pela quantidade de processos, por exemplo: np = 2, ran_num = 4.\nTente novamente. \n");
    }
    MPI_Finalize();
    return 0;
  }

  int number_elements_per_proc = number_of_elements / worldSize;

  int *vet = (int *)malloc(sizeof(int) * number_of_elements); // vetor de dados no rank = 0

  if (myRank == 0)
  {
    printf("Qtd de processos: %d \n", worldSize);
    printf("Qtd num. aleatorios: %d \n", number_of_elements);
    printf("-----------------------------------------------\n");
    vet = create_rand_nums(number_of_elements);
  }

  int *vetR = (int *)malloc(sizeof(int) * number_elements_per_proc);

  // Espalha os numeros aleatorios para todos os processos
  MPI_Scatter(vet, number_elements_per_proc, MPI_INT, vetR, number_elements_per_proc, MPI_INT, 0, MPI_COMM_WORLD);

  media = compute_avg(vetR, number_elements_per_proc);
  min = min_value(vetR, number_elements_per_proc);
  max = max_value(vetR, number_elements_per_proc);

  MPI_Reduce(&media, &mediaF, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
  MPI_Reduce(&max, &maxF, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
  MPI_Reduce(&min, &minF, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);

  if (myRank == 0)
  {
    mediaF = mediaF / worldSize;
    printf("Média = %.2f\n", mediaF);
    printf("Maior numero = %d\n", maxF);
    printf("Menor numero = %d\n", minF);
  }

  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Finalize();

  return 0;
}
