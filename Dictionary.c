//-----------------------------------------------------------------------------
// Dictionary.c
// Stephanie Shi (stjshi)
// CS 12B spring 15
// June 2, 2015
//
// Pa5 C version of Dictionary.java using Hash Table
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include "Dictionary.h"


// private types --------------------------------------------------------------

const int tableSize=101; //or some prime other than 101
// rotate_left()
// rotate the bits in an unsigned int
unsigned int rotate_left(unsigned int value, int shift) {
 int sizeInBits = 8*sizeof(unsigned int);
 shift = shift & (sizeInBits - 1);
 if ( shift == 0 )
 return value;
 return (value << shift) | (value >> (sizeInBits - shift));
}
// pre_hash()
// turn a string into an unsigned int
unsigned int pre_hash(char* input) {
 unsigned int result = 0xBAE86554;
 while (*input) {
 result ^= *input++;
 result = rotate_left(result, 5);
 }
 return result;
}
// hash()
// turns a string into an int in the range 0 to tableSize-1
int hash(char* key){
 return pre_hash(key)%tableSize;
}

// NodeObj
typedef struct NodeObj{
   char* key;
   char* value;
   struct NodeObj* next;
} NodeObj;

// Node
typedef NodeObj* Node;
Node findKey(Dictionary D, char* k);
// newNode()
// constructor of the Node type

Node newNode(char* k, char* v){
   Node N = malloc(sizeof(NodeObj));
   assert(N!= NULL);
   N->key = k;
   N->value = v;
   N->next = NULL;
   return(N);
}

// freeNode()
// destructor for the Node type
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

// DictionaryObj
typedef struct DictionaryObj{
   Node *table;
   Node head;
   int numItems;
} DictionaryObj;

Dictionary newDictionary(){
   Dictionary D = malloc(sizeof(DictionaryObj));
   D->table= calloc(D->table, tableSize);
   assert(D!=NULL);
   D->head = NULL;
   //D->tail = NULL;
   D->numItems = 0;
   for(int i = 0; i < tableSize; i++){
    D-> table[i] = NULL;
   }
   return D;
}

void freeDictionary(Dictionary* pD){
   if( pD!=NULL && *pD!=NULL ){
      free(*pD);
      *pD = NULL;
   }
}
// findKey()
// returns the Node containing key k in the subtree rooted at R, or returns
// NULL if no such Node exists

Node findKey(Dictionary D, char* k){
  int i = hash(k);
  Node H = D->table[i]; //fix if needed
  //find the unsigned int of char* k (x)
  //jump to table[x] and run a while loop to find if k already exists
  //set Node walker = table[x]->head;
  //walker = walker.next;
  //while (walker == NULL )

   //traverse through table[i]
   while(H= NULL){
      if(H->key = i){
        return H;
      }
      else{
        H = H->next;
      }
    }
    return NULL;
}

int isEmpty(Dictionary D){
   if( D==NULL ){
      return(1);
   }
   else{
    return(0);
   }
}

int size(Dictionary D){
   return sizeof(DictionaryObj);
}

char* lookup(Dictionary D, char* k){
 Node N;
   if( D==NULL ){
     return NULL;
   }
   else{
   N = findKey(D, k);
   return ( N==NULL ? NULL : N->value );
  }
}

void insert(Dictionary D, char* k, char* v){
     int i = hash(k);
  
     if(D == NULL){ //Dictionary is NULL
         fprintf(stderr, "Dictionary Error: calling insert() on NULL Dictionary reference\n");
         exit(EXIT_FAILURE);
      }
      if(lookup(D, k) == NULL){ //didn't find it
         Node N = newNode(k, v);
         D-> table[i] = N;
         N->next = D->table[i];
         D->table[i]  = N;
         //N->next = D->table[i];
         //D->table[i] = N;
      } 
      else{ //did find it
         Node P = P->next; 
         Node C = P->next;
         P->next = newNode(k, v);
         D-> table[i] = P;
         P = P->next;
         P->next = C;
      }
      D->numItems++;
}

void delete(Dictionary D, char* k){
   //int returnValue;
   //Node N;
  //if N.next = null, delete from the table
  int i = hash(k);
   Node A = findKey(D, k);
        A = D->table[i];
        Node tempNode = D->table[i];
        Node prevNode = NULL;
   if( D==NULL ){
      fprintf(stderr, "Dictionary Error: calling delete() on NULL Dictionary reference\n");
      exit(EXIT_FAILURE);
   }
   if( D->numItems==0 ){
      fprintf(stderr,  "Dictionary Error: cannot delete() non-existent key: \"%s\"\n", k);
      exit(EXIT_FAILURE);
   }
   while(tempNode != NULL) {
          if(tempNode == A) {
            prevNode->next = tempNode->next;
            D->numItems--;
            return;
          }
          prevNode = tempNode;
          tempNode = tempNode->next;
   }
}

void makeEmpty(Dictionary D){
   //table(tablesize-1)
  //while tableSize is not null, delete the previous 
  freeDictionary(D);
  Dictionary temp = newDictionary();
  D = temp;
   //D = NULL;
   //D->numItems = 0;
}
void printDictionary(FILE* out, Dictionary D){
   if( D==NULL ){
      fprintf(stderr, 
              "Dictionary Error: calling printDictionary() on NULL Dictionary reference\n");
      exit(EXIT_FAILURE);
   }
    for(int i=0; i<D->numItems; i++){
      Node H = D->table[i];
      for(Node N=H; N!=NULL; N=N->next) {
        fprintf(out, "%s %s", N->key, N->value);
        fprintf(out, "\n");
     }
    }
}








