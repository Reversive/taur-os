// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
// #ifndef FREE_LIST_MEMORY_MANAGER

#include "include/buddy.h"

#define BASE 2
enum powersOfTwo{KILO = 10, MEGA = 20, GIGA = 30};
#define MIN_ALLOC_LOG2 6 //Min size supported = 64 bytes 
#define MAX_ALLOC_LOG2 (GIGA - MIN_ALLOC_LOG2) //Max size supported = 1 GB
#define BINARY_POWER(x) (1 << (x))
#define HEAP_SIZE (1024 * 128)

typedef struct blockNode_t
{
    unsigned short int level;
    unsigned short int inUse;
    struct blockNode_t *previuous;
    struct blockNode_t *next;
} blockNode_t;

static unsigned int getBlock(unsigned int request);
static int getBlockToUse(unsigned int firstBlock);
static blockNode_t *getBuddy(blockNode_t *node);
static blockNode_t *getPrincipalAdress(blockNode_t *node);
static void addNodeAndMerge(blockNode_t *node);
static void addNewNode(blockNode_t *node, blockNode_t *lastNode, unsigned int level);

static int isPower(int x, long int y); // https://www.geeksforgeeks.org/check-if-a-number-is-power-of-another-number/
static inline uint64_t log2(uint64_t n);

static void pushNode(blockNode_t *oldNode, blockNode_t *newNode);
static void deleteNode(blockNode_t *node);
static blockNode_t *popNode(blockNode_t *node);
static int isNodeEmpty(blockNode_t *node);

static blockNode_t *heapPtr;
static void* heapPtrAux;
static int began = 0;
static unsigned int heapSize;
static unsigned int cantBlocks;
static blockNode_t blocksVec[MAX_ALLOC_LOG2];
static unsigned int availableMemory;


int memInfo()
{
        
        // newLineScreen();
        // printf(" - MEMORIA TOTAL: %d bytes",(int)heapSize);
        // newLineScreen();
        // printf(" - MEMORIA LIBRE: %d bytes",(int)availableMemory);
        // newLineScreen();
        // printf(" - MEMORIA UTILIZADA %d BYTES",(int)heapSize-availableMemory);
        // newLineScreen();
     
    return 0;
}

// 
// initializeMemoryManager(heapBaseAddress, HEAP_SIZE);
// void initializeMemoryManager(char *heapBase, unsigned long size)
void initializeMemoryManager()
{
    sbrk_handler(HEAP_SIZE, &heapPtrAux);

    heapPtr = (blockNode_t *)heapPtrAux;
    heapSize = availableMemory = HEAP_SIZE;
    cantBlocks = log2(heapSize) - MIN_ALLOC_LOG2 + 1;

    if (cantBlocks > MAX_ALLOC_LOG2)
        cantBlocks = MAX_ALLOC_LOG2;

    blockNode_t * aux= blocksVec;

    //inicializo los bloques del arreglo
    for (int i = 0; i < cantBlocks; i++,aux++)
    {
        blocksVec[i].level = i;
        blocksVec[i].inUse = 1;
        blocksVec[i].previuous = blocksVec[i].next = aux ;
    }
    //agrego el de mayor tamaño al heap
    addNewNode(heapPtr, &blocksVec[cantBlocks - 1], cantBlocks - 1);
}

void *malloc(size_t nbytes)
{
    if(began == 0 ){
        initializeMemoryManager();
        began =1;
    }
    if (nbytes == 0)
    {
        return NULL;
    }
    unsigned int totalBytes = nbytes + sizeof(blockNode_t);

    if (totalBytes > heapSize)
    {
        return NULL;
    }

    unsigned int block = getBlock(totalBytes);

    int parentBlock = getBlockToUse(block);
    if (parentBlock == -1)
    {
        return NULL;
    }

    blockNode_t *ptr;
    for (ptr = popNode(&blocksVec[parentBlock]); block < parentBlock; parentBlock--)
    {
        ptr->level--;
        addNewNode(getBuddy(ptr), &blocksVec[parentBlock - 1], parentBlock - 1);
    }
    ptr->inUse = 1;
    ptr++;

    availableMemory -= BINARY_POWER(block + MIN_ALLOC_LOG2);

    return (void *)ptr;
}

void free(void *ptr)
{

    if (ptr == NULL)
        return;

    blockNode_t *blockNode = (blockNode_t *)ptr - 1;

    blockNode->inUse = 0;

    availableMemory += BINARY_POWER(blockNode->level + MIN_ALLOC_LOG2);

    addNodeAndMerge(blockNode);

    return;
}

static int isPower(int x, long int y)
{
    // The only power of 1 is 1 itself
    if (x == 1)
        return (y == 1);

    // Repeatedly comput power of x
    long int pow = 1;
    while (pow < y)
        pow *= x;

    // Check if power of x becomes y
    return (pow == y);
}

static uint64_t log2(uint64_t n)
{
    uint64_t val;
    for (val = 0; n > 1; val++, n >>= 1)
        ;

    return val;
}

static void pushNode(blockNode_t *oldNode, blockNode_t *newNode)
{
    blockNode_t *previuous = oldNode->previuous;
    newNode->previuous = previuous;
    newNode->next = oldNode;
    previuous->next = newNode;
    oldNode->previuous = newNode;
}

static void deleteNode(blockNode_t *node)
{
    blockNode_t *previuous = node->previuous;
    blockNode_t *next = node->next;

    previuous->next = next;
    next->previuous = previuous;
}

static blockNode_t *popNode(blockNode_t *node)
{
    blockNode_t *aux = node->previuous;

    if (aux == node)
        return NULL;

    deleteNode(aux);

    return aux;
}

static int isNodeEmpty(blockNode_t *node)
{
    return node->previuous == node;
}

static void addNewNode(blockNode_t *node, blockNode_t *lastNode, unsigned int level)
{
    node->inUse = 0;
    node->level = level;
    pushNode(lastNode, node);
}

static void addNodeAndMerge(blockNode_t *node)
{
    blockNode_t *buddy = getBuddy(node);

    while (node->level != cantBlocks - 1 && buddy->inUse == 0 && buddy->level == node->level)
    {
        deleteNode(buddy);

        node = getPrincipalAdress(node);
        node->level++;

        buddy = getBuddy(node);
    }
    pushNode(&blocksVec[node->level], node);
}

static blockNode_t *getBuddy(blockNode_t *node)
{

    uint64_t currentOffset = (uint64_t)node - (uint64_t)heapPtr;
    uint64_t newOffset = currentOffset ^ BINARY_POWER(MIN_ALLOC_LOG2 + node->level);

    return (blockNode_t *)((uint64_t)heapPtr + newOffset);
}

static blockNode_t *getPrincipalAdress(blockNode_t *node)
{
    uint64_t mask = BINARY_POWER(node->level +MIN_ALLOC_LOG2);
    mask = ~mask;

    uint64_t currentOffset = (uint64_t)node - (uint64_t)heapPtr;
    uint64_t newOffset = currentOffset & mask;

    return (blockNode_t *)((uint64_t)heapPtr + newOffset);
}

static unsigned int getBlock(unsigned int request)
{

    unsigned int aux = log2(request);

    if (aux < MIN_ALLOC_LOG2)
        return 0;

    aux -= MIN_ALLOC_LOG2;

    return isPower(BASE, request) == 0 ? aux + 1 : aux;
}

static int getBlockToUse(unsigned int firstBlock)
{

    int currentBlock = firstBlock;

    while (currentBlock < cantBlocks && isNodeEmpty(&blocksVec[currentBlock]))
        currentBlock++;

    if (currentBlock == cantBlocks)
        return -1;

    return currentBlock;
}

// #endif