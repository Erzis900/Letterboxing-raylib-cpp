#include "Game.h"
#include <raylib.h>
#include <algorithm>

Game::Game()
	:m_scale(1.f)
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(1280, 720, "Letterboxing example in Raylib [C++]");
	SetTargetFPS(60);

	m_renderTexture = LoadRenderTexture(640, 360);
	m_texWidth = float(m_renderTexture.texture.width);
	m_texHeight = float(m_renderTexture.texture.height);

	SetTextureFilter(m_renderTexture.texture, TEXTURE_FILTER_POINT);
}

Game::~Game()
{
	UnloadRenderTexture(m_renderTexture);
	CloseWindow();
}

void Game::updateRenderRec()
{
	m_screenWidth = float(GetScreenWidth());
	m_screenHeight = float(GetScreenHeight());

	m_scale = std::min(m_screenWidth / m_texWidth, m_screenHeight / m_texHeight);
	m_renderRec.width = m_texWidth * m_scale;
	m_renderRec.height = m_texHeight * m_scale;
	m_renderRec.x = (m_screenWidth - m_renderRec.width) / 2.f;
	m_renderRec.y = (m_screenHeight - m_renderRec.height) / 2.f;
}

void Game::updateMouse()
{
	int offsetX = int(-(m_screenWidth - (m_texWidth * m_scale)) / 2.f);
	int offsetY = int(-(m_screenHeight - (m_texHeight * m_scale)) / 2.f);

	SetMouseOffset(offsetX, offsetY);
	SetMouseScale(1 / m_scale, 1 / m_scale);
}

void Game::update()
{
	updateRenderRec();
	updateMouse();
}

void Game::draw()
{
	BeginTextureMode(m_renderTexture);

	ClearBackground(GRAY);
	DrawRectangle(0, 0, 32, 32, PURPLE);	

	EndTextureMode();

	BeginDrawing();
	ClearBackground(BLACK);

	DrawTexturePro(m_renderTexture.texture, { 0.f, 0.f, m_texWidth, -m_texHeight }, m_renderRec, { 0.f, 0.f }, 0.f, WHITE);
	EndDrawing();
}

void Game::run()
{
	while (!WindowShouldClose())
	{
		update();
		draw();
	}
}