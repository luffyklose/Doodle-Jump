#pragma once
#include "Ogre.h"
#include "OgreInput.h"
#include <iostream>

using namespace Ogre;
using namespace OgreBites;

class GameObject : public Ogre::FrameListener
{
private:
	/// <summary>
	/// SceneNode
	/// </summary>
	Ogre::SceneNode* m_sceneNode;

	/// <summary>
	/// Entity for mesh variable
	/// </summary>
	Ogre::Entity* m_mesh;

	/// <summary>
	/// vector3 for scale
	/// </summary>
	Ogre::Vector3 m_scale;

public:
	/// <summary>
	/// default constructor
	/// </summary>
	GameObject();

	/// <summary>
	/// default destructor
	/// </summary>
	~GameObject();

	//Getter

	/// <summary>
	/// get attached scene node
	/// </summary>
	/// <returns></returns>
	Ogre::SceneNode* GetAttachedSceneNode();

	/// <summary>
	/// get entity
	/// </summary>
	/// <returns></returns>
	Ogre::Entity* GetEntity();

	/// <summary>
	/// get scale
	/// </summary>
	/// <returns></returns>
	Ogre::Vector3 GetScale();

	//Setters

	/// <summary>
	/// set scene node 
	/// </summary>
	/// <param name="node"></param>
	void SetSceneNode(SceneNode* node);

	/// <summary>
	/// set entity
	/// </summary>
	/// <param name="en"></param>
	void SetEntity(Entity* en);

	/// <summary>
	/// set scale
	/// </summary>
	/// <param name="scale"></param>
	void SetScale(Ogre::Vector3 scale);

	/// <summary>
	/// update
	/// </summary>
	/// <param name="evt"></param>
	/// <returns></returns>
	virtual bool frameStarted(const Ogre::FrameEvent& evt) = 0;
};
