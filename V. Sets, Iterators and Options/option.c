#define Option(TYPE) \
typedef struct option { TYPE some; int none; } Option_##TYPE; \
Option_##TYPE Some(TYPE value) {\
    Option_##TYPE o;\
    o.some = value;\
    o.none = 0;\
    return o;\
}\
Option_##TYPE None() { \
    Option_##TYPE o;\
    o.none = 1;\
    return o; \
}