#include "../headers/sorting.h"

// completing each task gives a score of d - t where d is the deadline and t is the time when the task was finished.
// the problem is to arrange the tasks in such an order that one can obtain maximum score.
// this can be achieved by sorting the tasks based on duration,
// based on the greedy strategy that the earlier a task completes, the more score it gives.

typedef struct task {
    char* name;
    int duration;
    int deadline;
} Task;


float cmp_task_by_duration(void* a, void* b) {
    return ((struct task*)a)->duration - ((struct task*)b)->duration;
}

int max_score_tasks_and_deadlines(struct task* tasks, int len) {
    quicksort(tasks, sizeof(struct task), 0, len - 1, cmp_task_by_duration);
    int score = 0;
    int time = 0;
    for(int i = 0; i < len; i++) {
        time += tasks[i].duration;
        score += tasks[i].deadline - time;
    }
    return score;
}

int main() {
    return 0;
}
