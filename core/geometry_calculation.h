# ifndef GEOMETRY_CALCULATION_H
# define GEOMETRY_CALCULATION_H

# include <cglm/cglm.h>

struct Position;
void calculate_model(struct Position*);

struct Camera;
void calculate_view(struct Camera*, struct Position*);
void calculate_projection(struct Camera*, struct Position*);

void calculate_mvp(struct Camera*, struct Position*, mat4);

# endif
