#include "kanyesgameoflife.hpp"
#include <MINX/Graphics/Color.hpp>
#include <MINX/Graphics/GameWindow.hpp>
#include <MINX/Graphics/TextureBatch.hpp>
#include <MINX/Graphics/ShaderFactory.hpp>

using namespace KanyeGameOfLife;
using namespace MINX;
using namespace MINX::Graphics;

bool* map;
TextureBatch* texBatch;
Texture2D* kanye;
const int tileWidth = 16, tileHeight = 16;

double elapsedTime = 0.0;
double timeLimit = 2.0;


bool* updateCells(bool* board, int width, int height);
int calculateLiveNeighbors(bool* board, int x, int y, int width, int height);

GameOfLife::GameOfLife() : Game()
{
	//This is the constructor. Put stuff here that should happen when the Game is created.
	srand(time(NULL));
	Game::SetVideoOptions(640, 480, true, "kanye\'s-game-of-life");
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
	kanye = new Texture2D("../content/kanye.png");
}

void GameOfLife::UnloadContent()
{
	//Put stuff here that unloads content from your game.

	free(map);

	Game::UnloadContent();
}

void GameOfLife::Update(GameTime * gameTime)
{
	elapsedTime += gameTime->GetDeltaTimeSeconds();

	if(elapsedTime >= timeLimit)
	{
		elapsedTime = 0.0;

		map = updateCells(map, GameWindow::GetWidth()/tileWidth, GameWindow::GetHeight()/tileHeight);
	}
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
			/*
			texBatch->DrawPrimitiveRectangle(
				Rectangle(
					x * tileWidth,
					y * tileHeight,
					tileWidth,
					tileHeight),
				map[y * width + x] ? Color::Black : Color::Salmon);
			//*/
			texBatch->Draw(kanye, x * tileWidth, y * tileHeight, tileWidth/64.0, tileHeight/64.0, 0, map[y * width + x] ? Color::White : Color::TransparentBlack );
		}
	}

	texBatch->DrawLoadedTextures();

	//Put stuff here to draw your game each frame.
	Game::Draw(gameTime);
}

bool* updateCells(bool* board, int width, int height)
{
	bool* newBoard = (bool*)malloc(width * height);
	for(int y = 0; y < height; ++y)
	{
		for(int x = 0; x < width; ++x)
		{
			int liveNeighbors = calculateLiveNeighbors(board, x, y, width, height);
			if(board[y * width + x] && (liveNeighbors < 2) || liveNeighbors > 3)
			{
				newBoard[y * width + x] = false;
			}
			else if(board[y * width + x] && liveNeighbors < 4)
			{
				newBoard[y * width + x] = true;
			}
			else if(liveNeighbors == 3)
			{
				newBoard[y * width + x] = true;
			}
			else
			{
				newBoard[y * width + x] = false;
			}
		}
	}
	free(board);
	return newBoard;
}

int calculateLiveNeighbors(bool* board, int x, int y, int width, int height)
{
	int liveCount = 0;
	if(y > 0)
	{
		if(board[(y - 1) * width + x]) ++liveCount;
	}
	if(y > 0 && x > 0)
	{
		if(board[(y - 1) * width + (x - 1)]) ++liveCount;
	}
	if(x > 0)
	{
		if(board[y * width + (x - 1)]) ++liveCount;
	}
	if(x > 0 && y < height)
	{
		if(board[(y + 1) * width + (x - 1)]) ++liveCount;
	}
	if(y < height)
	{
		if(board[(y + 1) * width + x]) ++liveCount;
	}
	if(y < height && x < width)
	{
		if(board[(y + 1) * width + (x + 1)]) ++liveCount;
	}
	if(x < width)
	{
		if(board[y * width + (x + 1)]) ++liveCount;
	}
	if(y > 0 && x < width)
	{
		if(board[(y - 1) * width + (x + 1)]) ++liveCount;
	}
	return liveCount;
}
