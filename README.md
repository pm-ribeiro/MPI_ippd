# Cálculo média, maior e menor - MPI

Trabalho proposto na disciplina de Introdução ao processamento paralelo e distribuído.
Universidade Federal de Pelotas - 2020/2

### Descrição:

Implementação de um programa usando MPI que calcula a média, menor e maior valor de um conjunto de inteiros.

O programa recebe como parâmetros o tamanho de um vetor, é criado um um vetor de inteiros, no tamanho informado e o vetor é inicializado com valores aletórios.

Ao final devem ser impressos, como resultado: o menor e o maior valor neste vetor e também a média dos valores contidos no vetor.

- Pré requisitos: MPI instalado

### Instruções de execução

Na linha de comando

Compilação

```bash
$ make -f Makefile
```

Execução

```bash
$ mpirun -np <qtd_de_processos> ./main <tamanho_do_vetor>
```
