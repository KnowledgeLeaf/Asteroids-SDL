#ifndef __GRAPHICS_H 
#define __GRAPHICS_H 
#include <SDL.h> 
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream> 
#include <string>

namespace SDLFramework { 

	class GraphicsManager { 
	public: 
		static const short SCREEN_WIDTH = 1024;
		static const short SCREEN_HEIGHT = 896;
		const char* WINDOW_TITLE = "Galaga";

	private:
		static GraphicsManager* sInstance;
		static bool sInitialized;
		SDL_Window* mWindow;
		SDL_Renderer* mRenderer;

	public:
		static GraphicsManager* Instance();
		static void Release();
		static bool Initialized();
		void ClearBackBuffer();
		void Render();

		SDL_Texture* LoadTexture(std::string path);
		SDL_Texture* CreateTextTexture(TTF_Font* font, std::string text, SDL_Color color);


		void DrawTexture(SDL_Texture* tex, SDL_Rect* srcRect = nullptr, SDL_Rect* dstRect = nullptr, float angle = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);
		void DrawLine(float startX, float startY, float endX, float endY);

	private:
		GraphicsManager();
		~GraphicsManager();
		bool Init();

	}; 

} 

#endif

