#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXMIRROR 30
#define DESTINO "/etc/pacman.d/mirrorlist"
#define TEMP "/tmp/src.txt"

int lerMirrors(char **mirrors) {
  char aux[80];
  int i;
  FILE *arch = fopen(TEMP, "r");
  if (arch == NULL) return 0;

  for(i = 0; i < 5; i++) {
    fscanf(arch, "%*[^\n]%*r");
  }

  for(i = 0; !feof(arch); i++) {
    fscanf(arch, "%[^\n]%*r", aux);
    mirrors[i] = (char*)malloc(sizeof(char) * strlen(aux));
    strcpy(mirrors[i], aux + 1);
  }
  return i;
}

int escreveMirrorList(char **mirrors, int tam) {
  FILE *arch = fopen(DESTINO, "w");
  if (arch == NULL) return 0;

  fprintf(arch, "#ARQUIVO GERADO PELO MEU SCRIPT!\n#VICTOR\n");
  for(int i = 0; i < tam; i++) {
    fprintf(arch, "%s\n", mirrors[i]);
  }
  return 1;
}

void testaLeitura (int *tam, char **mirrors) {
  *tam = lerMirrors(mirrors);
  if(!tam) printf("Falha na leitura");
}

void testaEscrita (int tam, char **mirrors) {
  if(!escreveMirrorList(mirrors, tam)) printf("Falha na escrita\nTente rodar com sudo\n");
}

int main () {
  char **mirrors;
  int mirrors_usados;

  mirrors = (char **)malloc(sizeof(char*) * MAXMIRROR);
  testaLeitura(&mirrors_usados, mirrors);
  mirrors = realloc(mirrors, sizeof(char*) * mirrors_usados);
  testaEscrita(mirrors_usados, mirrors);

  return 0;
}
