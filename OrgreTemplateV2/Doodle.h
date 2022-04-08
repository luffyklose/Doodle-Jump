#pragma once
#include <OgreTrays.h>

#include "GameObject.h"
#include "Platform.h"

class Doodle :
    public GameObject
{
private:
	SceneNode* cameraNode;
	Camera* camera;

	/// <summary>
	/// bool value for if doodle is colliding with platform
	/// </summary>
	bool m_bIsColliding;

	/// <summary>
	/// float value for max distance between camera & player
	/// </summary>
	float cameraPlayerDistanceLimit = 100.0f;

	/// <summary>
	/// float value for distance between camera & player on z-axis
	/// </summary>
	float distanceFromCameraToPlayerZAxis;

	/// <summary>
	/// player dies if value on z-axis is smaller than this value
	/// </summary>
	float playerDiedZValue;

	/// <summary>
	/// bool value for if the player is facing left
	/// </summary>
	bool isFacingLeft;

	/// <summary>
	/// int value for player live count
	/// </summary>
	int m_iLivesRemaining;

	/// <summary>
	/// int value for player score
	/// </summary>
	int m_iScore;

	/// <summary>
	/// bool value for if game is over
	/// </summary>
	bool m_bGameOver;

	/// <summary>
	/// bool value for if game is won
	/// </summary>
	bool m_bGameWon;

	/// <summary>
	/// float value for counting game time
	/// </summary>
	float m_fTotalGameTime;

	/// <summary>
	/// float value for player velocity on x-axis
	/// </summary>
	float m_velocityX;

	/// <summary>
	/// float value for player velocity on z-axis
	/// </summary>
	float m_velocityZ;

	/// <summary>
	/// label value for score UI reference 
	/// </summary>
	Label* m_scoreLabel;

	/// <summary>
	/// label value for player lives UI reference
	/// </summary>
	Label* m_liveLabel;

public:
	/// <summary>
	/// default constructor
	/// </summary>
	Doodle();

	/// <summary>
	/// constructor 
	/// </summary>
	/// <param name="node"></param>
	/// <param name="scnMgr"></param>
	Doodle(Ogre::SceneNode* node, Ogre::SceneManager* scnMgr);

	~Doodle();

	/// <summary>
	/// get player camera reference 
	/// </summary>
	/// <returns></returns>
	Camera* GetPlayerCamera();

	/// <summary>
	/// get player score
	/// </summary>
	/// <returns></returns>
	int GetScore();

	/// <summary>
	/// get remaining player live
	/// </summary>
	/// <returns></returns>
	int GetLivesRemaining();

	/// <summary>
	/// get if player is facing left
	/// </summary>
	/// <returns></returns>
	bool GetIsFacingLeft();

	/// <summary>
	/// get if player is game over
	/// </summary>
	/// <returns></returns>
	bool GetGameOver();

	/// <summary>
	/// get if player is won
	/// </summary>
	/// <returns></returns>
	bool GetGameWon();

	/// <summary>
	/// get player velocity on x-axis
	/// </summary>
	/// <returns></returns>
	float GetVelocityX();

	/// <summary>
	/// get player velocity on z-axis
	/// </summary>
	/// <returns></returns>
	float GetVelocityZ();

	/// <summary>
	/// get camera node
	/// </summary>
	/// <returns></returns>
	SceneNode* GetCameraNode();

	/// <summary>
	/// set player score
	/// </summary>
	/// <param name="score"></param>
	void SetScore(int score);

	/// <summary>
	/// set player lives
	/// </summary>
	/// <param name="livesRemaining"></param>
	void SetLivesRemaining(int livesRemaining);

	/// <summary>
	/// set player face direction
	/// </summary>
	/// <param name="dir"></param>
	void SetIsFacingLeft(bool dir);

	/// <summary>
	/// set game over
	/// </summary>
	/// <param name="m_bGameOver"></param>
	void SetGameOver(bool m_bGameOver);

	/// <summary>
	/// set game win
	/// </summary>
	/// <param name="m_bGameWon"></param>
	void SetGameWon(bool m_bGameWon);

	/// <summary>
	/// set player velocity on x-axis
	/// </summary>
	/// <param name="velocityX"></param>
	void SetVelocityX(float velocityX);

	/// <summary>
	/// set a player velocity on z-axis
	/// </summary>
	/// <param name="velocityZ"></param>
	void SetVelocityZ(float velocityZ);

	/// <summary>
	/// set live count UI reference
	/// </summary>
	/// <param name="label"></param>
	void SetLiveLabel(Label* label);

	/// <summary>
	/// set score count UI reference
	/// </summary>
	/// <param name="label"></param>
	void SetScoreLabel(Label* label);

	/// <summary>
	/// check if player is out of bounds, if the player is out of bounds then adjust position
	/// </summary>
	void CheckBounds();

	/// <summary>
	/// increment score and update UI
	/// </summary>
	void IncrementScore();

	/// <summary>
	/// decrement lives 
	/// </summary>
	void DecrementLivesRemaining();

	/// <summary>
	/// update doodle position based on velocity, check bounds & update camera position, if player dies, then reset player position & velocity
	/// </summary>
	/// <param name="evt"></param>
	/// <returns></returns>
	bool frameStarted(const Ogre::FrameEvent& evt);

	/// <summary>
	/// check player collision with platforms
	/// </summary>
	/// <param name="platform"></param>
	void CheckForCollisionWithPlatform(Platform* platform);

	/// <summary>
	/// create player camera
	/// </summary>
	/// <param name="scnMgr"></param>
	void CreatePlayerCamera(Ogre::SceneManager* scnMgr);

	/// <summary>
	/// update camera position
	/// </summary>
	/// <param name="evt"></param>
	void UpdateCameraPosition(const Ogre::FrameEvent& evt);

	/// <summary>
	/// update player direction
	/// </summary>
	/// <param name="input"></param>
	void UpdatePlayerDirection(char input);
	/// <summary>
	/// if player hits platform then set velocity 
	/// </summary>
	void PlayerHitPlatform();
};

