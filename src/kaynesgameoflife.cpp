#include "kaynesgameoflife.hpp"
#include <MINX/Graphics/Color.hpp>
#include <MINX/Graphics/GameWindow.hpp>
#include <MINX/Graphics/TextureBatch.hpp>
#include <MINX/Graphics/ShaderFactory.hpp>

using namespace KayneGameOfLife;
using namespace MINX;
using namespace MINX::Graphics;

bool* map;
TextureBatch* texBatch;
const int tileWidth = 32, tileHeight = 32;

GameOfLife::GameOfLife() : Game()
{
	//This is the constructor. Put stuff here that should happen when the Game is created.

	Game::SetVideoOptions(640, 480, false, "kaynes-game-of-life");
}

void GameOfLife::Initialize()
{
	//Put stuff here that should happen when the Game is initialized.
	
	GameWindow::sizeLocked = true;
	int width = GameWindow::GetWidth()/tileWidth;
	int height = GameWindow::GetHeight()/tileHeight;
	map = (bool*)malloc(width * height);
	for(int y = 0; y < height; ++y)
	{
		for(int x = 0; x < width; ++x)
		{
			map[y * width + x] = Math::random(0, 1, 2);
		}
	}

	Game::Initialize();

	texBatch = new TextureBatch(ShaderFactory::GetInstance()->GetShaderAtIndex(0));
}

void GameOfLife::LoadContent()
{
	//Put stuff here that loads content for your game.
	Game::LoadContent();
}

void GameOfLife::UnloadContent()
{
	//Put stuff here that unloads content from your game.

	free(map);

	Game::UnloadContent();
}

void GameOfLife::Update(GameTime * gameTime)
{
	//Put stuff here to update the logic in your game each tick.
	Game::Update(gameTime);
}

void GameOfLife::Draw(GameTime * gameTime)
{
	SetRenderTarget(NULL, Graphics::Color::CornflowerBlue);

	int width = GameWindow::GetWidth()/tileWidth;
	int height = GameWindow::GetHeight()/tileHeight;
	
	for(int y = 0; y < height; ++y)
	{
		for(int x = 0; x < width; ++x)
		{
			texBatch->DrawPrimitiveRectangle(Rectangle(x * tileWidth, y * tileHeight, tileWidth, tileHeight), map[y * width + x] ? Color::Black : Color::Salmon);
		}
	}

	texBatch->DrawLoadedTextures();

	//Put stuff here to draw your game each frame.
	Game::Draw(gameTime);
}