#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 800
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define INTERVAL_ADD_MS 5000
#define INTERVAL_TARGET_MS 3000
#define INTERVAL_MOVE_MS 50
#define MAX_FOOD 8
uint64_t last_tick_add;
uint64_t last_tick_move;
uint64_t last_tick_target;

typedef enum eatflag{
    WRONG,
    CORRECT,
    NOTHING
} EatFlag;

typedef struct food{
    bool available;
    int x;
    int y;
    int dir_x;
    int dir_y;
    int food_index;
    int SmokeTime;
    SDL_Texture *texture;
    SDL_Texture *Smoke_Texture;
} Food;

typedef struct hunter{
    int x;
    int y;
    int target_food_index;
    SDL_Texture *texture_target_food;
    SDL_Texture *texture_hunter;
} Hunter;

void draw_score(SDL_Renderer *renderer, TTF_Font *font, int score) 
{
    int texW = 0, texH = 0;
    char text[16];

    SDL_Color text_color = {255, 255, 255};

    sprintf(text, "Score : %d", score);

    SDL_Surface *surface = TTF_RenderText_Solid(font, text, text_color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    SDL_Rect dstrect = {0, 0, texW, texH};
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void draw_background(SDL_Renderer *renderer, SDL_Texture *background) {
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = SCREEN_WIDTH;
    rect.h = SCREEN_HEIGHT;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background, NULL, &rect);
}

void draw_hunter(SDL_Renderer *renderer, Hunter hunter) {
    SDL_Rect rect;
    SDL_Rect target_rect;

    rect.x = hunter.x;
    rect.y = hunter.y;
    rect.w = 100;
    rect.h = 100;

    target_rect.x = hunter.x + 37.5;
    target_rect.y = hunter.y + 50;
    target_rect.w = 25;
    target_rect.h = 25;
    SDL_RenderCopy(renderer, hunter.texture_hunter, NULL, &rect);
    SDL_RenderCopy(renderer, hunter.texture_target_food, NULL, &target_rect);
}

EatFlag hunter_eat_food(Hunter hunter, Food *food_array) {
    for (int i = 0; i < MAX_FOOD; i++) {
        if (food_array[i].available) {
            int distance_from_mouth_x = abs((food_array[i].x + 35) - (hunter.x + 50));
            int distance_from_mouth_y = abs((food_array[i].y + 35) - (hunter.y + 50));

            if ((distance_from_mouth_x < 20) && (distance_from_mouth_y < 20)) {
                food_array[i].available = false;
                if (food_array[i].food_index == hunter.target_food_index) {
                    return CORRECT;
                }
                else {
                    return WRONG;
                }
            }
        }
    }
    return NOTHING;
}

void change_hunter_target(Hunter *hunter, SDL_Texture **texture_small_food) {
    if (SDL_GetTicks() - last_tick_target > INTERVAL_TARGET_MS) {
        last_tick_target = SDL_GetTicks();
        (*hunter).target_food_index = rand() % 4;
        (*hunter).texture_target_food = texture_small_food[(*hunter).target_food_index];
    }
}

void add_or_move_food(Food *food_array, SDL_Texture **texture_food, SDL_Texture *texture_smoke, int *food_index) {
    bool should_move_food = false;

    if (SDL_GetTicks() - last_tick_move > INTERVAL_MOVE_MS) {
        should_move_food = true;
        last_tick_move = SDL_GetTicks();
    }

    if (should_move_food) {
        for (int i = 0; i < MAX_FOOD; i++) {
            if (food_array[i].available) {
                if (rand() % 100 < 2.5) {
                    food_array[i].Smoke_Texture = texture_smoke;
                    food_array[i].SmokeTime = 200;
                    food_array[i].dir_x = -5 + rand() % 10;
                    food_array[i].dir_y = -5 + rand() % 10;
                }
                if (food_array[i].x >= 0 && food_array[i].x <= SCREEN_WIDTH) {
                    food_array[i].x += food_array[i].dir_x;
                }
                else if (food_array[i].x > SCREEN_WIDTH) {
                    food_array[i].x = 0;
                }
                else {
                    food_array[i].x = SCREEN_WIDTH;
                }

                if (food_array[i].y >= 0 && food_array[i].y <= SCREEN_HEIGHT) {
                    food_array[i].y += food_array[i].dir_y;
                }
                else if (food_array[i].y > SCREEN_HEIGHT) {
                    food_array[i].y = 0;
                }
                else {
                    food_array[i].y = SCREEN_HEIGHT;
                }
            }
        }
    }

    bool should_add_food = false;

    if (SDL_GetTicks() - last_tick_add > INTERVAL_ADD_MS) {
        should_add_food = true;
        last_tick_add = SDL_GetTicks();
    }

    if (should_add_food) {
        Food new_food;

        new_food.available = true;
        new_food.food_index = rand() % 4;
        new_food.texture = texture_food[new_food.food_index];
        new_food.x = rand() % SCREEN_WIDTH;
        new_food.y = rand() % SCREEN_HEIGHT;

        new_food.dir_x = -5 + rand() % 10;
        new_food.dir_y = -5 + rand() % 10;

        if (*food_index < MAX_FOOD) {
            food_array[*food_index] = new_food;
            (*food_index) += 1;
        }
        else {
            (*food_index) = 0;
        }
    }
}

void draw_food(SDL_Renderer *renderer, Food *food_array) {
    for (int i = 0; i < MAX_FOOD; i++) {
        if (food_array[i].available) {
            SDL_Rect rect;
            rect.x = food_array[i].x;
            rect.y = food_array[i].y;
            rect.w = 70;
            rect.h = 70;
            SDL_RenderCopy(renderer, food_array[i].texture, NULL, &rect);

            if (food_array[i].Smoke_Texture) {
                SDL_RenderCopy(renderer, food_array[i].Smoke_Texture, NULL, &rect);
                if (--food_array[i].SmokeTime <= 0) {
                    food_array[i].Smoke_Texture = NULL;
                }
            }
        }
    }
}

int main(int argc, char **argv) {
    srand(time(NULL));

    bool quit = false;
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    IMG_Init(IMG_INIT_PNG);

    TTF_Font *font = TTF_OpenFont("media/arial.ttf", 25);

    SDL_Window *window = SDL_CreateWindow("Food Hunter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
    Mix_Chunk *audio_yuk = Mix_LoadWAV("media/Yuk.wav");
    Mix_Chunk *audio_yum = Mix_LoadWAV("media/Yum.wav");

    SDL_Surface *img_space = IMG_Load("media/space.png");
    SDL_Surface *img_hunter = IMG_Load("media/Hunter.png");
    SDL_Surface *img_burger = IMG_Load("media/Burger.png");
    SDL_Surface *img_chips = IMG_Load("media/Chips.png");
    SDL_Surface *img_icecream = IMG_Load("media/Icecream.png");
    SDL_Surface *img_pizza = IMG_Load("media/Pizza.png");
    SDL_Surface *img_small_burger = IMG_Load("media/SmallBurger.png");
    SDL_Surface *img_small_chips = IMG_Load("media/SmallChips.png");
    SDL_Surface *img_small_icecream = IMG_Load("media/SmallIcecream.png");
    SDL_Surface *img_small_pizza = IMG_Load("media/SmallPizza.png");
    SDL_Surface *img_smoke = IMG_Load("media/smoke.png");

    SDL_Texture *texture_space = SDL_CreateTextureFromSurface(renderer, img_space);
    SDL_Texture *texture_hunter = SDL_CreateTextureFromSurface(renderer, img_hunter);
    SDL_Texture *texture_food[4] = 
    {
        SDL_CreateTextureFromSurface(renderer, img_burger),
        SDL_CreateTextureFromSurface(renderer, img_chips),
        SDL_CreateTextureFromSurface(renderer, img_icecream),
        SDL_CreateTextureFromSurface(renderer, img_pizza)
    };

    SDL_Texture *texture_small_food[4] = 
    {
        SDL_CreateTextureFromSurface(renderer, img_small_burger),
        SDL_CreateTextureFromSurface(renderer, img_small_chips),
        SDL_CreateTextureFromSurface(renderer, img_small_icecream),
        SDL_CreateTextureFromSurface(renderer, img_small_pizza)
    };
    SDL_Texture *texture_smoke = SDL_CreateTextureFromSurface(renderer, img_smoke);

    SDL_FreeSurface(img_space);
    SDL_FreeSurface(img_hunter);
    SDL_FreeSurface(img_burger);
    SDL_FreeSurface(img_chips);
    SDL_FreeSurface(img_icecream);
    SDL_FreeSurface(img_pizza);
    SDL_FreeSurface(img_small_burger);
    SDL_FreeSurface(img_small_chips);
    SDL_FreeSurface(img_small_icecream);
    SDL_FreeSurface(img_small_pizza);
    SDL_FreeSurface(img_smoke);

    int food_renewal_idx = 0;
    Food food_array[MAX_FOOD] = {
        {.available = false},
        {.available = false},
        {.available = false},
        {.available = false},
        {.available = false},
        {.available = false},
        {.available = false},
        {.available = false}
    };

    Hunter hunter;
    hunter.texture_hunter = texture_hunter;
    hunter.texture_target_food = texture_small_food[0];
    hunter.x = 350;
    hunter.y = 250;

    int score = 0;

    const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);
    int frameCounter = 0;

    while (!quit) {
        while (SDL_PollEvent(&event)) 
        {
            if (event.type == SDL_QUIT) 
            {
                quit = true;
            }
        }

        if (frameCounter % 2 == 0) {
            if (keyboardState[SDL_SCANCODE_W]) {
                hunter.y -= 1;
            }
            if (keyboardState[SDL_SCANCODE_A]) {
                hunter.x -= 1;
            }
            if (keyboardState[SDL_SCANCODE_S]) {
                hunter.y += 1;
            }
            if (keyboardState[SDL_SCANCODE_D]) {
                hunter.x += 1;
            }
            if (keyboardState[SDL_SCANCODE_UP]) {
                hunter.y -= 1;
            }
            if (keyboardState[SDL_SCANCODE_LEFT]) {
                hunter.x -= 1;
            }
            if (keyboardState[SDL_SCANCODE_DOWN]) {
                hunter.y += 1;
            }
            if (keyboardState[SDL_SCANCODE_RIGHT]) {
                hunter.x += 1;
            }
        }

        frameCounter++;

        add_or_move_food(food_array, texture_food, texture_smoke, &food_renewal_idx);
        change_hunter_target(&hunter, texture_small_food);

        switch(hunter_eat_food(hunter, food_array)) {
            case WRONG:
                score -= 1;
                Mix_PlayChannel(-1, audio_yuk, 0);
                break;
            case CORRECT:
                score += 1;
                Mix_PlayChannel(-1, audio_yum, 0);
                break;
            default:
        }

        draw_background(renderer, texture_space);
        draw_food(renderer, food_array);
        draw_hunter(renderer, hunter);
        draw_score(renderer, font, score);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture_space);
    SDL_DestroyTexture(texture_hunter);
    SDL_DestroyTexture(texture_smoke);

    for (int i = 0; i < 4; i++){
        SDL_DestroyTexture(texture_food[i]);
        SDL_DestroyTexture(texture_small_food[i]);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    Mix_FreeChunk(audio_yuk);
    Mix_FreeChunk(audio_yum);

    TTF_CloseFont(font);

    TTF_Quit();
    IMG_Quit();
    Mix_CloseAudio();
    Mix_Quit();
    SDL_Quit();

    return 0;
}
