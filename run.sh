gcc                 \
    token.c         \
    tokenizer.c     \
    token_list.c    \
    parser.c        \
    main.c          \
-o                  \
    main.o          \
-O3                 \
-lm

./main.o

rm main.o
