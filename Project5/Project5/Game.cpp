#include "Game.h"
#include "Box2D.h"

using namespace sf;

Game::Game(int _width, int _height)
{

	_wnd = new RenderWindow(VideoMode(_width, _height), "EJERCICIO 5 - RAGDOLL BREAKDANCE");
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
			_head->ApplyForce(b2Vec2(100.f, 0.f), b2Vec2(0.f,0.f), true);
			_chest->ApplyForce(b2Vec2(100.f, 0.f), b2Vec2(0.f, 0.f), true);
			_lArm->ApplyForce(b2Vec2(100.f, 0.f), b2Vec2(0.f, 0.f), true);
			_rArm->ApplyForce(b2Vec2(100.f, 0.f), b2Vec2(0.f, 0.f), true);
			_lLeg->ApplyForce(b2Vec2(100.f, 0.f), b2Vec2(0.f, 0.f), true);
			_rLeg->ApplyForce(b2Vec2(100.f, 0.f), b2Vec2(0.f, 0.f), true);
		}
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			_head->ApplyForce(b2Vec2(-100.f, 0.f), b2Vec2(0.f, 0.f), true);
			_chest->ApplyForce(b2Vec2(-100.f, 0.f), b2Vec2(0.f, 0.f), true);
			_lArm->ApplyForce(b2Vec2(-100.f, 0.f), b2Vec2(0.f, 0.f), true);
			_rArm->ApplyForce(b2Vec2(-100.f, 0.f), b2Vec2(0.f, 0.f), true);
			_lLeg->ApplyForce(b2Vec2(-100.f, 0.f), b2Vec2(0.f, 0.f), true);
			_rLeg->ApplyForce(b2Vec2(-100.f, 0.f), b2Vec2(0.f, 0.f), true);
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

    _head = Box2D::CreateCircularDynamicBody(_world, 2.f, 1.f, 0.3f, 0.5f);
	_head->SetTransform(b2Vec2(40.f, 49.f), 0.f);

	_chest = Box2D::CreateRectangularDynamicBody(_world, 4.f, 8.f, 1.f, 0.3f, 0.2f);
	_chest->SetTransform(b2Vec2(40.f, 55.f), 0.f);

	_lArm = Box2D::CreateRectangularDynamicBody(_world, 2.f, 4.f, 1.f, 0.3f, 0.2f);
	_lArm->SetTransform(b2Vec2(37.f, 54.f), 0.f);

	_rArm = Box2D::CreateRectangularDynamicBody(_world, 2.f, 4.f, 1.f, 0.3f, 0.2f);
	_rArm->SetTransform(b2Vec2(43.f, 54.f), 0.f);

	_lLeg = Box2D::CreateRectangularDynamicBody(_world, 2.f, 4.f, 1.f, 0.3f, 0.2f);
	_lLeg->SetTransform(b2Vec2(37.f, 60.f), 0.f);

	_rLeg = Box2D::CreateRectangularDynamicBody(_world, 2.f, 4.f, 1.f, 0.3f, 0.2f);
	_rLeg->SetTransform(b2Vec2(43.f, 60.f), 0.f);

	Box2D::CreateDistanceJoint(_world, _head, b2Vec2(_head->GetWorldCenter()), _chest, b2Vec2(_chest->GetWorldCenter()), 0.f, 0.f, 0.1f );
	Box2D::CreateRevoluteJoint(_world, _chest, b2Vec2(40.f, 55.f), _head, -b2_pi * 0.2f, b2_pi * 0.2f, 0.f, 0.f, false, true);
	Box2D::CreateDistanceJoint(_world, _chest, b2Vec2(_chest->GetWorldCenter()), _lArm, b2Vec2(_lArm->GetWorldCenter()), 0.f, 0.f, 0.1f);
	Box2D::CreateRevoluteJoint(_world, _chest, b2Vec2(40.f, 52.f), _lArm, -b2_pi * 0.9f, b2_pi * 0.5f, 0.f, 0.f, false, true);
	Box2D::CreateDistanceJoint(_world, _chest, b2Vec2(_chest->GetWorldCenter()), _rArm, b2Vec2(_rArm->GetWorldCenter()), 0.f, 0.f, 0.1f);
	Box2D::CreateRevoluteJoint(_world, _chest, b2Vec2(40.f, 52.f), _rArm, -b2_pi * 0.9f, b2_pi * 0.5f, 0.f, 0.f, false, true);
	Box2D::CreateDistanceJoint(_world, _chest, b2Vec2(_chest->GetWorldCenter()), _lLeg, b2Vec2(_lLeg->GetWorldCenter()), 0.f, 0.f, 0.1f);
	Box2D::CreateRevoluteJoint(_world, _chest, b2Vec2(40.f, 58.f), _lLeg, -b2_pi * 0.2f, b2_pi * 0.2f, 0.f, 0.f, false, true);
	Box2D::CreateDistanceJoint(_world, _chest, b2Vec2(_chest->GetWorldCenter()), _rLeg, b2Vec2(_rLeg->GetWorldCenter()), 0.f, 0.f, 0.1f);
	Box2D::CreateRevoluteJoint(_world, _chest, b2Vec2(40.f, 58.f), _rLeg, -b2_pi * 0.2f, b2_pi * 0.2f, 0.f, 0.f, false, true);
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

	/*CircleShape headShape(2.f);
	headShape.setFillColor(Color::Yellow);
	headShape.setPosition(_head->GetPosition().x - 2.f, _head->GetPosition().y - 2.f);
	_wnd->draw(headShape);

	RectangleShape chestShape(Vector2f(4.f, 8.f));
	chestShape.setFillColor(Color::Red);
	chestShape.setPosition(_chest->GetPosition().x - 2.f, _chest->GetPosition().y - 4.f);
	_wnd->draw(chestShape);

	RectangleShape leftArmShape(Vector2f(2.f, 4.f));
	leftArmShape.setFillColor(Color::Cyan);
	leftArmShape.setPosition(_lArm->GetPosition().x - 1.f, _lArm->GetPosition().y - 2.f);
	_wnd->draw(leftArmShape);

	RectangleShape rightArmShape(Vector2f(2.f, 4.f));
	rightArmShape.setFillColor(Color::Cyan);
	rightArmShape.setPosition(_rArm->GetPosition().x - 1.f, _rArm->GetPosition().y - 2.f);
	_wnd->draw(rightArmShape);

	RectangleShape leftLegShape(Vector2f(2.f, 4.f));
	leftLegShape.setFillColor(Color::Blue);
	leftLegShape.setPosition(_lLeg->GetPosition().x - 1.f, _lLeg->GetPosition().y - 2.f);
	_wnd->draw(leftLegShape);

	RectangleShape rightLegShape(Vector2f(2.f, 4.f));
	rightLegShape.setFillColor(Color::Blue);
	rightLegShape.setPosition(_rLeg->GetPosition().x - 1.f, _rLeg->GetPosition().y - 2.f);
	_wnd->draw(rightLegShape);*/
}

Game::~Game(void)
{
}