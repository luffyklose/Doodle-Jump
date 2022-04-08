#pragma once
#include "BackgroundImage.h"
#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include "OgreTrays.h"
#include "Doodle.h"
#include "Platform.h"

using namespace Ogre;
using namespace OgreBites;

/// <summary>
/// Game Class, implement most of game features
/// </summary>
class Game
	: public ApplicationContext
	, public InputListener
{
private:	
	SceneManager* scnMgr;
	Root* root;
	RTShader::ShaderGenerator* shadergen;
	OgreBites::TrayManager* mTrayMgr;

	/// <summary>
	/// Label shows player's score
	/// </summary>
	Label* m_scoreLabel;
	/// <summary>
	/// Label shows player's live
	/// </summary>
	Label* m_liveLabel;
	/// <summary>
	/// Label shows game time
	/// </summary>
	Label* m_timeLabel;
	/// <summary>
	/// Label show game's FPS
	/// </summary>
	Label* m_frameLabel;
	/// <summary>
	/// Label gold player the game is over
	/// </summary>
	Label* m_gameOverLabel;

	/// <summary>
	/// A reference to the ball
	/// </summary>
	Doodle* m_doodle;
	/// <summary>
	/// A reference to the bat
	/// </summary>
	std::vector<Platform*> m_platformVec;
	BackgroundImage* m_backgroundImage[2];

	/// <summary>
	/// The lives player has, the initial value is 5
	/// </summary>
	int m_lives = 5;
	/// <summary>
	/// The score player has, the initial value is 0
	/// </summary>
	int m_score = 0;
	/// <summary>
	/// The width of window, is used to calculate if the ball is collided with border
	/// </summary>
	int m_windowWidth;
	/// <summary>
	/// The height of window, is used to calculate if the ball is collided with border
	/// </summary>
	int m_windowHeight;
	/// <summary>
	/// Used to set ScoreLabel
	/// </summary>
	std::string m_scoreText;
	/// <summary>
	/// Used to set LiveLabel
	/// </summary>
	std::string m_liveText;
	/// <summary>
	/// Used to set FPS
	/// </summary>
	std::string m_FPSText;
	/// <summary>
	/// Used to set Time/Update
	/// </summary>
	std::string m_TimeText;

	float m_randomPositionX = 0.0f;
	int m_platformNumber = 15;
public:
	/// <summary>
	/// default constructor
	/// </summary>
	Game();
	/// <summary>
	/// default destructor
	/// </summary>
	virtual ~Game() {}
	
	/// <summary>
	/// Called when the game starts
	/// </summary>
	void setup();
	/// <summary>
	/// Detect if there's any input. In this assignment detect move input.
	/// </summary>
	/// <param name="evt">reference to keyboard event</param>
	/// <returns>always return true</returns>
	bool keyPressed(const KeyboardEvent& evt);
	bool keyReleased(const KeyboardEvent& evt);
	/// <summary>
	/// Create scene
	/// </summary>
	void createScene();
	/// <summary>
	/// Set up camera
	/// </summary>
	void createCamera();
	/// <summary>
	/// Called every frame
	/// </summary>
	/// <param name="evt">reference to frame event</param>
	/// <returns>always return true</returns>
	bool frameRenderingQueued(const FrameEvent& evt);
	void createFrameListener();
};
