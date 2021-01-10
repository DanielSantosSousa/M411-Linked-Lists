#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#define RAND_MAX = 32767
#ifdef __linux__
#define strcpy_s strcpy;
#endif

const int N_COMMANDS = 4;

const char *COMMANDS[] = {
        "create", "sort", "print", "exit"
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
ListNode *executeCommand(ListNode *, char);
ListNode *execListCreationWizard(ListNode *);
ListNode *execListSortingWizard(ListNode *);
bool checkIfListEmpty(ListNode *);
int length(ListNode *);
char generateRandomChar();
void outputList(ListNode *);
void printIntro();
void getInput(char *, int);
void deleteList(ListNode *);
void mergeByPrice(ListNode **, ListNode **, ListNode **, ListNode **, bool);
void mergeByName(ListNode **, ListNode **, ListNode **, ListNode **, bool);
void mergeSort(ListNode **, bool, bool);
void generateArticleName(char *);

// Alex K.
int main() {
  ListNode *list = NULL;
  char text[50];
  do {
    printIntro();
    getInput(text, sizeof(text));
    list = executeCommand(list, text[0]);
  } while (list != NULL);
  return 0;
}

// Alex K.
void printIntro() {
  printf("What would you like to do?\n");
  for (int i = 0; i < N_COMMANDS; i++) {
    printf("%d\t%s\n", i, COMMANDS[i]);
  }
}

// Alex K. with help from Peter Kaufmann
// This method exists only because of the lack of a scanf/scanf_s under Linux
void getInput(char *text, int size) {
  fgets(text, size, stdin);
  for (int i = strlen(text) - 1; text[i] == '\n'; i--) text[i] = '\0';
}

// Alex K.
ListNode *executeCommand(ListNode *list, char input) {
  switch (input) {
    case '0':
      list = execListCreationWizard(list);
      break;
    case '1':
      if (!checkIfListEmpty(list)) {
        list = execListSortingWizard(list);
      }
      break;
    case '2':
      if (!checkIfListEmpty(list)) {
        outputList(list);
      }
      break;
    default:
      if (checkIfListEmpty(list)) {
        return NULL;
      } else {
        deleteList(list);
        return NULL;
      }
  }

  return list;
}

//Daniel S.S.
void mergeByName(ListNode **start1, ListNode **end1, ListNode **start2, ListNode **end2, bool ascending) {
  // Making sure that first node of second
  // list is higher.
  ListNode *temp = NULL;
  if (ascending) {
    if (strcmp((*start1)->pArticle->name, (*start2)->pArticle->name) > 0) {
      ListNode *temp = *start1;
      *start1 = *start2;
      *start2 = temp;
      temp = *end1;
      *end1 = *end2;
      *end2 = temp;
    }
    // Merging remaining nodes
    ListNode *astart = *start1, *aend = *end1;
    ListNode *bstart = *start2, *bend = *end2;
    ListNode *bendnext = (*end2)->pNext;
    while (astart != aend && bstart != bendnext) {
      if (strcmp(astart->pNext->pArticle->name, bstart->pArticle->name) > 0) {
        temp = bstart->pNext;
        bstart->pNext = astart->pNext;
        astart->pNext = bstart;
        bstart = temp;
      }
      astart = astart->pNext;
    }
    if (astart == aend)
      astart->pNext = bstart;
    else
      *end2 = *end1;
  } else {
    if (strcmp((*start1)->pArticle->name, (*start2)->pArticle->name) < 0) {
      ListNode *temp = *start1;
      *start1 = *start2;
      *start2 = temp;
      temp = *end1;
      *end1 = *end2;
      *end2 = temp;
    }
    // Merging remaining nodes
    ListNode *astart = *start1, *aend = *end1;
    ListNode *bstart = *start2, *bend = *end2;
    ListNode *bendnext = (*end2)->pNext;
    while (astart != aend && bstart != bendnext) {
      if (strcmp(astart->pNext->pArticle->name, bstart->pArticle->name) < 0) {
        temp = bstart->pNext;
        bstart->pNext = astart->pNext;
        astart->pNext = bstart;
        bstart = temp;
      }
      astart = astart->pNext;
    }
    if (astart == aend)
      astart->pNext = bstart;
    else
      *end2 = *end1;
  }
}

// Alex K.
int length(ListNode *currNode) {
  int count = 0;
  while (currNode != NULL) {
    currNode = currNode->pNext;
    count++;
  }
  return count;
}

//Daniel S.S.
void mergeByPrice(ListNode **start1, ListNode **end1, ListNode **start2, ListNode **end2, bool ascending) {
  // Making sure that first node of second
  // list is higher.
  ListNode *temp = NULL;
  if (ascending) {
    if ((*start1)->pArticle->price > (*start2)->pArticle->price) {
      ListNode *temp = *start1;
      *start1 = *start2;
      *start2 = temp;
      temp = *end1;
      *end1 = *end2;
      *end2 = temp;
    }
    // Merging remaining nodes
    ListNode *astart = *start1, *aend = *end1;
    ListNode *bstart = *start2, *bend = *end2;
    ListNode *bendnext = (*end2)->pNext;
    while (astart != aend && bstart != bendnext) {
      if (astart->pNext->pArticle->price > bstart->pArticle->price) {
        temp = bstart->pNext;
        bstart->pNext = astart->pNext;
        astart->pNext = bstart;
        bstart = temp;
      }
      astart = astart->pNext;
    }
    if (astart == aend)
      astart->pNext = bstart;
    else
      *end2 = *end1;
  } else {
    if ((*start1)->pArticle->price < (*start2)->pArticle->price) {
      ListNode *temp = *start1;
      *start1 = *start2;
      *start2 = temp;
      temp = *end1;
      *end1 = *end2;
      *end2 = temp;
    }
    // Merging remaining nodes
    ListNode *astart = *start1, *aend = *end1;
    ListNode *bstart = *start2, *bend = *end2;
    ListNode *bendnext = (*end2)->pNext;
    while (astart != aend && bstart != bendnext) {
      if (astart->pNext->pArticle->price < bstart->pArticle->price) {
        temp = bstart->pNext;
        bstart->pNext = astart->pNext;
        astart->pNext = bstart;
        bstart = temp;
      }
      astart = astart->pNext;
    }
    if (astart == aend)
      astart->pNext = bstart;
    else
      *end2 = *end1;
  }
}

//Daniel S.S.
void mergeSort(ListNode **head, bool ascending, bool mergedByPrice) {
  if (*head == NULL)
    return;
  ListNode *start1 = NULL, *end1 = NULL;
  ListNode *start2 = NULL, *end2 = NULL;
  ListNode *prevend = NULL;
  int len = length(*head);
  for (int gap = 1; gap < len; gap = gap * 2) {
    start1 = *head;
    while (start1) {
      // If this is first iteration
      bool isFirstIter = 0;
      if (start1 == *head)
        isFirstIter = 1;
      // First part for merging
      int counter = gap;
      end1 = start1;
      while (--counter && end1->pNext)
        end1 = end1->pNext;
      // Second part for merging
      start2 = end1->pNext;
      if (!start2)
        break;
      counter = gap;
      end2 = start2;
      while (--counter && end2->pNext)
        end2 = end2->pNext;
      // To store for next iteration.
      ListNode *temp = end2->pNext;
      // Merging two parts.
      if (mergedByPrice) {
        mergeByPrice(&start1, &end1, &start2, &end2, ascending);
      } else {
        mergeByName(&start1, &end1, &start2, &end2, ascending);
      }
      // Update head for first iteration, else
      // append after previous list
      if (isFirstIter)
        *head = start1;
      else
        prevend->pNext = start1;
      prevend = end2;
      start1 = temp;
    }
    prevend->pNext = start1;
  }
}

// Alex K.
ListNode *execListSortingWizard(ListNode *list) {
  printf("List sorting. Please input\n0\tfor ascending\n1\tfor descending\n");
  char text[100];
  getInput(text, sizeof(text));
  bool ascending = text[0] == '0' ? true : false;
  printf("List sorting. Please input\n0\tto sort by price\n1\tto sort by name\n");
  char textSortBy[100];
  getInput(textSortBy, sizeof(text));
  bool mergedByPrice = textSortBy[0] == '0' ? true : false;
  clock_t startTime = clock();
  ListNode **headRef = &list;
  mergeSort(headRef, ascending, mergedByPrice);
  clock_t endTime = clock();
  double duration = ((double) endTime - (double) startTime) / (double) CLOCKS_PER_SEC;
  printf("\nSorting took %.3lf seconds.\n", duration);
  return *headRef;
}

// Alex K.
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

// Daniel S. S.
char generateRandomChar() {
  char fromChar = 'A';
  char toChar = 'Z';
  return (rand() % (toChar - fromChar)) + fromChar;
}

// Daniel S. S.
void generateArticleName(char *name) {
  *name = generateRandomChar();
  *(++name) = generateRandomChar();
  *(++name) = generateRandomChar();
  *(++name) = '\0';
}

// Daniel S.S
ListNode *createList(int anzahl) {
  srand((unsigned) time(NULL));
  ListNode *pNew = NULL;
  ListNode *pFirst = NULL;
  ListNode *pLast = NULL;
  for (int i = 0; i < anzahl; i++) {
    // Create Elements
    pNew = (ListNode *) malloc(sizeof(ListNode));
    if (pNew == NULL) exit(-1);
    pNew->pNext = NULL;
    pNew->pArticle = (Article *) malloc(sizeof(Article));
    generateArticleName(pNew->pArticle->name);
    if (pNew->pArticle) {
      pNew->pArticle->price = rand() % 100;
    }
    // Add Elements to List
    if (pFirst == NULL) pFirst = pNew;
    if (pLast != NULL) pLast->pNext = pNew;
    pLast = pNew;
  }
  return pFirst;
}

// Alex K. & Daniel S. S.
void outputList(ListNode *pFirst) {
  printf("The list contains %d elements\n", length(pFirst));
  for (ListNode *p = pFirst; p != NULL; p = p->pNext)
    printf("Name: %s\nPrice=%lf\n\n", p->pArticle->name, p->pArticle->price);
}

// Alex K.
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

// Alex K.
bool checkIfListEmpty(ListNode *firstNode) {
  if (firstNode == NULL) {
    printf("No list exists! Create a list first.\n");
    return true;
  } else {
    return false;
  }
}