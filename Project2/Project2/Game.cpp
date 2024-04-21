#include "Game.h"
#include "Box2D.h"

using namespace sf;

Game::Game(int _width, int _height)
{

	_wnd = new RenderWindow(VideoMode(_width, _height), "EJERCICIO 2");
	_fps = 60;
	_wnd->setFramerateLimit(_fps);
	_frameTime = 1.f / _fps;
	InitPhysics();
	SetZoom();
}

void Game::Loop()
{

	while (_wnd->isOpen())
	{

		_wnd->clear(_clearColor);
		DoEvents();
		UpdatePhysics();
		DrawGame();
		_wnd->display();
	}
}

void Game::DoEvents()
{
	Event evt;
	while (_wnd->pollEvent(evt))
	{
		switch (evt.type)
		{
		case Event::Closed:
			_wnd->close();
			break;

		case Event::MouseButtonPressed:
			if (evt.mouseButton.button == Mouse::Left)
			{
				b2Vec2 mouseWorldPos = b2Vec2(evt.mouseButton.x, evt.mouseButton.y);
				_mouseJoint = Box2D::CreateMouseJoint(_world, _ballOne, 1000.f);
				_mouseJoint->SetTarget(mouseWorldPos);
			}
			break;

		case Event::MouseButtonReleased:
			if (evt.mouseButton.button == Mouse::Left)
			{
				_world->DestroyJoint(_mouseJoint);
				_mouseJoint = nullptr;
			}
			break;

		case Event::MouseMoved:
			if (_mouseJoint)
			{
				b2Vec2 mouseWorldPos = b2Vec2(evt.mouseMove.x, evt.mouseMove.y);
				_mouseJoint->SetTarget(mouseWorldPos);
			}
			break;
		}
	}
}

void Game::InitPhysics()
{

	_world = new b2World(b2Vec2(0.f, 9.8f));
	_render = new SFML(_wnd);
	_render->SetFlags(UINT_MAX);
	_world->SetDebugDraw(_render);

	b2Body* groundShape = Box2D::CreateRectangularStaticBody(_world, 100.f, 10.f);
	groundShape->SetTransform(b2Vec2(50.f, 100.f), 0.f);

	b2Body* rightWallShape = Box2D::CreateRectangularStaticBody(_world, 10.f, 100.f * 2);
	rightWallShape->SetTransform(b2Vec2(100.f, 100.f), 0.f);

	b2Body* leftWallShape = Box2D::CreateRectangularStaticBody(_world, 10.f, 100.f * 2);
	leftWallShape->SetTransform(b2Vec2(0.f, 100.f), 0.f);

	_ballOne = Box2D::CreateCircularDynamicBody(_world, 5.f, 1.f, 0.3f, 0.6f);
	_ballOne->SetTransform(b2Vec2(40.f, 50.f), 0.f);

	_ballTwo = Box2D::CreateCircularDynamicBody(_world, 3.f, 0.5f, 0.6f, 0.3f);
	_ballTwo->SetTransform(b2Vec2(60.f, 30.f), 0.f);

	Box2D::CreateDistanceJoint(_world, _ballOne, _ballOne->GetPosition(), _ballTwo, _ballTwo->GetPosition(), 0.f, 1.f, 0.f);
}

void Game::UpdatePhysics()
{

	_world->Step(_frameTime, 8, 8);
	_world->ClearForces();
	_world->DebugDraw();
}

void Game::SetZoom()
{

	View camara;
	camara.setSize(100.f, 100.f);
	camara.setCenter(50.f, 50.f);
	_wnd->setView(camara);
}

void Game::DrawGame()
{

	RectangleShape rightWallShape(Vector2f(5.f, 100.f));
	rightWallShape.setFillColor(Color::Yellow);
	rightWallShape.setPosition(95.f, 0.f);
	_wnd->draw(rightWallShape);

	RectangleShape leftWallShape(Vector2f(5.f, 100.f));
	leftWallShape.setFillColor(Color::Yellow);
	leftWallShape.setPosition(0.f, 0.f);
	_wnd->draw(leftWallShape);

	RectangleShape groundShape(Vector2f(100.f, 5.f));
	groundShape.setFillColor(Color::Green);
	groundShape.setPosition(0.f, 95.f);
	_wnd->draw(groundShape);

	CircleShape ballOne(5.f);
	ballOne.setFillColor(Color::Red);
	ballOne.setPosition(_ballOne->GetPosition().x - 5.f, _ballOne->GetPosition().y - 5.f);
	_wnd->draw(ballOne);
}

Game::~Game(void)
{
}