gcc                 \
    token.c         \
    stack.c         \
    tokenizer.c     \
    token_list.c    \
    parser.c        \
    main.c          \
-lm                 \
-O3                 \
-std=c18            \
-o                  \
    main.o

./main.o

rm main.o
