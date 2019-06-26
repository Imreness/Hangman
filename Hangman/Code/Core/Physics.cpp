#include "Physics.h"

PhysicsEngine::PhysicsEngine()
{
	//Setup
	m_collisionconfig = new btDefaultCollisionConfiguration();
	m_dispatcher = new btCollisionDispatcher(m_collisionconfig);
	m_overlappingPairCache = new btDbvtBroadphase();
	m_solver = new btSequentialImpulseConstraintSolver();

	m_world = new btDiscreteDynamicsWorld(m_dispatcher, m_overlappingPairCache, m_solver, m_collisionconfig);

	//We Wont need gravity since all the other bodies are going to be "static"
	m_world->setGravity(btVector3(0, 0, 0));
}

void PhysicsEngine::Update(double step)
{
	m_world->stepSimulation(step, 10);
}