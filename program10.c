
#include <stdio.h>
#include <stdlib.h>

void FCFS(int req[], int n, int head) {
    int total = 0;

    for (int i = 0; i < n; i++) {
        total += abs(head - req[i]);
        head = req[i];
    }

    printf("\nFCFS Total Head Movement: %d\n", total);
}

void SSTF(int req[], int n, int head) {
    int visited[n];
    int total = 0;

    for (int i = 0; i < n; i++)
        visited[i] = 0;

    for (int i = 0; i < n; i++) {
        int min = 1000000, index = -1;

        for (int j = 0; j < n; j++) {
            if (!visited[j] && abs(head - req[j]) < min) {
                min = abs(head - req[j]);
                index = j;
            }
        }

        visited[index] = 1;
        total += abs(head - req[index]);
        head = req[index];
    }

    printf("SSTF Total Head Movement: %d\n", total);
}

void SCAN(int req[], int n, int head, int size) {
    int a[n + 1], total = 0;

    for (int i = 0; i < n; i++)
        a[i] = req[i];

    a[n] = head;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n + 1; j++) {
            if (a[i] > a[j]) {
                int temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }

    int pos = 0;

    for (int i = 0; i < n + 1; i++) {
        if (a[i] == head) {
            pos = i;
            break;
        }
    }

    for (int i = pos; i < n; i++) {
        total += abs(head - a[i + 1]);
        head = a[i + 1];
    }

    total += abs(head - (size - 1));
    head = size - 1;

    for (int i = pos - 1; i >= 0; i--) {
        total += abs(head - a[i]);
        head = a[i];
    }

    printf("SCAN Total Head Movement: %d\n", total);
}

void CSCAN(int req[], int n, int head, int size) {
    int a[n + 1], total = 0;

    for (int i = 0; i < n; i++)
        a[i] = req[i];

    a[n] = head;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n + 1; j++) {
            if (a[i] > a[j]) {
                int temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }

    int pos = 0;

    for (int i = 0; i < n + 1; i++) {
        if (a[i] == head) {
            pos = i;
            break;
        }
    }

    for (int i = pos; i < n; i++) {
        total += abs(head - a[i + 1]);
        head = a[i + 1];
    }

    total += abs(head - (size - 1));
    total += (size - 1);
    head = 0;

    for (int i = 0; i < pos; i++) {
        total += abs(head - a[i]);
        head = a[i];
    }

    printf("C-SCAN Total Head Movement: %d\n", total);
}

int main() {
    int n, head, size;

    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid number of requests.\n");
        return 1;
    }

    printf("Enter disk size: ");
    scanf("%d", &size);

    if (size <= 0) {
        printf("Invalid disk size.\n");
        return 1;
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    if (head < 0 || head >= size) {
        printf("Invalid head position.\n");
        return 1;
    }

    int req[n];

    printf("Enter disk request sequence:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &req[i]);

        if (req[i] < 0 || req[i] >= size) {
            printf("Invalid request position.\n");
            return 1;
        }
    }

    FCFS(req, n, head);
    SSTF(req, n, head);
    SCAN(req, n, head, size);
    CSCAN(req, n, head, size);

    return 0;
}
