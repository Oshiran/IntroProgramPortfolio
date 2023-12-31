#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void draw_text(const char * text, SDL_Renderer *renderer, TTF_Font* font, SDL_Color color){
		SDL_Surface * surface = TTF_RenderText_Solid(font, text, color);
	    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
    	int texW = 0, texH = 0;
    	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    	SDL_Rect dstrect = { 0, 0, texW, texH };
        SDL_RenderCopy(renderer, texture, NULL, &dstrect);
 		SDL_DestroyTexture(texture);
    	SDL_FreeSurface(surface);
}

int main(int argc, char* args[]) {
  	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	int x = 50, y =50;

	SDL_Window *window = SDL_CreateWindow(
        "Task 4",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, 0
    );

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

	// Text Related
    TTF_Font * font = TTF_OpenFont("arial.ttf", 25);
    SDL_Color color = { 255, 255, 255 };

	// Application state
	uint64_t frame = 0;
	bool isRunning = true;
	SDL_Event event;

	while (isRunning)
	{
		while (SDL_PollEvent(&event))
		{
            switch(event.type){
                // Handles OS "Exit" event 
                case SDL_QUIT:
                    isRunning = false;
                    break;
				case SDL_KEYDOWN:
					/************/
					// TODO: Animation Logic here + keyboard logic here
					/************/
					// Add more functions here
					switch (event.key.keysym.scancode)
					{
						case SDL_SCANCODE_LEFT:
						case SDL_SCANCODE_A:
							if (x > 0) {
								x = x - 25;
							}
							break;
						case SDL_SCANCODE_RIGHT:
						case SDL_SCANCODE_D:
							if (x < 450) {
								x = x + 25;
							}
							break;
						case SDL_SCANCODE_DOWN:
						case SDL_SCANCODE_S:
							if (y < 450) {
								y = y + 25;
							}
							break;
						case SDL_SCANCODE_UP:
						case SDL_SCANCODE_W:
							if (y > 0) {
								y = y - 25;
							}
							break;
					}

            }
		}

        // Draw black background
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
        
        /************/
        //! Draw Something here
		SDL_SetRenderDrawColor(renderer,0,225,10,255);
		SDL_Rect rect1 = {x,y,150,75};
		SDL_RenderFillRect(renderer, &rect1);
        /************/

		// Draw text
		char text[16];
		sprintf(text, "Frame %d", frame % 1000);
		draw_text(text, renderer, font, color);
		frame += 1;

        // Present Render to screen
        SDL_RenderPresent(renderer);

        SDL_Delay(100); // Delay 100 ms
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
    TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();

	return 0;
}

