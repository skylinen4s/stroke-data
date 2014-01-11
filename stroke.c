/**
 * parson.h and parson.c come from:
 * https://github.com/kgabis/parson
 */
#include <stdio.h>
#include <assert.h>
#include "parson.h"

int main(int argc, char *argv[]) {
    JSON_Value *root;
    JSON_Array *strokes, *track;
    JSON_Object *stroke, *point;
    size_t i, j;
	int x, y, z;

    if(argc!=3){
        fprintf(stderr, "Usage: %s <input> <output>\n", argv[0]);
        return 1;
    }

    FILE *output = fopen(argv[2], "w");

    root = json_parse_file(argv[1]);
    assert(json_value_get_type(root) == JSONArray);

    strokes = json_value_get_array(root);
    for (i = 0; i < json_array_get_count(strokes); ++i) {
        stroke = json_array_get_object(strokes, i);
        track = json_object_get_array(stroke, "track");
        z = 1;
        for (j = 0; j < json_array_get_count(track); ++j) {
            point = json_array_get_object(track, j);
            printf("(%d, %d)\n",
                (int)json_object_get_number(point, "x"),
                (int)json_object_get_number(point, "y")
            );
			x = ((int)json_object_get_number(point, "x") - 100)/50;
			y = ((int)json_object_get_number(point, "y") - 100)/50;

            x = 60 + 5*x;
            y = 60 + 5*y;
            
			printf("moveTo(%d, %d);\n",x ,y);
            fprintf(output, "moveTo(%d, %d)\n",x ,y);
            if(z == 1)
            {
                printf("riseUp(NO);\n");
                fprintf(output, "riseUp(NO);\n");
                z = 0;
            }
        }
        printf("riseUp(YES);\n");
        fprintf(output, "riseUp(YES);\n");
        printf("\n");
        fprintf(output, "\n");
    }
    printf("zero()\n");
    fprintf(output, "zero()\n");
    return 0;
}
