
#include <stdio.h>

#define MAX 100

int main() {
    int totalBlocks, choice;
    int used[MAX] = {0};

    printf("Enter total number of disk blocks: ");
    scanf("%d", &totalBlocks);

    if (totalBlocks <= 0 || totalBlocks > MAX) {
        printf("Invalid number of blocks.\n");
        return 1;
    }

    printf("\n1. Contiguous Allocation");
    printf("\n2. Linked Allocation");
    printf("\n3. Indexed Allocation");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    int fileBlocks;

    printf("Enter number of blocks required by file: ");
    scanf("%d", &fileBlocks);

    if (fileBlocks <= 0 || fileBlocks > totalBlocks) {
        printf("Invalid file size.\n");
        return 1;
    }

    switch (choice) {

        case 1: {
            int start, found = 0;

            for (int i = 0; i <= totalBlocks - fileBlocks; i++) {
                int j;

                for (j = 0; j < fileBlocks; j++) {
                    if (used[i + j])
                        break;
                }

                if (j == fileBlocks) {
                    start = i;
                    found = 1;
                    break;
                }
            }

            if (found) {
                printf("\nContiguous Allocation Successful.\n");
                printf("Allocated Blocks: ");

                for (int i = start; i < start + fileBlocks; i++) {
                    used[i] = 1;
                    printf("%d ", i);
                }
                printf("\n");
            } else {
                printf("\nContiguous Allocation Not Possible.\n");
            }

            break;
        }

        case 2: {
            int blocks[MAX], count = 0;

            for (int i = 0; i < totalBlocks && count < fileBlocks; i++) {
                if (!used[i]) {
                    blocks[count++] = i;
                    used[i] = 1;
                }
            }

            printf("\nLinked Allocation Successful.\n");
            printf("Block Chain: ");

            for (int i = 0; i < count; i++) {
                if (i < count - 1)
                    printf("%d -> ", blocks[i]);
                else
                    printf("%d -> NULL\n", blocks[i]);
            }

            break;
        }

        case 3: {
            int indexBlock = -1;
            int dataBlocks[MAX], count = 0;

            for (int i = 0; i < totalBlocks; i++) {
                if (!used[i]) {
                    indexBlock = i;
                    used[i] = 1;
                    break;
                }
            }

            if (indexBlock == -1) {
                printf("No free index block available.\n");
                break;
            }

            for (int i = 0; i < totalBlocks && count < fileBlocks; i++) {
                if (!used[i]) {
                    dataBlocks[count++] = i;
                    used[i] = 1;
                }
            }

            if (count < fileBlocks) {
                printf("Not enough free blocks for indexed allocation.\n");
                break;
            }

            printf("\nIndexed Allocation Successful.\n");
            printf("Index Block: %d\n", indexBlock);
            printf("Data Blocks: ");

            for (int i = 0; i < count; i++)
                printf("%d ", dataBlocks[i]);

            printf("\n");
            break;
        }

        default:
            printf("Invalid choice.\n");
    }

    return 0;
}
