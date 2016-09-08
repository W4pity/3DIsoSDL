
#include <stdlib.h>
#include <unistd.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>





int main ( int argc, char** argv )
{
  // initialize SDL video
  if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
  {
    printf( "Unable to init SDL: %s\n", SDL_GetError() );
    return 1;
  }
  SDL_EnableKeyRepeat(10,10);
  // make sure SDL cleans up before exit
  atexit(SDL_Quit);

  // create a new window
  SDL_Surface* screen = SDL_SetVideoMode(1200, 600, 16,
      SDL_HWSURFACE|SDL_DOUBLEBUF);
  if (!screen)
  {
    printf("Unable to set 640x480 video: %s\n", SDL_GetError());
    return 1;
  }

  // load an image
  //SDL_Surface* bmp = SDL_LoadBMP("cp.bmp");
  SDL_Surface *bloc = NULL;
  SDL_Surface *grass = IMG_Load("images/grass.png");
  SDL_Surface *water = IMG_Load("images/water.png");    
  SDL_Surface *carac= IMG_Load("images/carac.png");    
  /*if (bloc)
    {
    printf("Unable to load bitmap: %s\n", SDL_GetError());
    return 1;
    }*/

  SDL_Rect pCaracBloc;
  pCaracBloc.x = 0;
  pCaracBloc.y = 0;
  pCaracBloc.w = 30;
  pCaracBloc.h = 41;
  // centre the bitmap on screen
  SDL_Rect pCarac;
  pCarac.x = 0;
  pCarac.y = 0;
  pCarac.w = 0;
  pCarac.h = 0;
  SDL_Rect dstrect;
  dstrect.x = (screen->w - grass->w) / 2;

  dstrect.y = (screen->h - grass->h) / 2;

  // program main loop
  int finish = 0;

  // 0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9  0  1  2  
  int map[21][23] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},//10
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},//20
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  int positionH = 0;
  int positionV = 0;
  int countSprite = 0;

  while (!finish)
  {
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
	// exit if the window is closed
	case SDL_QUIT:
	  finish = 1;
	  break;

	  // check for keypresses
	case SDL_KEYUP:
	  {
	    positionH = 0;
	    positionV =1;
	  }
	case SDL_KEYDOWN:
	  {
	    if(countSprite>5)
	    {
	    if(positionH>2)
		positionH = 0;//pb sprite walking

	      positionH+=1;
	      pCaracBloc.y = positionV*41;
	      pCaracBloc.x = positionH*31;
	      countSprite = 0;
	    }
	    int speed = 2;
	    // exit if ESCAPE is pressed
	    if (event.key.keysym.sym == SDLK_ESCAPE)
	      finish = 1;
	    if (event.key.keysym.sym == SDLK_RIGHT)
	    {
	      pCarac.x+=(1*speed);
	      pCarac.y+=(1*speed);
	    }
	    if (event.key.keysym.sym == SDLK_LEFT)
	    {
	      pCarac.x-=(1*speed);
	      pCarac.y-=(1*speed);
	    }
	    if (event.key.keysym.sym == SDLK_UP)
	    {
	      pCarac.y-=(1*speed);
	      pCarac.x+=(1*speed);
	    }
	    if (event.key.keysym.sym == SDLK_DOWN)
	    {
	      pCarac.y+=(1*speed);
	      pCarac.x-=(1*speed);
	    }
	    break;
	  }
      } // end switch
      countSprite+=1;
    } // end of message processing


    // clear screen
    SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

    // draw bitmap
    SDL_BlitSurface(bloc, 0, screen, &dstrect);

    int sizeBloc = 64;
    for(int i = 0; i<21; i++)
    {
      for(int j = 0; j<23; j++)
      {
	if(map[i][j] != -1)
	{


	  int x = (j-i)*sizeBloc/2+500;
	  int y = (j+i)*sizeBloc/4;
	  int numberBloc = 0;
	  numberBloc = map[i][j];


	  dstrect.x = x;
	  dstrect.y = y;
	  if(numberBloc == 0)
	  {
	    bloc = water;
	    dstrect.y += 20;
	    SDL_BlitSurface(bloc ,0 , screen, &dstrect);
	  }
	  else if(numberBloc == 1)
	  {
	    bloc = grass;
	    SDL_BlitSurface(bloc, 0, screen, &dstrect);
	  }
	  else if(numberBloc == 2)
	  {
	    bloc = grass;
	    SDL_BlitSurface(bloc, 0, screen, &dstrect);
	  }
	  else if(numberBloc == 3)
	  {
	    bloc = grass;
	    SDL_BlitSurface(bloc, 0, screen, &dstrect);
	  }

	  //	  sleep(0.2);
	  //	  SDL_Flip(screen);
	}
      }
    }
    bloc = carac;
    SDL_BlitSurface(bloc, &pCaracBloc, screen, &pCarac);
    int next = 0;
    //   scanf("%d",&next);
    if(next)
      finish=1; 
    // update the screen
    SDL_Flip(screen);
  } // end main loop

  // free loaded bitmap
  SDL_FreeSurface(bloc);


  // all is well
  printf("Exited cleanly\n");
  return 0;
}
