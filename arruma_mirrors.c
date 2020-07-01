#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXMIRROR 30
#define DESTINO "/etc/pacman.d/mirrorlist"
#define TEMP "/tmp/src.txt"

typedef struct {
  int dia, mes, ano;
}s_data;

int lerMirrors(char **mirrors, s_data *data) {
  char aux[80];
  int i;
  FILE *arch = fopen(TEMP, "r");
  if (arch == NULL) return 0;

  for(i = 0; i < 2; i++) {
    fscanf(arch, "%*[^\n]%*r");
  }
  fscanf(arch, "%*c%*c%*c%*s %*s %d-%d-%d%*r", &data->ano, &data->mes, &data->dia);
  for(i = 0; i < 3; i++) {
    fscanf(arch, "%*[^\n]%*r");
  }

  for(i = 0; !feof(arch); i++) {
    fscanf(arch, "%[^\n]%*r", aux);
    mirrors[i] = (char*)malloc(sizeof(char) * strlen(aux));
    strcpy(mirrors[i], aux + 1);
  }
  return i;
}

int escreveMirrorList(char **mirrors, int tam, s_data data) {
  FILE *arch = fopen(DESTINO, "w");
  if (arch == NULL) return 0;

  fprintf(arch, "#---------------------------------#\n");
  fprintf(arch, "# ATUALIZADO DIA = %02d/%02d/%d     #\n", data.dia, data.mes, data.ano);
  fprintf(arch, "# ARQUIVO GERADO PELO MEU SCRIPT! #\n");
  fprintf(arch, "# Por: Victor                     #\n");
  fprintf(arch, "#---------------------------------#\n\n");

  for(int i = 0; i < tam; i++) {
    fprintf(arch, "%s\n", mirrors[i]);
  }
  return 1;
}

void testaLeitura (int *tam, char **mirrors, s_data *data) {
  *tam = lerMirrors(mirrors, data);
  if(tam == 0) printf("Falha na leitura");
}

void testaEscrita (int tam, char **mirrors, s_data data) {
  if(!escreveMirrorList(mirrors, tam, data)) printf("Falha na escrita\nTente rodar com sudo\n");
}

int main () {
  char **mirrors;
  int mirrors_usados;
  s_data data;

  mirrors = (char **)malloc(sizeof(char*) * MAXMIRROR);
  testaLeitura(&mirrors_usados, mirrors, &data);
  mirrors = realloc(mirrors, sizeof(char*) * mirrors_usados);
  testaEscrita(mirrors_usados, mirrors, data);

  return 0;
}
