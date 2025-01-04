#ifndef OJ_TEST
#define OJ_TEST

#include <stdio.h>
#include <string.h>

#define oj_fresh return 0
#define oj_test(test) static int test(char* message)
#define oj_prepare(suite) static int suite(int oj_tests_run, int oj_tests_passed, int oj_ignore_fresh)

#define oj_assert(assertion, description)    \
    do {                        \
        sprintf(message, "%s (%s, line %d)", description, __FILE__, __LINE__);   \
        if (!(assertion)) {     \
            return 1;           \
        }                       \
    } while (0)

#define oj_assert_eq_int(expected, result)                                  \
    do {                                                                    \
        sprintf(message, "[Expected: %d, got: %d], in %s at line %d", expected, result, __FILE__, __LINE__);      \
        if(result != result && expected == expected) {                      \
            return 1;                                                       \
        }                                                                   \
        if(expected != result) {                                            \
            return 1;                                                       \
        }                                                                   \
    } while(0)

#define oj_assert_eq_float(expected, result)                                \
    do {                                                                    \
        sprintf(message, "[Expected: %lf, got: %lf], in %s at line %d", expected, result, __FILE__, __LINE__);      \
        double epsilon = expected - result;                                 \
        if(result != result && expected == expected) {                      \
            return 1;                                                       \
        }                                                                   \
        if(epsilon < -1e-4 || epsilon > 1e-4) {                             \
            return 1;                                                       \
        }                                                                   \
    } while(0)

#define oj_assert_eq_bytes(length, expected, result, description) do {              \
    sprintf(message, "%s (%s, line %d)", description, __FILE__, __LINE__);          \
    if(memcmp(expected, result, length)) {                                          \
        return 1;                                                                   \
    }                                                                               \
} while(0)

#define oj_run(test)                                                                                    \
    do {                                                                                                \
        char message[128];                                                                              \
        int test_result = !test(message);                                                               \
        if(test_result && !oj_ignore_fresh) {                                                           \
            printf("\x1b[1;32m    FRESH! \x1b[0m");                                                     \
            printf(#test);                                                                              \
            printf("\n");                                                                               \
        } else if(!test_result) {                                                                       \
            printf("\x1b[1;31m    ROTTEN \x1b[0m");                                                     \
            printf(#test);                                                                              \
            if(message) { printf("\x1b[35m %s \x1b[0m", message); }                                     \
            printf("\n");                                                                               \
        }                                                                                               \
        ++oj_tests_run;                                                                                 \
        oj_tests_passed += test_result;                                                                 \
    } while (0)

#define oj_blend(suite, ignore_fresh)   \
    do {                                \
        printf("\n");                   \
        printf("\U0001F34A \x1b[1;4m"); \
        printf(#suite);                 \
        printf("\x1b[0m");              \
        printf("\n\n");                 \
        suite(0, 0, ignore_fresh);      \
    } while(0)

#define oj_report                                                                                                           \
    do {                                                                                                                    \
        printf("  ----------------------------------\n");                                                                   \
        printf("    %s \x1b[1m%d out of %d tests passed.\x1b[0m\n",                                                         \
                oj_tests_passed == oj_tests_run ? "\U00002713" : "\U00002717", oj_tests_passed, oj_tests_run);              \
        printf("    %s \x1b[1mOJ %.0f%% juicy!\x1b[0m\n",                                                                   \
                oj_tests_passed == oj_tests_run ? "\U00002713" : "\U00002717", (double)oj_tests_passed/oj_tests_run * 100); \
        printf("  ----------------------------------\n");                                                                   \
        printf("\n");                                                                                                       \
    } while(0)

#endif
