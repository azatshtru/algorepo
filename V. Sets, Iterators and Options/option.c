#define Option(TYPE) \
typedef struct option_##TYPE { TYPE * some; int none; } Option_##TYPE; \
Option_##TYPE Some_##TYPE (TYPE * value) {\
    Option_##TYPE o;\
    o.some = value;\
    o.none = 0;\
    return o;\
}\
Option_##TYPE None_##TYPE () { \
    Option_##TYPE o;\
    o.none = 1;\
    return o; \
}