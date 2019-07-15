#include "Object.h"
void Object::Render(glm::mat4 &viewMatrix, glm::mat4 &projMatrix)
{
	if (m_shouldRender)
	{
		//Get the current transform from the physics engine
		btTransform transform;
		m_body->getMotionState()->getWorldTransform(transform);

		//Modify the transform of the visual object, so it matches up with the physics one
		m_model->TranslateMatrix(glm::vec3(transform.getOrigin().x(), transform.getOrigin().y(), transform.getOrigin().z()));

		m_model->RotateMatrix(glm::vec3(transform.getRotation().getAxis().x(),
			transform.getRotation().getAxis().y(),
			transform.getRotation().getAxis().z()),
			transform.getRotation().getAngle());

		m_model->ScaleMatrix(glm::vec3(m_colShape->getLocalScaling().x(),
			m_colShape->getLocalScaling().y(),
			m_colShape->getLocalScaling().z()));
		if (m_boolOverrideTexture)
			m_model->Render(viewMatrix, projMatrix, true, m_overrideTexture);
		m_model->Render(viewMatrix, projMatrix);
	}
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

Object::~Object()
{
	m_parentWorld->removeRigidBody(m_body);
	delete m_body;
	delete m_colShape;
}

Object::Object(std::string name, Model* model, btDynamicsWorld* physicsWorld, btTransform trans, bool textureOverdrive, Texture* tex)
	: m_model(model) , m_name(name)
{
	m_parentWorld = physicsWorld;

	btConvexHullShape* colShape = new btConvexHullShape(0, 0, sizeof(Vertex));

	for (int i = 0; i < m_model->GetVertices().size(); i++)
	{
		colShape->addPoint(btVector3(m_model->GetVertices()[i].pos.x,
									 m_model->GetVertices()[i].pos.y,
									 m_model->GetVertices()[i].pos.z));
	}

	//The margin is the extension of the hitbox. While setting it to 0 creates problems, we set it to 0.01.
	//While its still not perfect, its much better than the original 0.04
	colShape->setMargin(0.01);

	m_colShape = colShape;

	btScalar mass = 1.;

	btDefaultMotionState* defMotState = new btDefaultMotionState(trans);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, defMotState, m_colShape);
	m_body = new btRigidBody(rbInfo);

	//This way the body wont sleep. If it sleeps you cant move it.
	//Usually this is not a problem. If something is happening to the body, it wont sleep.
	//But since there is no gravity or anything, it'll go to sleep and then we cant animate things.
	m_body->setSleepingThresholds(0, 0);


	physicsWorld->addRigidBody(m_body);
	m_body      ->setUserPointer(this);

	m_overrideTexture = tex;
	m_boolOverrideTexture = textureOverdrive;
}