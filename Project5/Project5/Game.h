#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include "Box2D.h"
#include "SFML_Renderer.h"

using namespace sf;

class Game
{
private:

	int _width;
	int _height;
	RenderWindow* _wnd;
	Color _clearColor;

	float _frameTime;
	int _fps;

	b2World* _world;
	b2Body* _head;
	b2Body* _chest;
	b2Body* _rLeg;
	b2Body* _lLeg;
	b2Body* _rArm;
	b2Body* _lArm;
	SFML* _render;
public:

	Game(int _width, int _height);
	~Game(void);

	void InitPhysics();
	void UpdatePhysics();
	void Loop();
	void DoEvents();
	void DrawGame();
	void SetZoom();
};