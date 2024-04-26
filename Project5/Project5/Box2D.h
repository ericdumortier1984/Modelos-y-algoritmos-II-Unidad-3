#pragma once
#include <box2d/box2d.h>

class Box2D
{
public:

	static b2Body* CreateStaticBody(b2World* _world)
	{

		b2Body* body;
		b2BodyDef bodyDef;
		bodyDef.type = b2_staticBody;
		bodyDef.position.Set(0.f, 0.f);
		body = _world->CreateBody(&bodyDef);

		return body;
	}

	static b2Body* CreateDynamicBody(b2World* _world)
	{

		b2Body* body;

		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(0.0f, 0.0f);
		body = _world->CreateBody(&bodyDef);
		return body;
	}

	static b2FixtureDef CreateRectangularFixtureDef(float _sizeX, float _sizeY, float _density, float _friction, float _restitution)
	{

		b2PolygonShape* box = new b2PolygonShape();

		box->SetAsBox(_sizeX / 2.0f, _sizeY / 2.f, b2Vec2(0.f, 0.f), 0.f);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = box;
		fixtureDef.density = _density;
		fixtureDef.friction = _friction;
		fixtureDef.restitution = _restitution;

		return fixtureDef;
	}

	static b2Body* CreateRectangularStaticBody(b2World* _world, float _sizeX, float _sizeY)
	{
		b2Body* body = CreateStaticBody(_world);
		b2FixtureDef box = CreateRectangularFixtureDef(_sizeX, _sizeY, 0.f, 0.f, 0.f);
		body->CreateFixture(&box);

		return body;
	}

	static b2FixtureDef CreateCircularFixtureDef(float _radius, float _density, float _friction, float _restitution)
	{
		b2CircleShape* circle = new b2CircleShape();
		circle->m_p = b2Vec2(0.0f, 0.0f);
		circle->m_radius = _radius;

		b2FixtureDef fixtureDef;
		fixtureDef.shape = circle;
		fixtureDef.density = _density;
		fixtureDef.friction = _friction;
		fixtureDef.restitution = _restitution;

		return fixtureDef;
	}

	static b2Body* CreateCircularDynamicBody(b2World* _world, float _radius, float _density, float _friction, float _restitution)
	{
		b2Body* body = CreateDynamicBody(_world);
		b2FixtureDef cir = CreateCircularFixtureDef(_radius, _density, _friction, _restitution);
		body->CreateFixture(&cir);
		return body;
	}

	static b2Body* CreateRectangularDynamicBody(b2World* _world, float _sizeX, float _sizeY, float _density, float _friction, float _restitution)
	{
		b2Body* body = CreateDynamicBody(_world);
		b2FixtureDef box = CreateRectangularFixtureDef(_sizeX, _sizeY, _density, _friction, _restitution);
		body->CreateFixture(&box);

		return body;
	}

	static b2DistanceJoint* CreateDistanceJoint(b2World* _world, b2Body* _first, b2Vec2 _anchorFirst, b2Body* _second, b2Vec2 _anchorSecond,
		float _distance, float _frec, float _dampRatio)
	{
		b2DistanceJointDef jointDef;
		jointDef.Initialize(_first, _second, _anchorFirst, _anchorSecond);
		jointDef.collideConnected = true;
		jointDef.length = _distance;
		b2LinearStiffness(jointDef.stiffness, jointDef.damping, _frec, _dampRatio, jointDef.bodyA, jointDef.bodyB);
		b2DistanceJoint* distJoint = (b2DistanceJoint*)_world->CreateJoint(&jointDef);
		return distJoint;
	}

	static b2RevoluteJoint* CreateRevoluteJoint(b2World* _world, b2Body* _base, b2Vec2 _anchorBase, b2Body* _second,
		float _angMin, float _angMax, float _motorSpeed, float _maxTorque,
		bool _enableMotor, bool _enableLimits)
	{
		b2RevoluteJointDef jointDef;
		jointDef.Initialize(_base, _second, _anchorBase);
		jointDef.lowerAngle = _angMin;
		jointDef.upperAngle = _angMax;
		jointDef.enableLimit = _enableLimits;
		jointDef.maxMotorTorque = _maxTorque;
		jointDef.motorSpeed = _motorSpeed;
		jointDef.enableMotor = _enableMotor;
		jointDef.collideConnected = true;

		b2RevoluteJoint* revJoint = (b2RevoluteJoint*)_world->CreateJoint(&jointDef);
		return revJoint;
	}

};