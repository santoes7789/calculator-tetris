#ifndef _BLOCKS_H 
#define _BLOCKS_H 

/* Blocks */
#define SHAPE_L 0
#define SHAPE_J 1
#define SHAPE_S 2
#define SHAPE_Z 3
#define SHAPE_T 4
#define SHAPE_O 5
#define SHAPE_I 6

typedef struct {
    int size;
    bool data[16];
} TetData;

extern const TetData tetrominos[7];

#endif /* _BLOCKS_H_ */