#include "kaynesgameoflife.hpp"
#include <MINX/Graphics/Color.hpp>
#include <MINX/Graphics/GameWindow.hpp>

using namespace KayneGameOfLife;

bool* map;

GameOfLife::GameOfLife() : Game()
{
	//This is the constructor. Put stuff here that should happen when the Game is created.

	Game::SetVideoOptions(640, 480, false, "kaynes-game-of-life");
}

void GameOfLife::Initialize()
{
	//Put stuff here that should happen when the Game is initialized.
	 
	Game::Initialize();
}

void GameOfLife::LoadContent()
{
	//Put stuff here that loads content for your game.
	Game::LoadContent();
}

void GameOfLife::UnloadContent()
{
	//Put stuff here that unloads content from your game.
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

	//Put stuff here to draw your game each frame.
	Game::Draw(gameTime);
}