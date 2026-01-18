#ifndef MVP_H
#define MVP_H

#include <cglm/cglm.h>

struct Camera;
struct Position;

void calculate_model(struct Camera *, struct Position *);
void calculate_view(struct Camera *, struct Position *);
void calculate_projection(struct Camera *, struct Position *);
void calculate_mvp(struct Camera *, struct Position *);

#endif
