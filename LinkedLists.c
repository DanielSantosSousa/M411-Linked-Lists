#include <stdio.h>
#include <stdlib.h>
typedef struct Elm {
  int Nr;
  struct Elm* pNext;
} struElm;
struElm* CreateList(int Anzahl) {
  struElm* pNew = NULL;
  struElm* pFirst = NULL;
  struElm* pLast = NULL;
  for (int iElm = 0; iElm < Anzahl; iElm++) {
    // Element erstellen und initialisieren
    pNew = (struElm*)malloc(sizeof(struElm));
    if (pNew == NULL) exit(-1);
    pNew->Nr = iElm + 1;
    pNew->pNext = NULL;
    // Neues Element an Liste anfügen
    if (pFirst == NULL) pFirst = pNew;
    if (pLast != NULL) pLast->pNext = pNew;
    pLast = pNew;
  }
  return pFirst;
}
void OutputList(struElm* pFirst) {
  for (struElm* pElm = pFirst; pElm != NULL; pElm = pElm->pNext)
    printf("Nr=%i\n", pElm->Nr);
}
int main() {
  struElm* pStart = NULL;
  int AnzahlElm = 10;
  // Liste erstellen
  pStart = CreateList(AnzahlElm);
  // Ausgabe
  OutputList(pStart);
  system("pause");
  return 0;
}