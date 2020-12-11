#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define RAND_MAX = 32767

typedef struct Node {
  struct Node* pNext;
  struct Data* pData;
} listNode;

typedef struct Data {
  char Bez[50];
  double Preis;
} struDataElm;

listNode* createList(int);
listNode* sortList(listNode*, bool);
void outputList(listNode*);

int main() {
  listNode *pStart = NULL;
  int AnzahlElm = 6;
  // Liste erstellen
  pStart = createList(AnzahlElm);
  pStart = sortList(pStart, false);
  // Ausgabe
  outputList(pStart);
  return 0;
}

listNode*createList(int anzahl) {
  srand((unsigned)time(NULL));
  listNode *pNew = NULL;
  listNode *pFirst = NULL;
  listNode *pLast = NULL;
  for (int iElm = 0; iElm < anzahl; iElm++) {
    // Element erstellen und initialisieren
    pNew = (listNode*) malloc(sizeof(listNode));
    if (pNew == NULL) exit(-1);
    pNew->pNext = NULL;
    pNew->pData = (struDataElm*)malloc(sizeof(struDataElm));
    pNew->pData->Preis = rand() % 100;
    // Neues Element an Liste anf�gen
    if (pFirst == NULL) pFirst = pNew;
    if (pLast != NULL) pLast->pNext = pNew;
    pLast = pNew;
  }
  return pFirst;
}

listNode* sortList(listNode* firstNode, bool ascending) {
  listNode* previousNode = NULL;
  listNode* currentNode = firstNode;
  do {
    double currentPrice = currentNode->pData->Preis;
    double nextPrice = currentNode->pNext->pData->Preis;
    if ((currentPrice > nextPrice && ascending) || currentPrice < nextPrice && !ascending) {
      if (previousNode != NULL) {
        previousNode->pNext = currentNode->pNext;
      } else {
        firstNode = currentNode->pNext;
      }
      listNode* temp = currentNode->pNext->pNext;
      currentNode->pNext->pNext = currentNode;
      currentNode->pNext = temp;
      currentNode = firstNode;
      previousNode = NULL;
    } else {
      previousNode = currentNode;
      currentNode = currentNode->pNext;
    }
  } while (currentNode->pNext != NULL);
  return firstNode;
}

void outputList(listNode*pFirst) {
  for (listNode*pElm = pFirst; pElm != NULL; pElm = pElm->pNext)
    printf("Preis=%lf\n", pElm->pData->Preis);
}