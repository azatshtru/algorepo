#include "../std/vector.c"
#include "../std/box.c"

typedef struct task {
    char* taskName;
    int duration;
    int deadline;
} Task;

stdBox(Task)
stdVector(BoxTask)

Task make_task(char* S, int i, int f) {
    Task e = { S, i, f };
    return e;
}

int cmp_task_duration(BoxTask a, BoxTask b) {
    return a.value->duration<b.value->duration?1:0;
}

//Completing each task gives a score of d - x where d is the deadline and x is the time when the task was finished.
//The problem is to arrange the tasks in such an order that one can obtain maximum score.
//This can be easily achieved by sorting the tasks based on duration, based on the greedy strategy that the earlier a task completes, the more score it gives.
int max_td_score(Vector(BoxTask) v) {
    quick_sort(BoxTask, v, 0, v->fill, cmp_task_duration);
    int score = 0;
    int time = 0;
    for(int i = 0; i < v->fill+1; i++) {
        time += get(BoxTask, v, i).value->duration;
        score += get(BoxTask, v, i).value->deadline - time;
    }
    return score;
}

Vector(BoxTask) generateExampleTasks() {
    Vector(BoxTask) v = createVector(BoxTask);
    push(BoxTask, v, Box(Task, make_task("A", 2, 8)));
    push(BoxTask, v, Box(Task, make_task("B", 5, 10)));
    push(BoxTask, v, Box(Task, make_task("C", 3, 11)));
    push(BoxTask, v, Box(Task, make_task("D", 1, 12)));
    push(BoxTask, v, Box(Task, make_task("E", 4, 1)));
    push(BoxTask, v, Box(Task, make_task("F", 6, 3)));
    push(BoxTask, v, Box(Task, make_task("G", 1, 5)));
    push(BoxTask, v, Box(Task, make_task("H", 3, 6)));
    push(BoxTask, v, Box(Task, make_task("I", 2, 7)));
    push(BoxTask, v, Box(Task, make_task("J", 2, 8)));
    push(BoxTask, v, Box(Task, make_task("K", 4, 9)));
    push(BoxTask, v, Box(Task, make_task("L", 1, 11)));
    return v;
}
