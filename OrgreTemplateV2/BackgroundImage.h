#pragma once
#include "Doodle.h"
#include "GameObject.h"
class BackgroundImage :
    public GameObject
{
	/// <summary>
	/// doodle player ref
	/// </summary>
	Doodle* doodlePlayerRef;

	/// <summary>
	/// backgroundZExtent
	/// </summary>
	float backgroundZExtent;

	/// <summary>
	/// float value for distance between background extent & player
	/// </summary>
	float distanceToPlayer;

	/// <summary>
	/// back ground image starting position
	/// </summary>
	Vector3 m_vBackgroundStartingPosition;
public:
	/// <summary>
	/// default constructor
	/// </summary>
	BackgroundImage();

	/// <summary>
	/// constructor with params
	/// </summary>
	/// <param name="node"></param>
	/// <param name="scnMgr"></param>
	/// <param name="playerRef"></param>
	/// <param name="idNumber"></param>
	BackgroundImage(Ogre::SceneNode* node, Ogre::SceneManager* scnMgr, Doodle* playerRef, int idNumber);
	~BackgroundImage();

	/// <summary>
	/// get background z extent 
	/// </summary>
	/// <returns></returns>
	float GetBackgroundZExtent();

	/// <summary>
	/// get background starting position
	/// </summary>
	/// <returns></returns>
	Vector3 GetBackgroundStartingPosition();

	/// <summary>
	/// set background starting position
	/// </summary>
	/// <param name="startingPos"></param>
	void SetBackgroundStartingPosition(Vector3 startingPos);

private:
	/// <summary>
	/// check if the distance between background & player is greater than background extend,
	///	if so, then background image position
	/// </summary>
	/// <param name="evt"></param>
	/// <returns></returns>
	
	bool frameStarted(const Ogre::FrameEvent& evt);
};

