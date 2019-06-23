#include "Object.h"
void Object::Render(glm::mat4 &viewMatrix, glm::mat4 &projMatrix)
{
	btTransform transform;
	m_body->getMotionState()->getWorldTransform(transform);

	m_model->TranslateMatrix(glm::vec3(transform.getOrigin().x(), transform.getOrigin().y(), transform.getOrigin().z()));
	m_model->RotateMatrix(glm::vec3(transform.getRotation().getAxis().x(),
		transform.getRotation().getAxis().y(),
		transform.getRotation().getAxis().z()),
		transform.getRotation().getAngle());
	m_model->ScaleMatrix(glm::vec3(m_colShape->getLocalScaling().x(),
		m_colShape->getLocalScaling().y(),
		m_colShape->getLocalScaling().z()));

	m_model->Render(viewMatrix, projMatrix);
}

void Object::Translate(glm::vec3 amount, bool resetLastpos)
{
	btTransform btAmount;
	m_body->getMotionState()->getWorldTransform(btAmount);
	if (resetLastpos)
	{
		btAmount.setOrigin(btVector3(amount.x, amount.y, amount.z));
	}
	else
	{
		btAmount.setOrigin(btAmount.getOrigin() + btVector3(amount.x, amount.y, amount.z));
	}
	m_body->setCenterOfMassTransform(btAmount);
}

void Object::Rotate(float x , float y , float z, bool resetLastrot)
{
	btTransform trans;
	m_body->getMotionState()->getWorldTransform(trans);
	btQuaternion quaternion;
	quaternion = quaternion.getIdentity();

	quaternion.setX(x);
	quaternion.setY(y);
	quaternion.setZ(z);

	if (resetLastrot)
	{
		trans.setRotation(quaternion);
	}
	else
	{
		trans.setRotation(trans.getRotation() * quaternion);
	}

	m_body->setCenterOfMassTransform(trans);
}

void Object::Scale(glm::vec3 amount , bool resetLastscale)
{
	if (resetLastscale)
		m_colShape->setLocalScaling(btVector3(amount.x, amount.y, amount.z));
	else
		m_colShape->setLocalScaling(btVector3(amount.x, amount.y, amount.z) + m_colShape->getLocalScaling());
}

Object::Object(std::string name ,Model* model , btDynamicsWorld* physicsWorld)
	: m_model(model) , m_name(name)
{
	std::cout << m_name << "\n";
	//Physics set up
	//TODO - Assign the shape in the ConvexHullShape constructor
	btConvexHullShape* colShape = new btConvexHullShape(0, 0, sizeof(Vertex));

	float CollisionMargin = 0.04f;

	for (int i = 0; i < m_model->GetVertices().size(); i++)
	{
		colShape->addPoint(btVector3(m_model->GetVertices()[i].pos.x,
									 m_model->GetVertices()[i].pos.y,
									 m_model->GetVertices()[i].pos.z));
	}

	//const btScalar* firstPoint = &model->GetVertices()[0].pos.x;

	//btConvexHullShape* colShape = new btConvexHullShape(firstPoint, (int)(model->GetVertices().size()) * 3, (int)sizeof(Vertex));

	//btBoxShape* colShape = new btBoxShape(btVector3(1, 1, 1));

	colShape->setMargin(0.01);

	m_colShape = colShape;

	btTransform transform;
	transform.setIdentity();

	btScalar mass = 1.;

	transform.setOrigin(btVector3(0., 0., 0.));


	btDefaultMotionState* defMotState = new btDefaultMotionState(transform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, defMotState, m_colShape);

	m_body = new btRigidBody(rbInfo);

	m_body->setSleepingThresholds(0, 0);

	physicsWorld->addRigidBody(m_body);

	m_body->setUserPointer(this);
}