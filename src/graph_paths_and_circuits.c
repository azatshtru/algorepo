#include "../headers/graph_paths_and_circuits.h"

int graph_eulerian_path_exists(struct graph* graph, void** start_vertex) {
    void* start = NULL;
    void* end = NULL;
    int vertex_len = graph_vertices_len(graph);

    for (int i = 0; i < vertex_len; i++) {
        void* v = vec_get(graph->vertices, i);
        if(graph_vertex_out_degree(graph, v) - graph_vertex_in_degree(graph, v) == 1) {
            if(start) { return 0; }
            start = v;
        } else if(graph_vertex_in_degree(graph, v) - graph_vertex_out_degree(graph, v) == 1) {
            if(end) { return 0; }
            end = v;
        } else if (graph_vertex_out_degree(graph, v) != graph_vertex_in_degree(graph, v)) {
            return 0;
        }
    }
    *start_vertex = start;
    return 1;
}

void graph_hierholzer(struct graph* graph, struct edge** eulerian_path) {
    void* start;
    if(!graph_eulerian_path_exists(graph, &start)) {
        return;
    }
    if(start == NULL) {
        start = vec_get(graph->vertices, 0);
    }

    VecDeque(struct vertex*) stack = queue_new(struct vertex*);
    vector(void*) path = vec_new(void*);
    int processed[graph_vertices_len(graph)];
    memzero(processed, sizeof(int) * graph_vertices_len(graph));

    queue_push_back(stack, graph_vertex(graph, start));
    while(!queue_is_empty(stack)) {
        struct vertex* v = queue_back(stack);
        
        if(processed[v->i] < vec_len(v->out)) {
            queue_push_back(stack, vec_get(v->out, processed[v->i]++));
        } else {
            vec_push(path, queue_pop_back(stack)->value);
        }
    }

    int j = 0;
    void* last_vertex = vec_pop(path, -1);
    for (int i = vec_len(path) - 2; i >= 0; i--) {
        void* current_vertex = vec_pop(path, -1);
        eulerian_path[j++] = graph_edge_between(graph, last_vertex, current_vertex);
        last_vertex = current_vertex;
    }
}

void graph_hamiltonian_path_traverse(struct graph* graph, int** previous, int mask, int pos, vector(void*) path) {
    if (mask == (1 << pos)) {
        vec_push(path, vec_get(graph->vertices, pos));
        return;
    }
    graph_hamiltonian_path_traverse(graph, previous, mask ^ (1 << pos), previous[mask][pos], path);
    vec_push(path, vec_get(graph->vertices, pos));
}

int graph_hamiltonian_path(struct graph* graph, struct vertex** path) {
    int n = graph_vertices_len(graph);

    int** distance = malloc(sizeof(int*) * (1<<n));
    int** previous = malloc(sizeof(int*) * (1<<n));
    for(int i = 0; i < (1<<n); i++) {
        distance[i] = malloc(sizeof(int) * n);
        previous[i] = malloc(sizeof(int) * n);
        memzero(distance[i], sizeof(int) * n);
        memzero(previous[i], sizeof(int) * n);
    }

    for (int i = 0; i < (1 << n); i++) {
        for (int j = 0; j < n; j++) {
            distance[i][j] = I32_MAX;
            previous[i][j] = -1;
        }
    }

    for (int i = 0; i < n; i++) {
        distance[1 << i][i] = 0;
    }

    for (int mask = 0; mask < (1 << n); mask++) {
        for (int u = 0; u < n; u++) {
            if (!(mask & (1 << u))) { continue; }

            struct vertex* current = graph_vertex(graph, vec_get(graph->vertices, u));
            for (int i = 0; i < vec_len(current->out); i++) {
                struct vertex* neighbor = vec_get(current->out, i);
                int v = neighbor->i;
                if (mask & (1 << v)) { continue; }

                int new_mask = mask | (1 << v);
                if (distance[mask][u] != I32_MAX && distance[new_mask][v] > distance[mask][u] + 1) {
                    distance[new_mask][v] = distance[mask][u] + 1;
                    previous[new_mask][v] = u;
                }
            }
        }
    }

    int final_mask = (1 << n) - 1;
    int min_length = I32_MAX;
    int end_vertex = -1;

    for (int i = 0; i < n; i++) {
        if (distance[final_mask][i] < min_length) {
            min_length = distance[final_mask][i];
            end_vertex = i;
        }
    }

    int has_hamiltonian_path = 1;

    if (min_length == I32_MAX) {
        has_hamiltonian_path = 0;
    } else {
        vector(void*) path_vector = vec_new(void*);
        graph_hamiltonian_path_traverse(graph, previous, final_mask, end_vertex, path_vector);
        memmove(path, vec_as_array(path_vector), sizeof(void*) * vec_len(path_vector));
        vec_free(path_vector, NULL);
    }

    for(int i = 0; i < (1<<n); i++) {
        free(distance[i]);
        free(previous[i]);
    }
    free(distance);
    free(previous);
    return has_hamiltonian_path;
}

int graph_hamiltonian_circuit(struct graph* graph, struct vertex** path) {
    int n = graph_vertices_len(graph);

    int** distance = malloc(sizeof(int*) * (1<<n));
    int** previous = malloc(sizeof(int*) * (1<<n));
    for(int i = 0; i < (1<<n); i++) {
        distance[i] = malloc(sizeof(int) * n);
        previous[i] = malloc(sizeof(int) * n);
        memzero(distance[i], sizeof(int) * n);
        memzero(previous[i], sizeof(int) * n);
    }

    for (int i = 0; i < (1 << n); i++) {
        for (int j = 0; j < n; j++) {
            distance[i][j] = I32_MAX;
            previous[i][j] = -1;
        }
    }

    distance[1][0] = 0;

    for (int mask = 0; mask < (1 << n); mask++) {
        for (int u = 0; u < n; u++) {
            if (!(mask & (1 << u))) { continue; }

            struct vertex* current = graph_vertex(graph, vec_get(graph->vertices, u));
            for (int i = 0; i < vec_len(current->out); i++) {
                struct vertex* neighbor = vec_get(current->out, i);
                int v = neighbor->i;
                if (mask & (1 << v)) { continue; }

                int new_mask = mask | (1 << v);
                if (distance[mask][u] != I32_MAX && distance[new_mask][v] > distance[mask][u] + 1) {
                    distance[new_mask][v] = distance[mask][u] + 1;
                    previous[new_mask][v] = u;
                }
            }
        }
    }

    int final_mask = (1 << n) - 1;
    int found_circuit = 0;
    int end_vertex = -1;

    for (int i = 0; i < n; i++) {
        if(distance[final_mask][i] != I32_MAX
            && graph_edge_between(
                graph,
                vec_get(graph->vertices, i),
                vec_get(graph->vertices, 0)
            )
        ) {
            found_circuit = 1;
            end_vertex = i;
            break;
        }
    }

    if (found_circuit) {
        vector(void*) path_vector = vec_new(void*);
        graph_hamiltonian_path_traverse(graph, previous, final_mask, end_vertex, path_vector);
        memmove(path, vec_as_array(path_vector), sizeof(void*) * vec_len(path_vector));
        vec_free(path_vector, NULL);
    }

    for(int i = 0; i < (1<<n); i++) {
        free(distance[i]);
        free(previous[i]);
    }
    free(distance);
    free(previous);
    return found_circuit;
}

void de_bruijn_traverse(int* a, int t, int p, int k, int n, vector(int) sequence) {
    if(t > n) {
        if(n % p == 0) {
            for(int i = 1; i < p + 1; i++) {
                vec_push(sequence, a[i]);
            }
        }
    } else {
        a[t] = a[t - p];
        de_bruijn_traverse(a, t + 1, p, k, n, sequence);
        for(int j = a[t - p] + 1; j < k; j++) {
            a[t] = j;
            de_bruijn_traverse(a, t + 1, t, k, n, sequence);
        }
    }
}

void de_bruijn(int k, int n, vector(char) out) {
    int alphabet[k];
    for(int i = 0; i < k; i++) {
        alphabet[i] = i;
    }

    int a[k * n];
    memzero(a, sizeof(int) * k * n);
    vector(int) sequence = vec_new(int);


    de_bruijn_traverse(a, 1, 1, k, n, sequence);
    for(int i = 0; i < vec_len(sequence); i++) {
        vec_push(out, alphabet[vec_get(sequence, i)]);
    }

    vec_free(sequence, NULL);
}


int knight_move_is_valid(int** board, int n, int x, int y) {
    return (x >= 0 && x < n && y >= 0 && y < n && board[x][y] == -1);
}

int knight_moves_count(int** board, int n, int x, int y) {
    int knight_moves_x[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
    int knight_moves_y[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };

    int count = 0;
    for (int i = 0; i < 8; i++)
        if (knight_move_is_valid(board, n, x + knight_moves_x[i], y + knight_moves_y[i])) {
            count++;
        }
    return count;
}

int knight_move_warnsdorff(int** board, int n, int *x, int *y) {
    int knight_moves_x[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
    int knight_moves_y[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };

    int min_degree = I32_MAX;
    int index = -1;
    int nx;
    int ny;

    for (int i = 0; i < n; i++) {
        nx = *x + knight_moves_x[i];
        ny = *y + knight_moves_y[i];

        if (knight_move_is_valid(board, n, nx, ny)) {
            int degree = knight_moves_count(board, n, nx, ny);
            if (degree < min_degree) {
                min_degree = degree;
                index = i;
            }
        }
    }

    if (index == -1) return 0;

    *x += knight_moves_x[index];
    *y += knight_moves_y[index];
    return 1;
}

int knights_tour(int** board, int n, int start_x, int start_y) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            board[i][j] = -1;

    int x = start_x;
    int y = start_y;
    board[x][y] = 0;

    for (int move = 1; move < n * n; move++) {
        if (!knight_move_warnsdorff(board, n, &x, &y))
            return 0;

        board[x][y] = move;
    }

    return 1;
}
