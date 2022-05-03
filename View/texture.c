//
// Created by gracesheenxinran on 3/17/22.
//

#include "SDL2/SDL.h"
#include "main_view.h"


int initialTexture(SDL_Renderer *ren,SDL_Texture *tex,SDL_Rect rect)
{
    tex = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET, 200, 200);

    SDL_SetRenderDrawColor(ren, 255, 250, 250, 255); /* On dessine en blanc */

    SDL_SetRenderTarget(ren, tex);
    SDL_RenderFillRect(ren, &rect);
    SDL_SetRenderTarget(ren, NULL);
}

int displayTexture(SDL_Renderer *ren,SDL_Texture *tex)
{
    SDL_RenderCopy(ren, tex, NULL, NULL);
}

int colorSurface(const int width,const int height)
{
//    const SDL_PixelFormat* format;
    SDL_Surface *surface;

    surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
    // change the colour here
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 255, 255));
}


int iconWindow(SDL_Window *window, SDL_Surface *surface)
{
    size_t i;
    struct square squareImage[4] = {
            { {  4,  4, 10, 10 }, SDL_MapRGB(surface->format, 0, 0, 0) }, /* black */
            { {  4, 18, 10, 10 }, SDL_MapRGB(surface->format, 0, 0, 255) }, /* blue */
            { { 18,  4, 10, 10 }, SDL_MapRGB(surface->format, 0, 255, 0) }, /* green */
            { { 18, 18, 10, 10 }, SDL_MapRGB(surface->format, 255, 255, 255) } /* white */
    };

    /* On remplit notre surface grâce à nos carrés. */
    for (i = 0; i < 4; i++) {
        SDL_FillRect(surface, &squareImage[i].rect, squareImage[i].colour);
    }

    SDL_SetWindowIcon(window, surface);
    SDL_Delay(2000);
    return 0;
}

int loadImage(SDL_Renderer *ren,SDL_Texture *texture,SDL_Surface *surface) {
    SDL_Texture *tmp = NULL;

    if(NULL == surface)
    {
        fprintf(stderr, "Error SDL_LoadBMP : %s\n", SDL_GetError());
        SDL_DestroyRenderer(ren);
        SDL_Quit();
        return 1;
    }

    tmp = SDL_CreateTextureFromSurface(ren, surface);
    SDL_FreeSurface(surface); /* On libère la surface, on n’en a plus besoin */

    if(NULL == tmp)
    {
        fprintf(stderr, "Error SDL_CreateTextureFromSurface : %s", SDL_GetError());
    }

    texture = tmp;
}

void drawImage(SDL_Renderer *ren,SDL_Texture *tex)
{
    SDL_Surface *surface = NULL;
    SDL_Texture *tmp = NULL;
    surface = SDL_LoadBMP("test.bmp");

    loadImage(ren,tmp,surface);
    tex = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, surface->w, surface->h);

    SDL_SetRenderTarget(ren, tex); /* La cible de rendu est maintenant texture. */
    SDL_RenderCopy(ren, tmp, NULL, NULL); /* On copie tmp sur texture */
    SDL_DestroyTexture(tmp);
    SDL_FreeSurface(surface);
    SDL_SetRenderTarget(ren, NULL); /* La cible de rendu est de nouveau le renderer. */
    /* Now we can draw on our texture */
}
