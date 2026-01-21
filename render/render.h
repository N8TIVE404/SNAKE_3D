#ifndef RENDER_H
#define RENDER_H

struct Mesh;
struct Camera;
struct Position;
void draw_mesh(struct Mesh *, struct Camera *, struct Position *, unsigned int,
               unsigned int);

struct Skybox;
void draw_skybox(struct Skybox *, struct Camera *, struct Position *,
                 unsigned int, unsigned int, unsigned int);

#endif
