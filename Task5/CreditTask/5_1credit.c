#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <time.h> 
#include <stdlib.h> 

void displayMouseCoordinates(SDL_Renderer* renderer, TTF_Font* font) {
    SDL_Color textColor = {255, 100, 100, 255}; // White text color
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    char text[50];
    TTF_Font* font2 = TTF_OpenFont("arial.ttf", 20);
    snprintf(text, sizeof(text), "Mouse X: %d, Mouse Y: %d", mouseX, mouseY);
    SDL_Surface* surface = TTF_RenderText_Solid(font2, text, textColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    int texW = 0, texH = 0;
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    SDL_Rect dstrect = {10, 280, texW, texH};
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void draw_button(const char *text, SDL_Renderer *renderer, TTF_Font *font, SDL_Color color, SDL_Rect *dstrect, bool hover)
{
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    int texW = 0, texH = 0;
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    dstrect->w = texW;
    dstrect->h = texH;

    if (hover)
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, dstrect);
    }else
    {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, dstrect);
    }

    SDL_RenderCopy(renderer, texture, NULL, dstrect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

int main(int argc, char *args[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    int x = 50, y = 50, w = 50;

    SDL_Window *window = SDL_CreateWindow(
        "Task 5",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 300, 300, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    // Text Related
    TTF_Font *font = TTF_OpenFont("arial.ttf", 25);
    SDL_Color color = {255, 255, 255};

    // Application state
    bool isRunning = true;
    bool clicked = false;
    bool hover = false;
    SDL_Event event;
    srand(time(NULL)); 
    SDL_Rect dstrect; 

    while (isRunning)
    {
        if (SDL_PollEvent(&event) > 0)
        {
            switch (event.type)
            {
                // Handles OS "Exit" event
            case SDL_QUIT:
                isRunning = false;
                break;

            case SDL_MOUSEMOTION:
                {
                    int mouseX = event.motion.x;
                    int mouseY = event.motion.y;
                    if (mouseX > dstrect.x && mouseX < dstrect.x + dstrect.w && mouseY > dstrect.y && mouseY < dstrect.y + dstrect.h)
                    {
                        hover = true; 
                    }else 
                    {
                        hover = false; 
                    }
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT && hover) { 
                    printf("\nwe are button");
                    clicked = true;
                    x = rand() % 200; 
                    y = rand() % 200; 
                    w = w + 1;
                }
                else
                {
                    printf("\nNot in button");
                    clicked = false;
                }
                break;
            }
        }

        // Draw black background
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw text
        if (clicked)
        {
            draw_button("Clicked", renderer, font, color, &dstrect, hover); 
        }
        else
        {
            draw_button("Click me", renderer, font, color, &dstrect, hover); 
        }
        displayMouseCoordinates(renderer, font);
        dstrect.x = x;
        dstrect.y = y;

        // Present Render to screen
        SDL_RenderPresent(renderer);
        SDL_Delay(50); // Delay 50 ms
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
