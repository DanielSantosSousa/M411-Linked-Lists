#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define RAND_MAX = 32767

typedef struct Node {
    struct Node *pNext;
    struct Data *pArticle;
} ListNode;

typedef struct Data {
    char name[50];
    double price;
} Article;

ListNode *createList(int);

ListNode *sortList(ListNode *, bool);

void outputList(ListNode *);

int main() {
  ListNode *pStart = NULL;
  int nItems = 6;
  // Liste erstellen
  pStart = createList(nItems);
  pStart = sortList(pStart, false);
  // Ausgabe
  outputList(pStart);
  return 0;
}

ListNode *createList(int anzahl) {
  srand((unsigned) time(NULL));
  ListNode *pNew = NULL;
  ListNode *pFirst = NULL;
  ListNode *pLast = NULL;
  for (int i = 0; i < anzahl; i++) {
    // Element erstellen und initialisieren
    pNew = (ListNode *) malloc(sizeof(ListNode));
    if (pNew == NULL) exit(-1);
    pNew->pNext = NULL;
    pNew->pArticle = (Article *) malloc(sizeof(Article));
    pNew->pArticle->price = rand() % 100;
    // Neues Element an Liste anf�gen
    if (pFirst == NULL) pFirst = pNew;
    if (pLast != NULL) pLast->pNext = pNew;
    pLast = pNew;
  }
  return pFirst;
}

ListNode *sortList(ListNode *pFirstNode, bool ascending) {
  ListNode *pPreviousNode = NULL;
  ListNode *pCurrentNode = pFirstNode;
  do {
    double currentPrice = pCurrentNode->pArticle->price;
    double nextPrice = pCurrentNode->pNext->pArticle->price;
    if ((currentPrice > nextPrice && ascending) || currentPrice < nextPrice && !ascending) {
      if (pPreviousNode != NULL) {
        pPreviousNode->pNext = pCurrentNode->pNext;
      } else {
        pFirstNode = pCurrentNode->pNext;
      }
      ListNode *temp = pCurrentNode->pNext->pNext;
      pCurrentNode->pNext->pNext = pCurrentNode;
      pCurrentNode->pNext = temp;
      pCurrentNode = pFirstNode;
      pPreviousNode = NULL;
    } else {
      pPreviousNode = pCurrentNode;
      pCurrentNode = pCurrentNode->pNext;
    }
  } while (pCurrentNode->pNext != NULL);
  return pFirstNode;
}

void outputList(ListNode *pFirst) {
  for (ListNode *p = pFirst; p != NULL; p = p->pNext)
    printf("price=%lf\n", p->pArticle->price);
}