#include <stdio.h>
#include <math.h>

void fillVet(double vetor[], int n){
  int i;
  for(i = 0; i < n; i++){
    printf("Insira o %d elemento: ", i + 1);
    scanf("%lf", &vetor[i]);
  }
}

double calcMedia(double vetor[], int n){
  int i;
  double sum = 0;
  for(i = 0; i < n; i++){
    sum = sum + vetor[i];
  }
  return sum / n;
}

double calcVariancia(double vetor[], int n){
  int i;
  double media = calcMedia(vetor, n), sum = 0, temp;
  for(i = 0; i < n; i++){
    temp = (vetor[i] - media) * (vetor[i] - media);
    sum = sum + temp;
  }
  return sum / n;
}

double calcVariancia2(double vetor[], int n){
  int i;
  double media = calcMedia(vetor, n), sum = 0, temp;
  for(i = 0; i < n; i++){
    temp = (vetor[i] - media) * (vetor[i] - media);
    sum = sum + temp;
  }
  return sum / (n - 1);
}

void ordenar(double vet[], int n){
  int i, j;
  int temp = 0;
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if(vet[i] > vet[j]){
        temp = vet[i];
        vet[i] = vet[j];
        vet[j] = temp;
      }
    }
  }
}

double calcMediana(double vetor[], int n){
  if(n % 2 == 0){
    return (vetor[n / 2] + vetor[(n / 2) - 1]) / 2;
  }else{
    return vetor[n / 2];
  }
}

int countOcurrences(double vetor[], double x, int n){
  int i;
  int soma = 0;
  for(i = 0; i < n; i++){
    if(vetor[i] == x){
      soma++;
    }
  }
  return soma;
}
int moreAppearences(double vetor[], int n){
    int i, x, top = 0;
    for(i = 0; i < n; i++){
      x = countOcurrences(vetor, vetor[i], n);
      if(x > top){
        top = x;
      }
    }
    return top;
}

void calcModa(double vetor[], int n){
  int i, count = 1, size = moreAppearences(vetor, n);
  if(size == 1){
    printf("Moda: nao existe\n");
  }else{
    for(i = 0; i < n; i++){
      if(countOcurrences(vetor, vetor[i], n) == size){
        printf("Moda %d: %.2lf\n", count, vetor[i]);
        count++;
        i = i + size - 1;
      }
    }
  }
}

double findThirdQ(double vetor[], int n){
  int i;
  double tempvet[200];
  if(n % 2 == 0){
    for(i = n / 2; i < n; i++){
      tempvet[i - (n / 2)] = vetor[i];
    }
  }else{
    for(i = (n / 2); i < n; i++){
      tempvet[i - (n / 2)] = vetor[i + 1];
    }
  }
  return calcMediana(tempvet, n / 2);
}

void calcBoxPlot(double vetor[], int n){
  double firstQ = calcMediana(vetor, n / 2);
  double thirdQ = findThirdQ(vetor, n);
  printf("[BOXPLOT]\n");
  printf("Min: %.2lf\n", vetor[0]);
  printf("Q1: %.2lf\n", firstQ);
  printf("Q2: %.2lf\n", calcMediana(vetor, n));
  printf("Q3: %.2lf\n", thirdQ);
  printf("Max: %.2lf\n", vetor[n - 1]);
}

double calcAssimetria(double vetor[], int n){
  double assimetria = 3 * (calcMedia(vetor, n) - calcMediana(vetor, n)) / sqrt(calcVariancia(vetor, n));
  return assimetria;
}

void calcEscoreZ(double vetor[], int n){
  int i;
  printf("[ESCORE-Z]\n");
  for(i = 0; i < n; i++){
    printf("Escore-Z de %.2lf: %.2lf\n", vetor[i], (vetor[i] - calcMedia(vetor, n)) / sqrt(calcVariancia(vetor, n)));
  }
}

double calcEscore(double vetor[], int n, double x){
  return (x - calcMedia(vetor, n)) / sqrt(calcVariancia(vetor, n));
}

void showData(double vetor[], int n){
  printf("\n");
  printf("[INFO]\n");
  printf("Media: %.2lf\n", calcMedia(vetor, n));
  printf("Mediana: %.2lf\n", calcMediana(vetor, n));
  calcModa(vetor, n);
  printf("Amplitude: %.2lf\n", vetor[n - 1] - vetor[0]);
  printf("Amplitude interquartil: %.2lf\n", findThirdQ(vetor, n) - calcMediana(vetor, n / 2));
  printf("Variancia: %.2lf\n", calcVariancia(vetor, n));
  printf("Desvio Padrao: %.2lf\n", sqrt(calcVariancia(vetor, n)));
  printf("Variancia N-1: %.2lf\n", calcVariancia2(vetor, n));
  printf("Desvio Padrao N-1: %.2lf\n", sqrt(calcVariancia2(vetor, n)));
  printf("Coeficiente de variacao: %.2lf%%\n", sqrt(calcVariancia(vetor, n)) / calcMedia(vetor, n) * 100);
  printf("Coeficiente de assimetria de Pearson: %.2lf\n", calcAssimetria(vetor, n));
  printf("\n");
  calcBoxPlot(vetor, n);
  printf("\n");
  calcEscoreZ(vetor, n);
  printf("\n");
}


double calcPercentil(double vetor[], int n, int percentil){
  double position, dif, start, end;
  position = (double)(n + 1) * (double)percentil / 100;
  if(position == 0){
    return 0;
  }
  else if(position < 1){
    return vetor[0];
  }else if(position > n){
    return vetor[n - 1];
  }
  else if(floor(position) == position){
    return vetor[(int)position - 1];
  }else{
    start = vetor[(int)floor(position) - 1];
    end = vetor[(int)floor(position)];
    dif = position - floor(position);
    return start + dif * (end - start);
  }
  return 0;
}

/*
double calcPercentil(double vetor[], int n, int percentil){
  int x = percentil / 100 * n;
  if(floor(x) == x){
    return (vetor[x] + vetor[x + 1]) / 2;
  }
  return vetor[(int)floor(x) + 1];
}
*/

void calcCheby(double vetor[], int n){
  double value, escore, temp, result;
  printf("Insira um dos limites: ");
  scanf("%lf", &value);
    escore = calcEscore(vetor, n, value);
    if(escore > 1 || escore < -1){
      temp = 1 / (escore * escore);
      result = 1 - temp;
      printf("\nResultado do Teorema de Chebyshev para %.2lf: %.2lf%%\n", value, result * 100);
    }else{
      printf("Valor invalido\n");
    }
}

void showTable(double vetor[], int n){
  printf("\n");
  printf("[TABELA]\n");
  printf("     Classe     | Freq. Absoluta | Freq. Relativa |   Freq. Percentual\n");
  double amplitude, k, relativa;
  int i, j, tamanho, sum;
  amplitude = vetor[n - 1] - vetor[0];
  k = (double)sqrt(n);
  tamanho = (int)(amplitude / k);
  for(i = vetor[0]; i <= vetor[n - 1]; i = i + tamanho + 2){
    sum = 0;
    printf(" %4d |--| %4d | ", i, i + tamanho + 1);
    for(j = 0; j < n; j++){
      if(vetor[j] >= i && vetor[j] <= i + tamanho + 1){
        sum++;
      }
    }
    printf("       %d       |", sum);
    relativa = (double)sum / (double)n;
    printf("      %.2lf      | ", relativa);
    relativa = round(relativa * 100);
    printf("       %d%%", (int)relativa);
    printf("\n");
  }
  printf("OBS: todos os valores no formato X,5 na freq relativa sao arredonados\npra cima, tendo assim uma pequena margem de erro\n");
}

int main()
{
  int n, option, optcheby, percentil;
  double vetor[200];
  printf("Insira a quantidade de elementos: ");
  scanf("%d", &n);
  fillVet(vetor, n);
  ordenar(vetor, n);
  showTable(vetor, n);
  showData(vetor, n);
  while(1){
    printf("Digite 0 para sair\n");
    printf("Digite 1 para calcular percentil\n");
    printf("Digite 2 para Teorema de ChebyShev\n");
    scanf("%d", &option);
    if(option == 0){
      return 0;
    }else if(option == 1){
      printf("Insira o percentil a ser calculado: ");
      scanf("%d", &percentil);
      printf("\nP%d = %.2lf\n\n", percentil, calcPercentil(vetor, n, percentil));
    }else if(option == 2){
      calcCheby(vetor, n);
      printf("\n");
    }
  }
  return 0;
}
