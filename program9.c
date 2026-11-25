
#include <stdio.h>

void FIFO(int pages[], int n, int frames) {
    int memory[frames], faults = 0, pointer = 0;

    for (int i = 0; i < frames; i++)
        memory[i] = -1;

    for (int i = 0; i < n; i++) {
        int found = 0;

        for (int j = 0; j < frames; j++) {
            if (memory[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            memory[pointer] = pages[i];
            pointer = (pointer + 1) % frames;
            faults++;
        }
    }

    printf("\nFIFO Page Faults: %d\n", faults);
}

void LRU(int pages[], int n, int frames) {
    int memory[frames], lastUsed[frames], faults = 0;

    for (int i = 0; i < frames; i++) {
        memory[i] = -1;
        lastUsed[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int found = 0;

        for (int j = 0; j < frames; j++) {
            if (memory[j] == pages[i]) {
                found = 1;
                lastUsed[j] = i;
                break;
            }
        }

        if (!found) {
            int replace = 0;

            for (int j = 0; j < frames; j++) {
                if (memory[j] == -1) {
                    replace = j;
                    break;
                }

                if (lastUsed[j] < lastUsed[replace])
                    replace = j;
            }

            memory[replace] = pages[i];
            lastUsed[replace] = i;
            faults++;
        }
    }

    printf("LRU Page Faults: %d\n", faults);
}

void Optimal(int pages[], int n, int frames) {
    int memory[frames], faults = 0;

    for (int i = 0; i < frames; i++)
        memory[i] = -1;

    for (int i = 0; i < n; i++) {
        int found = 0;

        for (int j = 0; j < frames; j++) {
            if (memory[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            int replace = -1, farthest = i + 1;

            for (int j = 0; j < frames; j++) {
                if (memory[j] == -1) {
                    replace = j;
                    break;
                }

                int k;
                for (k = i + 1; k < n; k++) {
                    if (memory[j] == pages[k])
                        break;
                }

                if (k == n) {
                    replace = j;
                    break;
                }

                if (k > farthest) {
                    farthest = k;
                    replace = j;
                }
            }

            memory[replace] = pages[i];
            faults++;
        }
    }

    printf("Optimal Page Faults: %d\n", faults);
}

int main() {
    int n, frames;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid number of pages.\n");
        return 1;
    }

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    if (frames <= 0) {
        printf("Invalid number of frames.\n");
        return 1;
    }

    int pages[n];

    printf("Enter page reference string:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    FIFO(pages, n, frames);
    LRU(pages, n, frames);
    Optimal(pages, n, frames);

    return 0;
}
