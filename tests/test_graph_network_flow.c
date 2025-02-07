#include "../headers/graph_network_flow.h"
#include "orange_juice.h"

oj_test(edmonds_karp_returns_7_for_network_with_7_flow) {
    oj_rotten;
}

oj_test(edmonds_karp_returns_5_for_network_with_5_flow) {
    oj_rotten;
}

oj_test(edmonds_karp_returns_19_for_network_with_19_flow) {
    oj_rotten;
}

oj_prepare(test_edmonds_karp) {
    oj_run(edmonds_karp_returns_7_for_network_with_7_flow);
    oj_run(edmonds_karp_returns_5_for_network_with_5_flow);
    oj_run(edmonds_karp_returns_19_for_network_with_19_flow);
    oj_report;
    oj_fresh;
}

int main() {
    oj_blend(test_edmonds_karp, 0);
    return 0;
}
