#ifndef _BLOCKS_H 
#define _BLOCKS_H 

#include <gint/display.h>

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
    int name;
    bopti_image_t *img;
    bool data[16];
} TetData;

extern const TetData tetrominos[7];

extern bopti_image_t img_I_piece; 
extern bopti_image_t img_J_piece; 
extern bopti_image_t img_L_piece; 
extern bopti_image_t img_O_piece; 
extern bopti_image_t img_S_piece; 
extern bopti_image_t img_T_piece; 
extern bopti_image_t img_Z_piece; 

#endif /* _BLOCKS_H_ */