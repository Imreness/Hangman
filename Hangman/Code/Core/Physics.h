#pragma once
#ifndef PHYSICS_CLASS
#define PHYSICS_CLASS

#include <bullet/btBulletDynamicsCommon.h>

class PhysicsEngine
{
private:
	btDynamicsWorld* m_world;

	btDefaultCollisionConfiguration* m_collisionconfig;
	btCollisionDispatcher* m_dispatcher;
	btBroadphaseInterface* m_overlappingPairCache;
	btSequentialImpulseConstraintSolver* m_solver;
public:

	~PhysicsEngine();

	PhysicsEngine();

	void Update(double step);

	btDynamicsWorld* getWorld() { return m_world; }

};


#endif