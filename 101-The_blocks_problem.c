#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BLOCK_NUM 25
#define MAX_INPUT_LENGTH 10

typedef enum COMMAND_T {
    MOVE_ONTO = 0,
    MOVE_OVER,
    PILE_ONTO,
    PILE_OVER
} COMMAND;

typedef struct CommandNode_T {
    COMMAND eCommand;
    int numA;
    int numB;
    struct CommandNode_T* pNextCommand;
} CommandNode;

typedef struct BlockNode_T {
    int number;
    struct BlockNode_T* pNextBlock;
} BlockNode;

void ClearUpperBlocks (BlockNode** pTableBlocks, BlockNode* pBlockNode) {
    BlockNode* pIndexBlock = pBlockNode->pNextBlock;

    while (pIndexBlock != NULL) {
        pBlockNode->pNextBlock = pIndexBlock->pNextBlock;
        pTableBlocks[pIndexBlock->number] = pIndexBlock;
        pIndexBlock->pNextBlock = NULL;
        pIndexBlock = pBlockNode->pNextBlock;
    }

    return;
}

int CheckSameStack (BlockNode* pBlockA, BlockNode* pBlockB) {
    BlockNode* pIndexBlock = pBlockA;

    while (pIndexBlock != NULL) {
        if (pIndexBlock == pBlockB) {
            return 0;
        }

        pIndexBlock = pIndexBlock->pNextBlock;
    }

    pIndexBlock = pBlockB;

    while (pIndexBlock != NULL) {
        if (pIndexBlock == pBlockA) {
            return 0;
        }

        pIndexBlock = pIndexBlock->pNextBlock;
    }

    return 1;
}

void MoveOnto (BlockNode** pTableBlocks, BlockNode** pAllBlocks, int numA, int numB) {
    int index = 0;
    BlockNode* pBlockA = pAllBlocks[numA];
    BlockNode* pBlockB = pAllBlocks[numB];

    if (CheckSameStack(pBlockA, pBlockB) == 0) {
        return;
    }

    ClearUpperBlocks(pTableBlocks, pBlockA);
    ClearUpperBlocks(pTableBlocks, pBlockB);

    for (index = 0; index < MAX_BLOCK_NUM; index++) {
        if ((pAllBlocks[index] != NULL) && (pAllBlocks[index]->pNextBlock == pBlockA)) {
            pAllBlocks[index]->pNextBlock = NULL;
            break;
        }
    }

    if ((pTableBlocks[pBlockA->number] != NULL) && (pTableBlocks[pBlockA->number]->number == pBlockA->number)) {
        pTableBlocks[pBlockA->number] = NULL;
    }

    pBlockB->pNextBlock = pBlockA;
    return;
}

void MoveOver (BlockNode** pTableBlocks, BlockNode** pAllBlocks, int numA, int numB) {
    int index = 0;
    BlockNode* pBlockA = pAllBlocks[numA];
    BlockNode* pBlockB = pAllBlocks[numB];
    BlockNode* pIndexBlock = pBlockB;

    if (CheckSameStack(pBlockA, pBlockB) == 0) {
        return;
    }

    ClearUpperBlocks(pTableBlocks, pBlockA);

    for (index = 0; index < MAX_BLOCK_NUM; index++) {
        if ((pAllBlocks[index] != NULL) && (pAllBlocks[index]->pNextBlock == pBlockA)) {
            pAllBlocks[index]->pNextBlock = NULL;
            break;
        }
    }

    if ((pTableBlocks[pBlockA->number] != NULL) && (pTableBlocks[pBlockA->number]->number == pBlockA->number)) {
        pTableBlocks[pBlockA->number] = NULL;
    }

    while (pIndexBlock->pNextBlock != NULL) {
        pIndexBlock = pIndexBlock->pNextBlock;
    }

    pIndexBlock->pNextBlock = pBlockA;
    return;
}

void PileOnto (BlockNode** pTableBlocks, BlockNode** pAllBlocks, int numA, int numB) {
    int index = 0;
    BlockNode* pBlockA = pAllBlocks[numA];
    BlockNode* pBlockB = pAllBlocks[numB];

    if (CheckSameStack(pBlockA, pBlockB) == 0) {
        return;
    }

    ClearUpperBlocks(pTableBlocks, pBlockB);

    for (index = 0; index < MAX_BLOCK_NUM; index++) {
        if ((pAllBlocks[index] != NULL) && (pAllBlocks[index]->pNextBlock == pBlockA)) {
            pAllBlocks[index]->pNextBlock = NULL;
            break;
        }
    }

    if ((pTableBlocks[pBlockA->number] != NULL) && (pTableBlocks[pBlockA->number]->number == pBlockA->number)) {
        pTableBlocks[pBlockA->number] = NULL;
    }

    pBlockB->pNextBlock = pBlockA;
    return;
}

void PileOver (BlockNode** pTableBlocks, BlockNode** pAllBlocks, int numA, int numB) {
    int index = 0;
    BlockNode* pBlockA = pAllBlocks[numA];
    BlockNode* pBlockB = pAllBlocks[numB];
    BlockNode* pIndexBlock = pBlockB;

    if (CheckSameStack(pBlockA, pBlockB) == 0) {
        return;
    }

    for (index = 0; index < MAX_BLOCK_NUM; index++) {
        if ((pAllBlocks[index] != NULL) && (pAllBlocks[index]->pNextBlock == pBlockA)) {
            pAllBlocks[index]->pNextBlock = NULL;
            break;
        }
    }

    if ((pTableBlocks[pBlockA->number] != NULL) && (pTableBlocks[pBlockA->number]->number == pBlockA->number)) {
        pTableBlocks[pBlockA->number] = NULL;
    }

    while (pIndexBlock->pNextBlock != NULL) {
        pIndexBlock = pIndexBlock->pNextBlock;
    }

    pIndexBlock->pNextBlock = pBlockA;
    return;
}

int main () {
    CommandNode* pCommandList = NULL;
    CommandNode* pIndexCommand = NULL;
    BlockNode* allBlocks[MAX_BLOCK_NUM] = {0};
    BlockNode* tableBlocks[MAX_BLOCK_NUM] = {0};
    int index = 0, blockNum = 0;

    scanf("%d", &blockNum);

    while (1) {
        char inputBuf[MAX_INPUT_LENGTH] = {0};

        scanf("%s", inputBuf);

        if (strcmp(inputBuf, "quit") == 0) {
            break;
        }
        else if (strcmp(inputBuf, "move") == 0) {
            CommandNode* pNewCommand = (CommandNode*)malloc(sizeof(CommandNode));
            int inputNum = 0;

            scanf("%d", &inputNum);

            if (inputNum < blockNum) {
                pNewCommand->numA = inputNum;
            }
            else {
                free(pNewCommand);
                continue;
            }

            scanf("%s", inputBuf);

            if (strcmp(inputBuf, "onto") == 0) {
                pNewCommand->eCommand = MOVE_ONTO;
            }
            else if (strcmp(inputBuf, "over") == 0) {
                pNewCommand->eCommand = MOVE_OVER;
            }
            else {
                free(pNewCommand);
                continue;
            }

            scanf("%d", &inputNum);

            if (inputNum < blockNum) {
                pNewCommand->numB = inputNum;
            }
            else {
                free(pNewCommand);
                continue;
            }

            if (pIndexCommand == NULL) {
                pCommandList = pNewCommand;
            }
            else {
                pIndexCommand->pNextCommand = pNewCommand;
            }

            pIndexCommand = pNewCommand;
        }
        else if (strcmp(inputBuf, "pile") == 0) {
            CommandNode* pNewCommand = (CommandNode*)malloc(sizeof(CommandNode));
            int inputNum = 0;

            scanf("%d", &inputNum);

            if (inputNum < blockNum) {
                pNewCommand->numA = inputNum;
            }
            else {
                free(pNewCommand);
                continue;
            }

            scanf("%s", inputBuf);

            if (strcmp(inputBuf, "onto") == 0) {
                pNewCommand->eCommand = PILE_ONTO;
            }
            else if (strcmp(inputBuf, "over") == 0) {
                pNewCommand->eCommand = PILE_OVER;
            }
            else {
                free(pNewCommand);
                continue;
            }

            scanf("%d", &inputNum);

            if (inputNum < blockNum) {
                pNewCommand->numB = inputNum;
            }
            else {
                free(pNewCommand);
                continue;
            }

            if (pIndexCommand == NULL) {
                pCommandList = pNewCommand;
            }
            else {
                pIndexCommand->pNextCommand = pNewCommand;
            }

            pIndexCommand = pNewCommand;
        }
        else {
            continue;
        }
    }

    for (index = 0; index < blockNum; index++) {
        allBlocks[index] = (BlockNode*)malloc(sizeof(BlockNode));
        allBlocks[index]->number = index;
        allBlocks[index]->pNextBlock = NULL;
        tableBlocks[index] = allBlocks[index];
    }

    pIndexCommand = pCommandList;

    while (pIndexCommand != NULL) {
        pCommandList = pCommandList->pNextCommand;

        switch (pIndexCommand->eCommand) {
            case MOVE_ONTO:
                MoveOnto(tableBlocks, allBlocks, pIndexCommand->numA, pIndexCommand->numB);
                break;
            case MOVE_OVER:
                MoveOver(tableBlocks, allBlocks, pIndexCommand->numA, pIndexCommand->numB);
                break;
            case PILE_ONTO:
                PileOnto(tableBlocks, allBlocks, pIndexCommand->numA, pIndexCommand->numB);
                break;
            case PILE_OVER:
                PileOver(tableBlocks, allBlocks, pIndexCommand->numA, pIndexCommand->numB);
                break;
            default:
                break;
        }

        free(pIndexCommand);
        pIndexCommand = pCommandList;
    }

    for (index = 0; index < blockNum; index++) {
        BlockNode* pIndexBlock = tableBlocks[index];

        printf("%d:", index);

        while (pIndexBlock != NULL) {
            printf(" %d", pIndexBlock->number);
            pIndexBlock = pIndexBlock->pNextBlock;
        }

        printf("\n");
    }

    for (index = 0; index < blockNum; index++) {
        free(allBlocks[index]);
    }

    return 0;
}
