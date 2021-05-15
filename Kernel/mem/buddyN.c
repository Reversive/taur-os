// //This is a personal academic project. Dear PVS-Studio, please check it.
// //PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
// #include "include/memManager.h"
// #include "include/lib.h"
// #define FALSE 0
// #define TRUE !FALSE

// #define MEM_SIZE 1048576 // 1 MiB (a parte de la usada para el arbol)

// #define TREE_ADDRESS ((void *) 0x0000000000050000L)
// #define TREE_END_ADDRESS ((void *) 0x000000000009FFFFL)
// #define TREE_MAX_SIZE ((uint64_t)((uint64_t)TREE_END_ADDRESS - (uint64_t)TREE_ADDRESS)) // 327680
// #define MAX_NODES 8192 // 2^(floor(log2((TREE_MAX_SIZE / sizeof(Node))))    (MAXIMA CANTIDAD DE NODOS QUE ENTRAN ENTRE TREE_ADDRESS Y TREE_END_ADDRESS)
// #define MIN_BLOCK_SIZE (MEM_SIZE / MAX_NODES) // 128

// #define MAX_LIST_NODES 8192  //2^(floor(log2((TREE_MAX_SIZE - sizeof(List))/ sizeof(ListNode)))    (MAXIMA CANTIDAD DE NODOS QUE ENTRAN ENTRE TREE_ADDRESS Y TREE_END_ADDRESS)
// #define MIN_PAGE_SIZE (MEM_SIZE / MAX_LIST_NODES) // 128

// // #define MODO_FREE_LIST

// typedef char bool;


// typedef struct Node{ // SI SE CAMBIA, HAY QUE CAMBIAR EL DEFINE DE MAX_NODES
//     int size;
//     void * address;
//     uint64_t pid;
//     struct Node * left;
//     struct Node * right;   // If both ptrs are NULL, then this is a process, else, its a full or partially full node
//     bool isFull;    // To know if the node is partially full, or entirely full (if empty, then there shouldnt be a node)
// }Node;

// Node createNode(void * address, uint64_t size, uint64_t pid);
// void * buddyAlloc(uint64_t size, uint64_t pid);
// void * recursiveBuddyAlloc(uint64_t size, uint64_t pid, uint64_t blockSizeWanted, Node * current, uint64_t currentLevelSize);
// void createLeftChild(Node * parent, uint64_t size, uint64_t pid);
// void createRightChild(Node * parent, uint64_t childsBlockSize, uint64_t size, uint64_t pid);
// // void recPrint(Node * node, int depth);
// Node * nextFreeSpaceForNode();
// void pBuddyFree(uint64_t pid, void * address);
// bool pBuddyFreeRec(uint64_t pid, void * address, Node * current);
// void buddyInitializer();
// uint64_t freeMemBuddy();
// uint64_t usedMemBuddy();

// Node * root = TREE_ADDRESS;
// bool isOccupiedNodeSpace[MAX_NODES];
// uint64_t lastUsedIndex; // Of the isOccupiedNodeSpace array
// uint64_t memUsed;


// void buddyInitializer(){
//     isOccupiedNodeSpace[0] = TRUE;
//     lastUsedIndex = 0;
//     for (uint64_t i = 1; i < MAX_NODES; i++)
//     {
//         isOccupiedNodeSpace[i] = FALSE;
//     }
    
//     Node rootNode = createNode(MEM_STARTING_ADDRESS, 0, 0);
//     memcpy(root, &rootNode, sizeof(*root));
//     memUsed = 0;
// }

// Node createNode(void * address, uint64_t size, uint64_t pid){
//     Node node;
//     node.size = size;
//     node.address = address;
//     node.pid = pid;
//     node.left = NULL;
//     node.right = NULL;
//     node.isFull = FALSE;
//     return node;
// }

// void * buddyAlloc(uint64_t size, uint64_t pid){
//     uint64_t childBlockSize;
//     for (childBlockSize = MIN_BLOCK_SIZE; childBlockSize < size; childBlockSize *= 2); // Me fijo cual es la menor potencia de 2 que es mayor al size
//     //return 0x7000000;
//     void * ans = recursiveBuddyAlloc(size, pid, childBlockSize, root, MEM_SIZE);
//     if(ans != NULL)
//         memUsed += childBlockSize;
//     return ans;
// }

// void * recursiveBuddyAlloc(uint64_t size, uint64_t pid, uint64_t blockSize, Node * current, uint64_t currentLevelSize){
//     if((current == NULL) || (currentLevelSize < blockSize) || (current->isFull)){ // estado invalido
//         return NULL;
//     }
//     if(currentLevelSize == blockSize){
//         if((current->left == NULL) && (current->right == NULL)){ // este es su lugar en el arbol
//             current->isFull = TRUE;
//             current->pid = pid;
//             current->size = size;
//             return current->address;
//         }
//         else{ // no tiene que ir por esta rama del arbol
//             return NULL; 
//         }
//     }
//     void * ans;
//     if(current->left == NULL){ // si o si esta en esta rama su lugar
//         createLeftChild(current, size, pid);
//         ans = recursiveBuddyAlloc(size, pid, blockSize, current->left, currentLevelSize/2);
//     }
//     else{
//         ans = recursiveBuddyAlloc(size, pid, blockSize, current->left, currentLevelSize/2); // me fijo si va en el hijo izquierdo 
//         if(ans == NULL){
//             if(current->right == NULL){ // si no existe hijo derecho lo creo
//                 createRightChild(current, currentLevelSize, size, pid);
//             }
//             ans = recursiveBuddyAlloc(size, pid, blockSize, current->right, currentLevelSize/2); // me fijo si va en el hijo derecho
//         }
//     }
//     if((current->left->isFull) && (current->right != NULL) && (current->right->isFull)){
//         current->isFull = TRUE;
//     }
//     return ans;
// }

// void createLeftChild(Node * parent, uint64_t size, uint64_t pid){
//     Node child = createNode(parent->address, size, pid); //primera mitad
//     void * nodeSpace = nextFreeSpaceForNode();
//     memcpy(nodeSpace, &child, sizeof(child));
//     parent->left = nodeSpace;
// }

// void createRightChild(Node * parent, uint64_t parentBlockSize, uint64_t size, uint64_t pid){
//     Node child = createNode((char *)parent->address + parentBlockSize/2, size, pid); //segunda mitad
//     void * nodeSpace = nextFreeSpaceForNode();
//     memcpy(nodeSpace, &child, sizeof(child));
//     parent->right = nodeSpace;
// }

// Node * nextFreeSpaceForNode(){
//     uint64_t i;
//     for (i = (lastUsedIndex + 1) % MAX_NODES; i != lastUsedIndex; i = (i + 1) % MAX_NODES)
//     {
//         if(isOccupiedNodeSpace[i] == FALSE){
//             isOccupiedNodeSpace[i] = TRUE;
//             return root + i;
//         }
//     }
//     if(isOccupiedNodeSpace[i] == FALSE){ // Por si se libero el ultimo espacio reservado
//         return root + i;
//     }
//     return NULL;
// }

// void pBuddyFree(uint64_t pid, void * address){
//     pBuddyFreeRec(pid, address, root);
// }

// bool pBuddyFreeRec(uint64_t pid, void * address, Node * current){
//     if(current == NULL)
//         return FALSE;
//     if((current->left == NULL) && (current->right == NULL)){ // es memoria ocupada
//         if(/*(pid == current->pid) && */(address == current->address)){ // haciamos el chequeo del pid pero sino teniamos algunos problemas con background
//             uint64_t i;
//             for ( i = MIN_BLOCK_SIZE; i < current->size; i*=2);
//             memUsed -= i; 
//             return TRUE; // liberar
//         }
//         return FALSE; // no liberar
//     }

//     if(current->left == NULL){
//         if(pBuddyFreeRec(pid, address, current->right)){
//             current->right = NULL;
//             return TRUE;
//         }
//     }
//     if(current->right == NULL){
//         if(pBuddyFreeRec(pid, address, current->left)){
//             current->left = NULL;
//             return TRUE;
//         }
//     }
//     if(pBuddyFreeRec(pid, address, current->left) == FALSE){
//         if(pBuddyFreeRec(pid, address, current->right)){
//             current->right = NULL;
//         }
//     }
//     else{
//         current->left = NULL;
//     }
//     if(current->isFull){
//         if((current->left == NULL || !(current->left->isFull)) || (current->right == NULL || !(current->right->isFull)))
//             current->isFull = FALSE;
//     }
//     return FALSE;
    
// }

// uint64_t freeMemBuddy(){
//     return MEM_SIZE - usedMemBuddy();
// }

// uint64_t usedMemBuddy(){
//     return memUsed;
// }

