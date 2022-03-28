//
// Created by gracesheenxinran on 3/17/22.
//

#ifndef VIEW_TEXTURE_H
#define VIEW_TEXTURE_H

#endif //VIEW_TEXTURE_H

struct square {
    SDL_Rect rect;
    Uint32 colour;
};

int initialTexture(SDL_Renderer *ren,SDL_Texture *tex,SDL_Rect rect);
int displayTexture(SDL_Renderer *ren,SDL_Texture *tex);
int colorSurface(const int width,const int height);


void loadImage(SDL_Renderer *ren,SDL_Texture *texture);
void drawImage(SDL_Renderer *ren,SDL_Texture *tex);
