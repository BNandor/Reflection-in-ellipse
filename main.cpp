#include <iostream>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <math.h>
#include "SDL2_gfxPrimitives.h"

#define W_HEIGHT 1024
#define W_WIDTH 1024
// #define A  500.0
// #define B  400.0
// #define C 300.0

// #define ref1 3
// #define ref2 10
// #define ref3 30
// #define ref4 60

#ifndef SCALE
#define SCALE 3
#endif

class ellipse
{
protected:
struct F{
		long double x,y;
	}focus;
public:

	double A,B,C;
	int ref1;
	bool continue_drawing;

	ellipse(double A,double B,double C,int ref):A(A),B(B),C(C),ref1(ref){

		continue_drawing=true;

		initG();	
	}	

	long double  getEllipseY(long double x);
	void set_focus(double C);
	void update_C(){
		C = sqrt(A*A - B*B);
	}
	virtual ~ellipse();
	
	
	void visualize();
	void reflect();
	void clear(){
    		SDL_RenderClear( renderer );
	}

protected:

	

	void initG();
	void setRcolor(int ,int,int,int);
    	SDL_Window* window;
    	SDL_Renderer* renderer;

	
};

void ellipse::setRcolor(int r,int g,int b,int a){

    SDL_SetRenderDrawColor( renderer, r, g, b, a);
}

void ellipse::initG(){

   		 window = SDL_CreateWindow
   		 (
   		     "ellipszis", SDL_WINDOWPOS_UNDEFINED,
   		     SDL_WINDOWPOS_UNDEFINED,
   		     W_HEIGHT,
   		     W_WIDTH,
   		     SDL_WINDOW_SHOWN
   		 );
    renderer =  SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);

}

ellipse::~ellipse(){
    SDL_DestroyWindow(window);
    SDL_Quit();
}


void ellipse::visualize(){
	
	
	 ellipseRGBA( renderer,  W_WIDTH /2, W_HEIGHT/2,A, B,255,255, 255, 255);
    
}

long double  ellipse::getEllipseY(long double x){
	return (long double)B*(sqrt(1.0-(long double)((x*x)/(A*A))));
}

void ellipse::set_focus(double C){
	focus.x = (long double)-C;
	focus.y = 0.0;
}
void ellipse::reflect(){
	visualize();
	
	

	set_focus(C);

	// SDL_Rect frect1;
	// frect1.x = -focus.x + W_WIDTH /2 ;
	// frect1.y = focus.y+W_HEIGHT/2;
	// frect1.w = 10;
	// frect1.h = 10;

	// SDL_Rect frect2;
	// frect2.x = focus.x + W_WIDTH /2 ;
	// frect2.y = focus.y+W_HEIGHT/2;
	// frect2.w = 10;
	// frect2.h = 10;

	long double m,n;
	long double ml,nl;
	long double rx,ry;
	long double newx1,newx2,newy1,newy2;
	long double nextx,nexty;
	int p;
	do{
		for(long double x=0;x<A;x++){
			SDL_PollEvent(NULL);
			setRcolor(0,0,0,255);
			SDL_RenderClear( renderer );

			SDL_Delay(10);
			long double y = getEllipseY(x);

			long double lastx,lasty;
			lastx = focus.x;
			lasty = focus.y;
			nextx = x;
			nexty = y;

			for (int i = 0; i < ref1; ++i)
			{
				if(!continue_drawing)break;
				setRcolor(0,255,0,255);
				m = (long double)(A*A*(long double)nexty)/(B*B*(long double)nextx);
				n = nexty - (long double)(A*A*nexty)/(long double)(B*B);

				rx = lastx *((1.0 -m*m)/(1.0 + m*m)) + lasty*((2.0*m)/(1.0 + m*m)) - ((n*2.0*m)/(1.0 + m*m));
				ry = lastx *((2.0*m)/(1.0 + m*m)) - lasty *((1.0 -m*m)/(1.0 + m*m)) + ((n*2.0)/(1.0 + m*m));
				
				ml = (ry - nexty)/(rx - nextx);
				nl = -ml*rx +ry;

				newx1 = (-A*A*2.0*ml*nl + sqrt(A*A*A*A*4.0*ml*ml*nl*nl - 4.0*(A*A*(nl*nl-B*B))*(A*A*ml*ml+B*B)))/(2.0*(A*A*ml*ml+B*B));
				newx2 = (-A*A*2.0*ml*nl - sqrt(A*A*A*A*4.0*ml*ml*nl*nl - 4.0*(A*A*(nl*nl-B*B))*(A*A*ml*ml+B*B)))/(2.0*(A*A*ml*ml+B*B));		

				SDL_RenderDrawLine(renderer,W_WIDTH /2 +lastx,W_HEIGHT/2 + lasty,W_WIDTH /2  + nextx ,W_HEIGHT/2 + nexty);
				SDL_RenderDrawLine(renderer,W_WIDTH /2  + newx2 ,W_HEIGHT/2 + newx2*ml + nl,W_WIDTH /2  + newx1 ,W_HEIGHT/2 + newx1*ml + nl);
				
				if(abs(nextx-newx2) <1.0 && abs(nexty-newx2*ml - nl) <1.0 ){
					lastx = newx2;
					lasty = newx2*ml + nl;
					nextx = newx1;
					nexty = newx1*ml + nl;
				}else{
					lastx = newx1;
					lasty = newx1*ml + nl;
					nextx = newx2;
					nexty = newx2*ml + nl;
				}

			}
			if(!continue_drawing)break;
			// SDL_RenderFillRect(renderer,&frect1);
			// SDL_RenderFillRect(renderer,&frect2);
			visualize();
			SDL_RenderPresent(renderer);
			//int p;std::cin>>p;

		}

		for(long double x=A;x>0;--x){
			SDL_PollEvent(NULL);
			setRcolor(0,0,0,255);
			SDL_RenderClear( renderer );

			SDL_Delay(10);
			long double y = getEllipseY(x);
			
			long double lastx,lasty;
			lastx = focus.x;
			lasty = focus.y;
			nextx = x;
			nexty = -y;

			for (int i = 0; i < ref1; ++i)
			{
				if(!continue_drawing)break;
				setRcolor(0,0,255,255);
				m = (long double)(A*A*(long double)nexty)/(B*B*(long double)nextx);
				n = nexty - (long double)(A*A*nexty)/(long double)(B*B);

				rx = lastx *((1.0 -m*m)/(1.0 + m*m)) + lasty*((2.0*m)/(1.0 + m*m)) - ((n*2.0*m)/(1.0 + m*m));
				ry = lastx *((2.0*m)/(1.0 + m*m)) - lasty *((1.0 -m*m)/(1.0 + m*m)) + ((n*2.0)/(1.0 + m*m));
				
				ml = (ry - nexty)/(rx - nextx);
				nl = -ml*rx +ry;

				newx1 = (-A*A*2.0*ml*nl + sqrt(A*A*A*A*4.0*ml*ml*nl*nl - 4.0*(A*A*(nl*nl-B*B))*(A*A*ml*ml+B*B)))/(2.0*(A*A*ml*ml+B*B));
				newx2 = (-A*A*2.0*ml*nl - sqrt(A*A*A*A*4.0*ml*ml*nl*nl - 4.0*(A*A*(nl*nl-B*B))*(A*A*ml*ml+B*B)))/(2.0*(A*A*ml*ml+B*B));		

				SDL_RenderDrawLine(renderer,W_WIDTH /2 +lastx,W_HEIGHT/2 + lasty,W_WIDTH /2  + nextx ,W_HEIGHT/2 + nexty);
				SDL_RenderDrawLine(renderer,W_WIDTH /2  + newx2 ,W_HEIGHT/2 + newx2*ml + nl,W_WIDTH /2  + newx1 ,W_HEIGHT/2 + newx1*ml + nl);
				
				if(abs(nextx-newx2) <1.0 && abs(nexty-newx2*ml - nl) <1.0 ){
					lastx = newx2;
					lasty = newx2*ml + nl;
					nextx = newx1;
					nexty = newx1*ml + nl;
				}else{
					lastx = newx1;
					lasty = newx1*ml + nl;
					nextx = newx2;
					nexty = newx2*ml + nl;
				}

			}
			if(!continue_drawing)break;
			// SDL_RenderFillRect(renderer,&frect1);
			// SDL_RenderFillRect(renderer,&frect2);
			visualize();
			SDL_RenderPresent(renderer);
			//int p;std::cin>>p;

		}
		
		
		
		

	for(long double x=0;x<A;x++){
			SDL_PollEvent(NULL);
			setRcolor(0,0,0,255);
			SDL_RenderClear( renderer );

			SDL_Delay(10);

			long double y = getEllipseY(x);

			long double lastx,lasty;
			lastx = focus.x;
			lasty = focus.y;
			nextx = -x;
			nexty = -y;

			for (int i = 0; i < ref1; ++i)
			{
				if(!continue_drawing)break;
				setRcolor(255,0,0,255);
				m = (long double)(A*A*(long double)nexty)/(B*B*(long double)nextx);
				n = nexty - (long double)(A*A*nexty)/(long double)(B*B);

				rx = lastx *((1.0 -m*m)/(1.0 + m*m)) + lasty*((2.0*m)/(1.0 + m*m)) - ((n*2.0*m)/(1.0 + m*m));
				ry = lastx *((2.0*m)/(1.0 + m*m)) - lasty *((1.0 -m*m)/(1.0 + m*m)) + ((n*2.0)/(1.0 + m*m));
				
				ml = (ry - nexty)/(rx - nextx);
				nl = -ml*rx +ry;

				newx1 = (-A*A*2.0*ml*nl + sqrt(A*A*A*A*4.0*ml*ml*nl*nl - 4.0*(A*A*(nl*nl-B*B))*(A*A*ml*ml+B*B)))/(2.0*(A*A*ml*ml+B*B));
				newx2 = (-A*A*2.0*ml*nl - sqrt(A*A*A*A*4.0*ml*ml*nl*nl - 4.0*(A*A*(nl*nl-B*B))*(A*A*ml*ml+B*B)))/(2.0*(A*A*ml*ml+B*B));		

				SDL_RenderDrawLine(renderer,W_WIDTH /2 +lastx,W_HEIGHT/2 + lasty,W_WIDTH /2  + nextx ,W_HEIGHT/2 + nexty);
				SDL_RenderDrawLine(renderer,W_WIDTH /2  + newx2 ,W_HEIGHT/2 + newx2*ml + nl,W_WIDTH /2  + newx1 ,W_HEIGHT/2 + newx1*ml + nl);
				
				if(abs(nextx-newx2) <1.0 && abs(nexty-newx2*ml - nl) <1.0 ){
					lastx = newx2;
					lasty = newx2*ml + nl;
					nextx = newx1;
					nexty = newx1*ml + nl;
				}else{
					lastx = newx1;
					lasty = newx1*ml + nl;
					nextx = newx2;
					nexty = newx2*ml + nl;
				}

			}
			if(!continue_drawing)break;
			// SDL_RenderFillRect(renderer,&frect1);
			// SDL_RenderFillRect(renderer,&frect2);
			visualize();
			SDL_RenderPresent(renderer);
			//int p;std::cin>>p;

		}
		
		for(long double x=A;x>0;--x){
			SDL_PollEvent(NULL);
			setRcolor(0,0,0,255);
			SDL_RenderClear( renderer );

			SDL_Delay(10);
			long double y = getEllipseY(x);
			
			long double lastx,lasty;
			lastx = focus.x;
			lasty = focus.y;
			nextx = -x;
			nexty = y;

			for (int i = 0; i < ref1; ++i)
			{
				if(!continue_drawing)break;
				setRcolor(0,255,255,255);
				m = (long double)(A*A*(long double)nexty)/(B*B*(long double)nextx);
				n = nexty - (long double)(A*A*nexty)/(long double)(B*B);

				rx = lastx *((1.0 -m*m)/(1.0 + m*m)) + lasty*((2.0*m)/(1.0 + m*m)) - ((n*2.0*m)/(1.0 + m*m));
				ry = lastx *((2.0*m)/(1.0 + m*m)) - lasty *((1.0 -m*m)/(1.0 + m*m)) + ((n*2.0)/(1.0 + m*m));
				
				ml = (ry - nexty)/(rx - nextx);
				nl = -ml*rx +ry;

				newx1 = (-A*A*2.0*ml*nl + sqrt(A*A*A*A*4.0*ml*ml*nl*nl - 4.0*(A*A*(nl*nl-B*B))*(A*A*ml*ml+B*B)))/(2.0*(A*A*ml*ml+B*B));
				newx2 = (-A*A*2.0*ml*nl - sqrt(A*A*A*A*4.0*ml*ml*nl*nl - 4.0*(A*A*(nl*nl-B*B))*(A*A*ml*ml+B*B)))/(2.0*(A*A*ml*ml+B*B));		

				SDL_RenderDrawLine(renderer,W_WIDTH /2 +lastx,W_HEIGHT/2 + lasty,W_WIDTH /2  + nextx ,W_HEIGHT/2 + nexty);
				SDL_RenderDrawLine(renderer,W_WIDTH /2  + newx2 ,W_HEIGHT/2 + newx2*ml + nl,W_WIDTH /2  + newx1 ,W_HEIGHT/2 + newx1*ml + nl);
				
				if(abs(nextx-newx2) <1.0 && abs(nexty-newx2*ml - nl) <1.0 ){
					lastx = newx2;
					lasty = newx2*ml + nl;
					nextx = newx1;
					nexty = newx1*ml + nl;
				}else{
					lastx = newx1;
					lasty = newx1*ml + nl;
					nextx = newx2;
					nexty = newx2*ml + nl;
				}

			}
			if(!continue_drawing)break;
			// SDL_RenderFillRect(renderer,&frect1);
			// SDL_RenderFillRect(renderer,&frect2);
			visualize();
			SDL_RenderPresent(renderer);
			

		}
		
	}while(continue_drawing);
	
	
}

void ellipse_drawer(ellipse &e){

	e.visualize();
	e.reflect();
}

void update_ellipse(ellipse & e){

	SDL_Event event;
	bool pressed_shift=true;

	while(e.continue_drawing){

		while( SDL_PollEvent( &event ) ){
			
		        switch( event.type ){
		            /* Look for a keypress */
		            case SDL_KEYDOWN:
		                /* Check the SDLKey values and move change the coords */
		                switch( event.key.keysym.sym ){

		                	case SDLK_RSHIFT:

		                		
		                		pressed_shift=true;
		                		while(pressed_shift){

		                			while( SDL_PollEvent( &event ) ){
									 	switch( event.type ){
		            
			            					case SDL_KEYDOWN:
					        					switch( event.key.keysym.sym ){
					        						case SDLK_r:
					                        		e.ref1--;
					                        		break;
					                        		case SDLK_a:
		                        						e.A--;
											e.update_C();
		                        						e.set_focus(e.C);
		                        						break;
		                    						case SDLK_b:
		                        						e.B--;
											e.update_C();
		                        						e.set_focus(e.C);
		                        						break;
		                    						case SDLK_c:
		                        						e.C--;
		                        						e.set_focus(e.C);
		                        						break;
					                        		default:break;
					        					}
			        						break;
			        						case SDL_KEYUP:
					        					switch( event.key.keysym.sym ){
					        						case SDLK_RSHIFT:
					                        		pressed_shift=false;
					                        		break;
					                        		default:break;
					        					}
			        						break;

			        							        					
		        						}	
		        					}
		        				}
		                	break;

		                	case SDLK_LSHIFT:

		                		
		                		pressed_shift=true;
		                		while(pressed_shift){

		                			while( SDL_PollEvent( &event ) ){
									 	switch( event.type ){
		            
			            					case SDL_KEYDOWN:
					        					switch( event.key.keysym.sym ){
					        						case SDLK_r:
					                        			e.ref1--;
					                        			break;
					                        		case SDLK_a:
		                        						e.A--;
											e.update_C();
		                        						e.set_focus(e.C);
		                        						break;
		                    						case SDLK_b:
		                        						e.B--;
											e.update_C();
		                        						e.set_focus(e.C);
		                        						break;
		                    						case SDLK_c:
		                        						e.C--;
		                        						e.set_focus(e.C);
		                        						break;
					                        		default:break;
					        					}
			        						break;
			        						case SDL_KEYUP:
					        					switch( event.key.keysym.sym ){
					        						case SDLK_LSHIFT:
					                        		pressed_shift=false;
					                        		break;
					                        		default:break;
					        					}
			        						break;

			        							        					
		        						}	
		        					}
		        				}
		                	break;

		                    case SDLK_r:
		                        e.ref1++;
		                        break;
		                   	case SDLK_a:
		                        e.A++;
					e.update_C();
		                        e.set_focus(e.C);
		                        break;
		                    case SDLK_b:
		                        e.B++;
					e.update_C();
		                        e.set_focus(e.C);
		                        break;
		                    case SDLK_c:
		                        e.C++;
		                        e.set_focus(e.C);
		                        break;
							case SDLK_ESCAPE:
		                    	std::cout<<"quit event";
		            			e.continue_drawing = false;
		                        break;
		                    default:
		                        break;
		                }
		                break;
		         
		            default:
		                break;
		        }

		    }
	}
}

int main(int argc, char const *argv[])
{
	ellipse e(500,400,300,3);
	std::thread threads[2];

	threads[0] = std::thread(ellipse_drawer,std::ref(e));
	threads[1] = std::thread(update_ellipse,std::ref(e));

	threads[0].join();
	threads[1].join();

	
	
	
	return 0;
}


