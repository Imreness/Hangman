#include "Object.h"
void Object::Render(glm::mat4 &viewMatrix, glm::mat4 &projMatrix)
{
	btTransform transform;
	m_body->getMotionState()->getWorldTransform(transform);

	m_model->TranslateMatrix(glm::vec3(transform.getOrigin().x(), transform.getOrigin().y(), transform.getOrigin().z()));
	m_model->Render(viewMatrix, projMatrix);
}

void Object::Translate(glm::vec3 amount)
{
	//TODO
	//make it so that it adds to the current position instead of overwriting it
	btTransform btAmount;
	btAmount.setOrigin(btVector3(amount.x, amount.y, amount.z));
	m_body->setWorldTransform(btAmount);
	m_body->getMotionState()->setWorldTransform(btAmount);
}

Object::Object(std::string name ,Model* model , btDynamicsWorld* physicsWorld)
	: m_model(model) , m_name(name)
{
	std::cout << m_name << "\n";
	//Physics set up
	//TODO - Assign the shape in the ConvexHullShape constructor
	//btConvexHullShape* colShape = new btConvexHullShape(0, 0, sizeof(Vertex));

	//float CollisionMargin = 0.04f;

	//for (int i = 0; i < m_model->GetVertices().size(); i++)
	//{
	//	colShape->addPoint(btVector3(m_model->GetVertices()[i].pos.x,
	//								 m_model->GetVertices()[i].pos.y,
	//								 m_model->GetVertices()[i].pos.z));
	//}

	//const btScalar* firstPoint = &model->GetVertices()[0].pos.x;

	//btConvexHullShape* colShape = new btConvexHullShape(firstPoint, (int)(model->GetVertices().size()) * 3, (int)sizeof(Vertex));

	btBoxShape* colShape = new btBoxShape(btVector3(1, 1, 1));

	m_colShape = colShape;

	btTransform transform;
	transform.setIdentity();

	btScalar mass = 0.;

	transform.setOrigin(btVector3(0., 0., 0.));


	btDefaultMotionState* defMotState = new btDefaultMotionState(transform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, defMotState, m_colShape);

	m_body = new btRigidBody(rbInfo);

	physicsWorld->addRigidBody(m_body);

	m_body->setUserPointer(this);
}