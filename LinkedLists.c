#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  struct Elm* pNext;
  struct Data* pData;
} listNode;

typedef struct Data {
  char Bez[50];
  double Preis;
} struDataElm;


listNode*CreateList(int Anzahl) {
  listNode *pNew = NULL;
  listNode *pFirst = NULL;
  listNode *pLast = NULL;
  for (int iElm = 0; iElm < Anzahl; iElm++) {
    // Element erstellen und initialisieren
    pNew = (listNode*) malloc(sizeof(listNode));
    if (pNew == NULL) exit(-1);
    pNew->pNext = NULL;
    pNew->pData = (struDataElm*)malloc(sizeof(struDataElm));
    // Neues Element an Liste anf�gen
    if (pFirst == NULL) pFirst = pNew;
    if (pLast != NULL) pLast->pNext = pNew;
    pLast = pNew;
  }
  return pFirst;
}

void OutputList(listNode*pFirst) {
  for (listNode*pElm = pFirst; pElm != NULL; pElm = pElm->pNext)
    printf("Nr=%i\n", &(pElm->pData)->Bez);
}

int main() {
  listNode *pStart = NULL;
  int AnzahlElm = 10;
  // Liste erstellen
  pStart = CreateList(AnzahlElm);
  // Ausgabe
  OutputList(pStart);
  return 0;
}