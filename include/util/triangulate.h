#ifndef __interface_h
#define __interface_h

#ifdef __cplusplus
extern "C" {
#endif

#define TRUE 1
#define FALSE 0

extern int triangulate_polygon(int, int *, double (*)[2], int (*)[3]);
extern int is_point_inside_polygon(double *);

#ifdef __cplusplus
}
#endif

#endif /* __interface_h */
