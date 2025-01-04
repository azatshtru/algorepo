#include "orange_juice.h"
#include "../headers/miniqutils.h"

oj_test(ln_5) {
    oj_assert_eq_float(1.60943791243, natural_log(5));
    oj_fresh;
}

oj_test(ln_1) {
    oj_assert_eq_float(0.0, natural_log(1));
    oj_fresh;
}

oj_test(ln_0_point_8) {
    oj_assert_eq_float(-0.22314355131, natural_log(0.8));
    oj_fresh;
}

oj_test(ln_1_point_5) {
    oj_assert_eq_float(0.4054651081, natural_log(1.5));
    oj_fresh;
}

oj_test(ln_negative_3) {
    oj_assert_eq_float(0.0/0.0, natural_log(-3));
    oj_fresh;
}

oj_prepare(natural_log_tests) {
    oj_run(ln_5);
    oj_run(ln_1);
    oj_run(ln_1_point_5);
    oj_run(ln_0_point_8);
    oj_run(ln_negative_3);
    oj_report;
    oj_fresh;
}

int main() {
    oj_blend(natural_log_tests, 0);
    return 0;
}

