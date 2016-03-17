#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_gfx/SDL2_gfxPrimitives.h>
#include "SDL2_own.h"
#include "Main.h"
#include "Timer.h"
#include "Tadpole.h"
#include "cleanup.h"
#include "Functions.h"

using namespace::std;

const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;
const int FRAMES_PER_SECOND = 20;			//Fps auf 20 festlegen

/*
 * Log an SDL error with some error message to the output stream of our choice
 * @param os The output stream to write the message too
 * @param msg The error message to write, format will be msg error: SDL_GetError()
 */
void logSDLError(std::ostream &os, const std::string &msg){
	os << msg << " error: " << SDL_GetError() << std::endl;
}

/*
 * Log an SDL debug output with some message to the output stream of our choice
 * @param os The output stream to write the message too
 * @param msg The message to write, format will be msg [DEBUG]: SDL_GetError()
 */
void logSDLDebug(std::ostream &os, const std::string &msg){
	os << " [DEBUG]: " << msg << std::endl;
}
void logSDLDebug(std::ostream &os, const int msg){
	os << " [DEBUG]: " << msg << std::endl;
}

/*
 * Loads an image into a texture on the rendering device
 * @param file The image file to load
 * @param ren The renderer to load the texture onto
 * @return the loaded texture, or NULL if something went wrong.
 */
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren){
	SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
	if (texture == NULL){
		logSDLError(std::cout, "LoadTexture");
	}
	return texture;
}

/*
 * Draw an SDL_Texture to an SDL_Renderer at position x, y, with some desired
 * width and height
 * @param tex The source texture we want to draw
 * @param rend The renderer we want to draw too
 * @param x The x coordinate to draw too
 * @param y The y coordinate to draw too
 * @param w The width of the texture to draw
 * @param h The height of the texture to draw
 */
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h){
	//Setup the destination rectangle to be at the position we want
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

/*
 * Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
 * the texture's width and height
 * @param tex The source texture we want to draw
 * @param rend The renderer we want to draw too
 * @param x The x coordinate to draw too
 * @param y The y coordinate to draw too
 */
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y){
	int w, h;
	SDL_QueryTexture(tex, NULL, NULL, &w, &h);
	renderTexture(tex, ren, x, y, w, h);
}

// Draw a tadpole to an SDL_Rederer
void drawTadpole(Tadpole *tad,  SDL_Renderer *ren, int ticks) {

    // x1 and y1 marks the middle of the head
    float xhead1f = (float)tad->x();
    float yhead1f = (float)tad->y();
    // x2 and y2 marks the end of the head
    float xhead2f = xhead1f - (float)tad->hsize();
    float yhead2f = yhead1f;
    float xnose1f = xhead1f + (float)tad->hsize();
    float ynose1f = yhead1f;
    
    float xeye0f = xnose1f + 130.0f;
    float yeye0f = ynose1f;
    
    float xeye1f = xnose1f + 100.0f;
    float yeye1f = ynose1f + 50.0f;
    float xeye2f = xnose1f + 110.0f;
    float yeye2f = ynose1f + 40.0f;
    float xeye3f = xnose1f + 120.0f;
    float yeye3f = ynose1f + 30.0f;
    float xeye4f = xnose1f + 125.0f;
    float yeye4f = ynose1f + 20.0f;
    
    float xeye5f = xnose1f + 100.0f;
    float yeye5f = ynose1f - 50.0f;
    float xeye6f = xnose1f + 110.0f;
    float yeye6f = ynose1f - 40.0f;
    float xeye7f = xnose1f + 120.0f;
    float yeye7f = ynose1f - 30.0f;
    float xeye8f = xnose1f + 125.0f;
    float yeye8f = ynose1f - 20.0f;
    
    //tail start
    float xtail1f = xhead2f;
    float ytail1f = yhead2f;
    //tail end
    float xtail2f = xhead2f - (float)tad->tsize();
    float ytail2f = yhead2f;
    
    float vxtadf = (float)tad->vx();
    float vytadf = (float)tad->vy();

    //the direction in respect to the world in which the tadpole moves
    float theta = getAngle(vxtadf, vytadf);
    
    //the absoulute velocity
    float vsq = sqrt(pow(vxtadf,2) + pow(vytadf,2));

    //the new position in the unrotated coordinate system
    float xhead1sf = 0.0f;
    float yhead1sf = 0.0f;
    float xhead2sf = xhead2f - xhead1f;
    float yhead2sf = yhead2f - yhead1f;
    float xtail1sf = xtail1f - xhead1f;
    float ytail1sf = ytail1f - yhead1f;
    float xtail2sf = xtail2f - xhead1f;
    float ytail2sf = ytail2f - yhead1f;
    float xnose1sf = xnose1f - xhead1f;
    float ynose1sf = ynose1f - yhead1f;
    
    float xeye0sf = xeye0f - xhead1f;
    float yeye0sf = yeye0f - yhead1f;
    
    float xeye1sf = xeye1f - xhead1f;
    float yeye1sf = yeye1f - yhead1f;
    float xeye2sf = xeye2f - xhead1f;
    float yeye2sf = yeye2f - yhead1f;
    float xeye3sf = xeye3f - xhead1f;
    float yeye3sf = yeye3f - yhead1f;
    float xeye4sf = xeye4f - xhead1f;
    float yeye4sf = yeye4f - yhead1f;
    
    float xeye5sf = xeye5f - xhead1f;
    float yeye5sf = yeye5f - yhead1f;
    float xeye6sf = xeye6f - xhead1f;
    float yeye6sf = yeye6f - yhead1f;
    float xeye7sf = xeye7f - xhead1f;
    float yeye7sf = yeye7f - yhead1f;
    float xeye8sf = xeye8f - xhead1f;
    float yeye8sf = yeye8f - yhead1f;

    //rotate back into the world coordinate system
    if (vsq != 0) {
        xhead1f = cos(theta)*xhead1sf - sin(theta)*yhead1sf + xhead1f;
        yhead1f = sin(theta)*xhead1sf + cos(theta)*yhead1sf + yhead1f;
        
        xhead2f = cos(theta)*xhead2sf - sin(theta)*yhead2sf + xhead1f;
        yhead2f = sin(theta)*xhead2sf + cos(theta)*yhead2sf + yhead1f;
        
        xtail1f = cos(theta)*xtail1sf - sin(theta)*ytail1sf + xhead1f;
        ytail1f = sin(theta)*xtail1sf + cos(theta)*ytail1sf + yhead1f;
        
        xtail2f = cos(theta)*xtail2sf - sin(theta)*ytail2sf + xhead1f;
        ytail2f = sin(theta)*xtail2sf + cos(theta)*ytail2sf + yhead1f;
        
        xnose1f = cos(theta)*xnose1sf - sin(theta)*ynose1sf + xhead1f;
        ynose1f = sin(theta)*xnose1sf + cos(theta)*ynose1sf + yhead1f;
        
        xeye0f = cos(theta)*xeye0sf - sin(theta)*yeye0sf + xhead1f;
        yeye0f = sin(theta)*xeye0sf + cos(theta)*yeye0sf + yhead1f;
        
        xeye1f = cos(theta)*xeye1sf - sin(theta)*yeye1sf + xhead1f;
        yeye1f = sin(theta)*xeye1sf + cos(theta)*yeye1sf + yhead1f;
        
        xeye2f = cos(theta)*xeye2sf - sin(theta)*yeye2sf + xhead1f;
        yeye2f = sin(theta)*xeye2sf + cos(theta)*yeye2sf + yhead1f;
        
        xeye3f = cos(theta)*xeye3sf - sin(theta)*yeye3sf + xhead1f;
        yeye3f = sin(theta)*xeye3sf + cos(theta)*yeye3sf + yhead1f;

        xeye4f = cos(theta)*xeye4sf - sin(theta)*yeye4sf + xhead1f;
        yeye4f = sin(theta)*xeye4sf + cos(theta)*yeye4sf + yhead1f;
        
        xeye5f = cos(theta)*xeye5sf - sin(theta)*yeye5sf + xhead1f;
        yeye5f = sin(theta)*xeye5sf + cos(theta)*yeye5sf + yhead1f;
        
        xeye6f = cos(theta)*xeye6sf - sin(theta)*yeye6sf + xhead1f;
        yeye6f = sin(theta)*xeye6sf + cos(theta)*yeye6sf + yhead1f;
        
        xeye7f = cos(theta)*xeye7sf - sin(theta)*yeye7sf + xhead1f;
        yeye7f = sin(theta)*xeye7sf + cos(theta)*yeye7sf + yhead1f;

        xeye8f = cos(theta)*xeye8sf - sin(theta)*yeye8sf + xhead1f;
        yeye8f = sin(theta)*xeye8sf + cos(theta)*yeye8sf + yhead1f;
    }
    
    //wiggle the tail
    int amptail = (int)(tad->hsize()*((float)sin(ticks*vsq/300)));
    
    //TODO: das sollte nicht in der Funktion stehen, die das Bild zeichnet.
    //reflect the velocity if the tadpole reaches the screen
    if (xhead1f < 0 || xhead1f > SCREEN_WIDTH) {
        tad->set_v(-tad->vx(),tad->vy());
    }
    if (yhead1f < 0 || yhead1f > SCREEN_HEIGHT) {
        tad->set_v(tad->vx(),-tad->vy());
    }
    
    //draw the tadpole
    filledEllipseRGBA(ren, (int)xhead1f, (int)yhead1f, tad->hsize(), tad->hsize(), 0, 0, 0, 255);
    filledEllipseRGBA(ren, (int)xnose1f, (int)ynose1f, 2, 2, 255, 0, 0, 255);
    curlRGBA(ren, (int)xtail1f, (int)ytail1f, (int)xtail2f, (int)ytail2f, amptail, 4, 2, 0, 0, 0, 255);
    //filledTrigonRGBA(ren, (int)xnose1f, (int)ynose1f, (int)xeye1f, (int)yeye1f, (int)xeye2f, (int)yeye2f, 0, 0, 255, 20);
    lineRGBA(ren, (int)xnose1f, (int)ynose1f, (int)xeye0f, (int)yeye0f, 0, 0, 255, 20);
    lineRGBA(ren, (int)xnose1f, (int)ynose1f, (int)xeye1f, (int)yeye1f, 0, 0, 255, 20);
    lineRGBA(ren, (int)xnose1f, (int)ynose1f, (int)xeye2f, (int)yeye2f, 0, 0, 255, 20);
    lineRGBA(ren, (int)xnose1f, (int)ynose1f, (int)xeye3f, (int)yeye3f, 0, 0, 255, 20);
    lineRGBA(ren, (int)xnose1f, (int)ynose1f, (int)xeye4f, (int)yeye4f, 0, 0, 255, 20);
    lineRGBA(ren, (int)xnose1f, (int)ynose1f, (int)xeye5f, (int)yeye5f, 0, 0, 255, 20);
    lineRGBA(ren, (int)xnose1f, (int)ynose1f, (int)xeye6f, (int)yeye6f, 0, 0, 255, 20);
    lineRGBA(ren, (int)xnose1f, (int)ynose1f, (int)xeye7f, (int)yeye7f, 0, 0, 255, 20);
    lineRGBA(ren, (int)xnose1f, (int)ynose1f, (int)xeye8f, (int)yeye8f, 0, 0, 255, 20);
}

int main( int argc, char* args[] ) {

	int frame = 0; //Buch führen bei welchem Frame das Programm gerade ist
	bool cap = true; //Framecap an oder ausschalten
    
    //Timer zum festlegen der FPS
	Timer fps;
    //Timer zum errechnen der weltweit vergangenen Zeit
	Timer worldtime;
    worldtime.start();
    
    //calculate the small time between two frames in ms
    int oldTime = 0;
    int newTime = 0;
    int dt = 0;

	//Start up SDL and make sure it went ok
	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		logSDLError(std::cout, "SDL_Init");
		return 1;
	}

	//Setup our window and renderer, this time let's put our window in the center
	//of the screen
	SDL_Window *window = SDL_CreateWindow("Evolution", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL){
		logSDLError(std::cout, "CreateWindow");
		SDL_Quit();
		return 1;
	}
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL){
		logSDLError(std::cout, "CreateRenderer");
		cleanup(window);
		SDL_Quit();
		return 1;
	}

    //generate a new creature
    Tadpole tadpole(15,100,100,10,50); //= Kaulquappe

	//Our event structure
	SDL_Event e;
	//For tracking if we want to quit
	bool quit = false;

    
	while (!quit){
        //start the fps timer
        fps.start();
        
		//Read any events that occured, for now we'll just quit if any event occurs
		while (SDL_PollEvent(&e)){
			//If user closes the window
			if (e.type == SDL_QUIT){
				quit = true;
			}
			//If user presses any key
			if (e.type == SDL_KEYDOWN){
                //do something
				if( e.key.keysym.sym == SDLK_c ) { //Falls c gedrückt wurde
                    cap = !cap;
				}
                if ( e.key.keysym.sym == SDLK_DOWN) {
                    tadpole.set_v(tadpole.vx(),tadpole.vy() + 1);
                }
                if ( e.key.keysym.sym == SDLK_UP) {
                    tadpole.set_v(tadpole.vx(),tadpole.vy() - 1);
                }
                if ( e.key.keysym.sym == SDLK_LEFT) {
                    tadpole.set_v(tadpole.vx() - 1,tadpole.vy());
                }
                if ( e.key.keysym.sym == SDLK_RIGHT) {
                    tadpole.set_v(tadpole.vx() + 1,tadpole.vy());
                }
			}
			//If user clicks the mouse
			if (e.type == SDL_MOUSEBUTTONDOWN){
				//do something
			}
		}
        
        //Rendering
		SDL_RenderClear(renderer);
		//Draw the background white
        boxRGBA(renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 255, 255, 255, 255);
    
        //draw one tadpole
        drawTadpole(&tadpole, renderer, worldtime.getTicks());
        
		//update the screen and all objects
        tadpole.update_position();
		SDL_RenderPresent(renderer);
        
        // Timer related stuff
        oldTime = newTime;
        newTime = worldtime.getTicks();
        if (newTime > oldTime) {
            dt = newTime - oldTime; // small time between two frames in ms
        }
        
        //increment the frame number
        frame++;
        //apply the fps cap
		if( (cap == true) && (fps.getTicks() < 1000/FRAMES_PER_SECOND) ) {
			SDL_Delay( (1000/FRAMES_PER_SECOND) - fps.getTicks() );
		}
            
        //update the window caption
		if( worldtime.getTicks() > 1000 ) {
			std::stringstream caption;
			caption << "Evolution, aktuelle FPS: " << 1000.f*frame/worldtime.getTicks();
            SDL_SetWindowTitle(window,caption.str().c_str());
			worldtime.start();
            frame = 0;
		}
	}
    
	//Destroy the various items
	cleanup(renderer, window);
	IMG_Quit();
	SDL_Quit();

	return 0;
}