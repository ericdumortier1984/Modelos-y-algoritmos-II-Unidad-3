#include "Game.h"
#include "Box2D.h"

using namespace sf;

Game::Game(int _width, int _height)
{

	_wnd = new RenderWindow(VideoMode(_width, _height), "EJERCICIO 5 - RAGDOLL");
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
		}

		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			for (int i = 0; i < 6; i++)
			{
				_bodies[i]->ApplyForce(b2Vec2(400.f, 0.f), _bodies[i]->GetWorldCenter(), true);
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			for (int i = 0; i < 6; i++)
			{
				_bodies[i]->ApplyForce(b2Vec2(-400.f, 0.f), _bodies[i]->GetWorldCenter(), true);
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			for (int i = 0; i < 6; i++)
			{
				_bodies[i]->ApplyForce(b2Vec2(0.f, -800.f), _bodies[i]->GetWorldCenter(), true);
			}
		}
	}
}

void Game::InitPhysics()
{

	_world = new b2World(b2Vec2(0.f, 9.8f));
	_render = new SFML(_wnd);
	_render->SetFlags(UINT_MAX);
	_world->SetDebugDraw(_render);

	b2Body* ground = Box2D::CreateRectangularStaticBody(_world, 100.f, 10.f);
	ground->SetTransform(b2Vec2(50.f, 100.f), 0.f);

	b2Body* rightWall = Box2D::CreateRectangularStaticBody(_world, 10.f, 100.f * 2);
	rightWall->SetTransform(b2Vec2(100.f, 100.f), 0.f);

	b2Body* leftWall = Box2D::CreateRectangularStaticBody(_world, 10.f, 100.f * 2);
	leftWall->SetTransform(b2Vec2(0.f, 100.f), 0.f);

	b2Body* roof = Box2D::CreateRectangularStaticBody(_world, 100.f, 10.f);
	roof->SetTransform(b2Vec2(50.f, 0.f), 0.f);

	_bodies[0] = Box2D::CreateCircularDynamicBody(_world, 2.f, 1.f, 0.f, 0.1f); // Cabeza
	_bodies[0]->SetTransform(b2Vec2(40.f, 49.f), 0.f);

	_bodies[1] = Box2D::CreateRectangularDynamicBody(_world, 4.f, 8.f, 1.f, 0.f, 0.1f); // Pecho
	_bodies[1]->SetTransform(b2Vec2(40.f, 55.f), 0.f);

	_bodies[2] = Box2D::CreateRectangularDynamicBody(_world, 2.f, 4.f, 1.f, 0.f, 0.1f); // Brazo izquierdo
	_bodies[2]->SetTransform(b2Vec2(37.f, 54.f), -50.f);

	_bodies[3] = Box2D::CreateRectangularDynamicBody(_world, 2.f, 4.f, 1.f, 0.f, 0.1f); // Brazo derecho
	_bodies[3]->SetTransform(b2Vec2(43.f, 54.f), 50.f);

	_bodies[4] = Box2D::CreateRectangularDynamicBody(_world, 2.f, 4.f, 1.f, 0.f, 0.1f); // Pierna izquierda
	_bodies[4]->SetTransform(b2Vec2(37.f, 60.f), -50.f);

	_bodies[5] = Box2D::CreateRectangularDynamicBody(_world, 2.f, 4.f, 1.f, 0.f, 0.1f); // Pierna derecha
	_bodies[5]->SetTransform(b2Vec2(43.f, 60.f), 50.f);

	Box2D::CreateDistanceJoint(_world, _bodies[0], b2Vec2(_bodies[0]->GetWorldCenter()), _bodies[1], b2Vec2(_bodies[1]->GetWorldCenter()), 0.f, 0.f, 0.1f);
	Box2D::CreateRevoluteJoint(_world, _bodies[1], b2Vec2(40.f, 55.f), _bodies[0], -b2_pi * 0.2f, b2_pi * 0.2f, 0.f, 0.f, false, true);
	Box2D::CreateDistanceJoint(_world, _bodies[1], b2Vec2(_bodies[1]->GetWorldCenter()), _bodies[2], b2Vec2(_bodies[2]->GetWorldCenter()), 0.f, 0.f, 0.1f);
	Box2D::CreateRevoluteJoint(_world, _bodies[1], b2Vec2(40.f, 52.f), _bodies[2], -b2_pi * 0.9f, b2_pi * 0.5f, 0.f, 0.f, false, true);
	Box2D::CreateDistanceJoint(_world, _bodies[1], b2Vec2(_bodies[1]->GetWorldCenter()), _bodies[3], b2Vec2(_bodies[3]->GetWorldCenter()), 0.f, 0.f, 0.1f);
	Box2D::CreateRevoluteJoint(_world, _bodies[1], b2Vec2(40.f, 52.f), _bodies[3], -b2_pi * 0.9f, b2_pi * 0.5f, 0.f, 0.f, false, true);
	Box2D::CreateDistanceJoint(_world, _bodies[1], b2Vec2(_bodies[1]->GetWorldCenter()), _bodies[4], b2Vec2(_bodies[4]->GetWorldCenter()), 0.f, 0.f, 0.1f);
	Box2D::CreateRevoluteJoint(_world, _bodies[1], b2Vec2(40.f, 58.f), _bodies[4], -b2_pi * 0.2f, b2_pi * 0.2f, 0.f, 0.f, false, true);
	Box2D::CreateDistanceJoint(_world, _bodies[1], b2Vec2(_bodies[1]->GetWorldCenter()), _bodies[5], b2Vec2(_bodies[5]->GetWorldCenter()), 0.f, 0.f, 0.1f);
	Box2D::CreateRevoluteJoint(_world, _bodies[1], b2Vec2(40.f, 58.f), _bodies[5], -b2_pi * 0.2f, b2_pi * 0.2f, 0.f, 0.f, false, true);
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
	groundShape.setFillColor(Color::Yellow);
	groundShape.setPosition(0.f, 95.f);
	_wnd->draw(groundShape);

	RectangleShape roofShape(Vector2f(100.f, 5.f));
	roofShape.setFillColor(Color::Yellow);
	roofShape.setPosition(0.f, 0.f);
	_wnd->draw(roofShape);

	CircleShape headShape(2.f);
	headShape.setFillColor(Color::Yellow);

	RectangleShape chestShape(Vector2f(4.f, 8.f));
	chestShape.setFillColor(Color::Red);

	RectangleShape leftArmShape(Vector2f(2.f, 4.f));
	leftArmShape.setFillColor(Color::Cyan);

	RectangleShape rightArmShape(Vector2f(2.f, 4.f));
	rightArmShape.setFillColor(Color::Cyan);

	RectangleShape leftLegShape(Vector2f(2.f, 4.f));
	leftLegShape.setFillColor(Color::Blue);

	RectangleShape rightLegShape(Vector2f(2.f, 4.f));
	rightLegShape.setFillColor(Color::Blue);

	for (int i = 0; i < 6; i++)
	{
		switch (i)
		{
		case 0: // Cabeza
			headShape.setPosition(_bodies[i]->GetPosition().x - 2.f, _bodies[i]->GetPosition().y - 2.f);
			_wnd->draw(headShape);
			break;
		case 1: // Pecho
			chestShape.setPosition(_bodies[i]->GetPosition().x - 2.f, _bodies[i]->GetPosition().y - 4.f);
			_wnd->draw(chestShape);
			break;
		case 2: // Brazo izquierdo
			leftArmShape.setPosition(_bodies[i]->GetPosition().x - 1.f, _bodies[i]->GetPosition().y - 2.f);
			_wnd->draw(leftArmShape);
			break;
		case 3: // Brazo derecho
			rightArmShape.setPosition(_bodies[i]->GetPosition().x - 1.f, _bodies[i]->GetPosition().y - 2.f);
			_wnd->draw(rightArmShape);
			break;
		case 4: // Pierna izquierda
			leftLegShape.setPosition(_bodies[i]->GetPosition().x - 1.f, _bodies[i]->GetPosition().y - 2.f);
			_wnd->draw(leftLegShape);
			break;
		case 5: // Pierna derecha
			rightLegShape.setPosition(_bodies[i]->GetPosition().x - 1.f, _bodies[i]->GetPosition().y - 2.f);
			_wnd->draw(rightLegShape);
			break;
		}
	}
}

Game::~Game(void)
{
}