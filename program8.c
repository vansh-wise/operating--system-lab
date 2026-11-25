
#include <stdio.h>

void firstFit(int block[], int m, int process[], int n) {
    int temp[m], allocation[n];

    for (int i = 0; i < m; i++)
        temp[i] = block[i];

    for (int i = 0; i < n; i++)
        allocation[i] = -1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (temp[j] >= process[i]) {
                allocation[i] = j;
                temp[j] -= process[i];
                break;
            }
        }
    }

    printf("\nFIRST FIT:\n");
    printf("Process\tSize\tBlock\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t", i + 1, process[i]);

        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void bestFit(int block[], int m, int process[], int n) {
    int temp[m], allocation[n];

    for (int i = 0; i < m; i++)
        temp[i] = block[i];

    for (int i = 0; i < n; i++)
        allocation[i] = -1;

    for (int i = 0; i < n; i++) {
        int best = -1;

        for (int j = 0; j < m; j++) {
            if (temp[j] >= process[i]) {
                if (best == -1 || temp[j] < temp[best])
                    best = j;
            }
        }

        if (best != -1) {
            allocation[i] = best;
            temp[best] -= process[i];
        }
    }

    printf("\nBEST FIT:\n");
    printf("Process\tSize\tBlock\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t", i + 1, process[i]);

        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void worstFit(int block[], int m, int process[], int n) {
    int temp[m], allocation[n];

    for (int i = 0; i < m; i++)
        temp[i] = block[i];

    for (int i = 0; i < n; i++)
        allocation[i] = -1;

    for (int i = 0; i < n; i++) {
        int worst = -1;

        for (int j = 0; j < m; j++) {
            if (temp[j] >= process[i]) {
                if (worst == -1 || temp[j] > temp[worst])
                    worst = j;
            }
        }

        if (worst != -1) {
            allocation[i] = worst;
            temp[worst] -= process[i];
        }
    }

    printf("\nWORST FIT:\n");
    printf("Process\tSize\tBlock\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t", i + 1, process[i]);

        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

int main() {
    int m, n;

    printf("Enter number of memory blocks: ");
    scanf("%d", &m);

    printf("Enter number of processes: ");
    scanf("%d", &n);

    if (m <= 0 || n <= 0) {
        printf("Invalid number of blocks or processes.\n");
        return 1;
    }

    int block[m], process[n];

    printf("\nEnter sizes of memory blocks:\n");
    for (int i = 0; i < m; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &block[i]);
    }

    printf("\nEnter sizes of processes:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &process[i]);
    }

    firstFit(block, m, process, n);
    bestFit(block, m, process, n);
    worstFit(block, m, process, n);

    return 0;
}
