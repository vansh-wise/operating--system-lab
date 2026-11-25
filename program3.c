
#include <stdio.h>

#define MAX 20

typedef struct {
    int pid, at, bt, pr;
    int ct, tat, wt, rem;
} Process;

void sortByArrival(Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at) {
                Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void printResult(Process p[], int n) {
    float totalWT = 0, totalTAT = 0;

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt);

        totalWT += p[i].wt;
        totalTAT += p[i].tat;
    }

    printf("\nAverage Waiting Time = %.2f\n", totalWT / n);
    printf("Average Turnaround Time = %.2f\n", totalTAT / n);
}

void fcfs(Process p[], int n) {
    int time = 0;

    sortByArrival(p, n);

    for (int i = 0; i < n; i++) {
        if (time < p[i].at)
            time = p[i].at;

        time += p[i].bt;
        p[i].ct = time;
    }

    printResult(p, n);
}

void sjf(Process p[], int n) {
    int completed = 0, time = 0;
    int done[MAX] = {0};

    while (completed < n) {
        int idx = -1;

        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].at <= time) {
                if (idx == -1 || p[i].bt < p[idx].bt)
                    idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        time += p[idx].bt;
        p[idx].ct = time;
        done[idx] = 1;
        completed++;
    }

    printResult(p, n);
}

void priorityScheduling(Process p[], int n) {
    int completed = 0, time = 0;
    int done[MAX] = {0};

    while (completed < n) {
        int idx = -1;

        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].at <= time) {
                if (idx == -1 || p[i].pr < p[idx].pr)
                    idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        time += p[idx].bt;
        p[idx].ct = time;
        done[idx] = 1;
        completed++;
    }

    printResult(p, n);
}

void roundRobin(Process p[], int n, int quantum) {
    int queue[10000];
    int front = 0, rear = 0, count = 0;
    int completed = 0, time = 0, next = 0;

    sortByArrival(p, n);

    for (int i = 0; i < n; i++)
        p[i].rem = p[i].bt;

    while (completed < n) {
        while (next < n && p[next].at <= time) {
            queue[rear] = next;
            rear = (rear + 1) % 10000;
            count++;
            next++;
        }

        if (count == 0) {
            time = p[next].at;
            continue;
        }

        int idx = queue[front];
        front = (front + 1) % 10000;
        count--;

        int slice = (p[idx].rem < quantum)
                    ? p[idx].rem : quantum;

        time += slice;
        p[idx].rem -= slice;

        while (next < n && p[next].at <= time) {
            queue[rear] = next;
            rear = (rear + 1) % 10000;
            count++;
            next++;
        }

        if (p[idx].rem > 0) {
            queue[rear] = idx;
            rear = (rear + 1) % 10000;
            count++;
        } else {
            p[idx].ct = time;
            completed++;
        }
    }

    printResult(p, n);
}

int main() {
    Process p[MAX];
    int n, choice, quantum;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    if (n < 1 || n > MAX) {
        printf("Invalid number of processes.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;

        printf("Process %d - Arrival Time, Burst Time, Priority: ",
               i + 1);

        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].pr);

        if (p[i].at < 0 || p[i].bt <= 0) {
            printf("Invalid arrival or burst time.\n");
            return 1;
        }
    }

    printf("\nMenu:\n");
    printf("1. FCFS\n");
    printf("2. SJF (Non-preemptive)\n");
    printf("3. Priority (Non-preemptive)\n");
    printf("4. Round Robin\n");

    printf("Enter choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            fcfs(p, n);
            break;

        case 2:
            sjf(p, n);
            break;

        case 3:
            priorityScheduling(p, n);
            break;

        case 4:
            printf("Enter time quantum: ");
            scanf("%d", &quantum);

            if (quantum <= 0) {
                printf("Invalid time quantum.\n");
                return 1;
            }

            roundRobin(p, n, quantum);
            break;

        default:
            printf("Invalid choice.\n");
    }

    return 0;
}
