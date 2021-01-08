#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#define RAND_MAX = 32767
#ifdef __linux__
#define strcpy_s strcpy;
#endif

const int N_COMMANDS = 5;

const char *COMMANDS[] = {
        "create", "sort", "print", "delete", "exit"
};

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

void printIntro();

void getInput(char *, int);

ListNode *executeCommand(ListNode *, char);

ListNode *execListCreationWizard(ListNode *);

ListNode *execListSortingWizard(ListNode *);

int countElements(ListNode *);

void deleteList(ListNode *);

int main() {
  ListNode *list = NULL;
  char text[50];
  do {
    printIntro();
    getInput(text, sizeof(text));
    list = executeCommand(list, text[0]);
  } while (list != 0);
  return 0;
}

void printIntro() {
  printf("What would you like to do?\n");
  for (int i = 0; i < N_COMMANDS; i++) {
    printf("%d\t%s\n", i, COMMANDS[i]);
  }
}

void getInput(char *text, int size) {
  fgets(text, size, stdin);
  for (int i = strlen(text) - 1; text[i] == '\n'; i--) text[i] = '\0';
}

int countElements(ListNode *firstNode) {
  int count = 1;
  ListNode *cNode = firstNode;
  if (firstNode != NULL) {
    while (cNode->pNext != NULL) {
      count++;
      cNode = cNode->pNext;
    }
  }
  return count;
}

ListNode *executeCommand(ListNode *list, char input) {
  switch (input) {
    case '0':
      list = execListCreationWizard(list);
      break;
    case '1':
      list = execListSortingWizard(list);
      break;
    case '2':
      outputList(list);
      break;
    case '3':
      deleteList(list);
      break;
    case '4':
    default:
      deleteList(list);
      return 0;
  }

  return list;
}

ListNode *execListSortingWizard(ListNode *list) {
  printf("List sorting. Please input\n0\tfor ascending\n1\tfor descending\n");
  char text[100];
  getInput(text, sizeof(text));
  bool ascending = text[0] == '0' ? true : false;
  list = sortList(list, ascending);

  return list;
}

ListNode *execListCreationWizard(ListNode *currList) {
  if (currList != NULL) {
    printf("There exists a list already!\n");
    deleteList(currList);
  }
  ListNode *list = NULL;

  printf("List creation. Please input the desired number of items:\n");
  char text[100];
  getInput(text, sizeof(text));
  int nItems = atoi(text);

  if (nItems <= 0) {
    printf("Input invalid. Please enter a number bigger than 0.\n");
  } else {
    list = createList(nItems);
  }

  return list;
}

char generateRandomChar() {
  char fromChar = 'A';
  char toChar = 'Z';
  return (rand() % (toChar - fromChar)) + fromChar;
}

void generateArticleName(char* name) {
  *name = generateRandomChar();
  *(++name) = generateRandomChar();
  *(++name) = generateRandomChar();
  *(++name) = '\0';
}

ListNode* createList(int anzahl) {
  srand((unsigned)time(NULL));
  ListNode* pNew = NULL;
  ListNode* pFirst = NULL;
  ListNode* pLast = NULL;
  for (int i = 0; i < anzahl; i++) {
    // Element erstellen und initialisieren
    pNew = (ListNode *) malloc(sizeof(ListNode));
    if (pNew == NULL) exit(-1);
    pNew->pNext = NULL;
    pNew->pArticle = (Article*)malloc(sizeof(Article));
    generateArticleName(pNew->pArticle->name);
    if (pNew->pArticle) {
      pNew->pArticle->price = rand() % 100;
    }
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
  printf("The list contains %d elements\n", countElements(pFirst));
  for (ListNode *p = pFirst; p != NULL; p = p->pNext)
    printf("Name: %s\nPrice=%lf\n\n", p->pArticle->name, p->pArticle->price);
}

void deleteList(ListNode *firstNode) {
  printf("The list will be deleted...\n");
  ListNode *pCurr = firstNode;
  ListNode *pNext = firstNode->pNext;

  while (pNext != NULL) {
    free(pCurr->pArticle);
    free(pCurr);
    pCurr = pNext;
    pNext = pNext->pNext;
  }
  free(pCurr->pArticle);
  free(pCurr);
}