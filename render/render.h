# ifndef RENDER_H
# define RENDER_H

extern const char *textureStrings[];
struct Mesh;
struct Camera;
struct Position;
void draw_mesh(struct Camera*, struct Position*, struct Mesh*, unsigned int);

# endif
