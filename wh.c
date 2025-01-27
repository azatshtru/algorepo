
do {
  Vector *__v__ = (Vector *)(cnode->children);
  if (0 > __v__->len) {
    break;
  }
  do {
    Vector *__v__ = (Vector *)((cnode->children));
    if (__v__->len >= __v__->cap) {
      vec_resize(__v__, __v__->cap * 2);
    }
    (*((cnode->children)))[__v__->len] =
        (*(lsnode->children))[(vec_len(lsnode->children) - 1)];
    ++__v__->len;
  } while (0);
  __builtin___memmove_chk(*(cnode->children) + 0 + 1, *(cnode->children) + 0,
                          __v__->type_size * (__v__->len - 0 - 1),
                          __builtin_object_size(*(cnode->children) + 0 + 1, 0));
  (*(cnode->children))[0] =
      ((*(lsnode->children))[(vec_len(lsnode->children) - 1)]);
} while (0)

do {
  Vector *__v__ = (Vector *)(cnode->children);
  if (0 > __v__->len) {
    break;
  }
  do {
    Vector *__v__ = (Vector *)((cnode->children));
    if (__v__->len >= __v__->cap) {
      vec_resize(__v__, __v__->cap * 2);
    }
    (*((cnode->children)))[__v__->len] =
        (**((lsnode->children) + 1) = (*(
             (lsnode->children)))[(((vec_len(lsnode->children) - 1) >= 0)
                                       ? (vec_len(lsnode->children) - 1)
                                       : (((Vector *)(lsnode->children))->len +
                                          (vec_len(lsnode->children) - 1)))],
         vec_zap((lsnode->children), (vec_len(lsnode->children) - 1),
                 ((void *)0)),
         **((lsnode->children) + 1));
    ++__v__->len;
  } while (0);
  __builtin___memmove_chk(*(cnode->children) + 0 + 1, *(cnode->children) + 0,
                          __v__->type_size * (__v__->len - 0 - 1),
                          __builtin_object_size(*(cnode->children) + 0 + 1, 0));
  (*(cnode->children))[0] = ((
      **((lsnode->children) + 1) =
          (*((lsnode->children)))[(((vec_len(lsnode->children) - 1) >= 0)
                                       ? (vec_len(lsnode->children) - 1)
                                       : (((Vector *)(lsnode->children))->len +
                                          (vec_len(lsnode->children) - 1)))],
      vec_zap((lsnode->children), (vec_len(lsnode->children) - 1), ((void *)0)),
      **((lsnode->children) + 1)));
} while (0)
