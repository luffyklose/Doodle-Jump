#pragma once
#include "GameObject.h"
class Platform :
    public GameObject
{
private:
	/// <summary>
	/// int value for platform ID 
	/// </summary>
	int m_iPlatformIDNumber;

	/// <summary>
	/// bool value for if play earned point from jumping onto it 
	/// </summary>
	bool m_bPointEarned;

public:
	/// <summary>
	/// default constructor
	/// </summary>
	Platform();

	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="player"></param>
	/// <param name="scnMgr"></param>
	/// <param name="platformIDNumber"></param>
	Platform(Ogre::SceneNode* player, Ogre::SceneManager* scnMgr, int platformIDNumber);

	/// <summary>
	/// default destructor
	/// </summary>
	~Platform();

	/// <summary>
	/// update
	/// </summary>
	/// <param name="evt"></param>
	/// <returns></returns>
	bool frameStarted(const Ogre::FrameEvent& evt);

	/// <summary>
	/// set point earned
	/// </summary>
	/// <param name="pEarned"></param>
	void SetPointEarned(bool pEarned);

	/// <summary>
	/// get points earned
	/// </summary>
	/// <returns></returns>
	bool GetPointEarned();
};

