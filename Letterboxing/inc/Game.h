#pragma once
#include <raylib.h>

class Game
{
public:
	Game();
	~Game();

	void run();
	void update();
	void draw();

	void updateRenderRec();
	void updateMouse();
private:
	RenderTexture2D m_renderTexture;
	Rectangle m_renderRec;

	float m_scale;
	float m_texWidth;
	float m_texHeight;

	float m_screenWidth;
	float m_screenHeight;
};