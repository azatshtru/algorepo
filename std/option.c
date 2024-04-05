#define initOption(TYPE) \
typedef struct option_##TYPE { TYPE * some; int none; } Option_##TYPE; \
Option_##TYPE Some_##TYPE (TYPE * value) {\
    Option_##TYPE o;\
    o.some = value;\
    o.none = 0;\
    return o;\
}\
Option_##TYPE None_##TYPE () { \
    Option_##TYPE o;\
    o.some = NULL; \
    o.none = 1;\
    return o; \
} \
TYPE * unwrap_##TYPE(Option_##TYPE o) {\
    if(o.none) {\
        printf("PANIC! No value in option");\
        exit(1);\
    } else {\
        return o.some;\
    }\
    return 0;\
}\

#define Option(TYPE) Option_##TYPE
#define Some(TYPE, v) Some_##TYPE(v)
#define None(TYPE) None_##TYPE()
#define unwrap(TYPE, o) unwrap_##TYPE(o)