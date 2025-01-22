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

oj_test(four_to_the_power_10) {
    oj_assert_eq_int(1048576, power(4, 10));
    oj_fresh;
}

oj_test(canton_pairing_of_2_and_3_returns_18) {
    oj_assert_eq_int(18, cantor_pairing(2, 3));
    oj_fresh;
}

oj_test(canton_pairing_of_5_and_8_returns_99) {
    oj_assert_eq_int(99, cantor_pairing(5, 8));
    oj_fresh;
}

struct point2d {
    int x;
    int y;
};

oj_test(container_of_returns_the_pointer_to_struct) {
    struct point2d point = { 3, 4 };
    struct point2d* result1 = container_of(&point.x, struct point2d, x);
    struct point2d* result2 = container_of(&point.y, struct point2d, y);
    oj_assert_eq_pointer(&point, result1);
    oj_assert_eq_pointer(&point, result2);
    oj_fresh;
}

oj_prepare(container_of_tests) {
    oj_run(container_of_returns_the_pointer_to_struct);
    oj_report;
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

oj_prepare(exponentiation_tests) {
    oj_run(four_to_the_power_10);
    oj_report;
    oj_fresh;
}

oj_prepare(cantor_pairing_tests) {
    oj_run(canton_pairing_of_2_and_3_returns_18);
    oj_run(canton_pairing_of_5_and_8_returns_99);
    oj_report;
    oj_fresh;
}

int main() {
    oj_blend(natural_log_tests, 0);
    oj_blend(exponentiation_tests, 0);
    oj_blend(cantor_pairing_tests, 0);
    oj_blend(container_of_tests, 0);
    return 0;
}

