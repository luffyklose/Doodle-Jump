#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

Ogre::SceneNode* GameObject::GetAttachedSceneNode()
{
	return m_sceneNode;
}
Ogre::Entity* GameObject::GetEntity()
{
	return m_mesh;
}

Ogre::Vector3 GameObject::GetScale()
{
	return m_scale;
}

void GameObject::SetSceneNode(SceneNode* node)
{
	m_sceneNode = node;
}
void GameObject::SetEntity(Entity* en)
{
	m_mesh = en;
}

void GameObject::SetScale(Ogre::Vector3 scale)
{
	m_scale = scale;
}
