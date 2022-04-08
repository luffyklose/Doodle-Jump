#include "Doodle.h"

Doodle::Doodle()
{

	SetSceneNode(nullptr);
	SetEntity(nullptr);
	m_bIsColliding = false;
	SetScale(Ogre::Vector3(0.05f, 0.05f, 0.05f));
	distanceFromCameraToPlayerZAxis = 0;
	isFacingLeft = false;
	camera = nullptr;
	cameraNode = nullptr;
	m_iLivesRemaining = 3;
	m_bGameOver = false;
	m_bGameWon = false;
	playerDiedZValue = -140.0f;

}

Doodle::Doodle(Ogre::SceneNode* node, Ogre::SceneManager* scnMgr)
{
	SetEntity(scnMgr->createEntity("Sinbad.mesh"));
	GetEntity()->setCastShadows(false);

	SetSceneNode(node);
	GetAttachedSceneNode()->attachObject(GetEntity());
	scnMgr->getRootSceneNode()->addChild(GetAttachedSceneNode());
	SetScale(Ogre::Vector3(10.0f, 10.0f, 10.0f));
	GetAttachedSceneNode()->setScale(GetScale());
	GetAttachedSceneNode()->setPosition(Ogre::Vector3(0, 0, 0));
	GetAttachedSceneNode()->roll(Degree(90));
	GetAttachedSceneNode()->pitch(Degree(-90));
	distanceFromCameraToPlayerZAxis = 0;
	isFacingLeft = true;
	m_iLivesRemaining = 3;
	m_fTotalGameTime = 0.0f;

	//Creates box collider for player
	m_bIsColliding = false;
	m_bGameOver = false;
	m_bGameWon = false;
	playerDiedZValue = -150.0f;
	//Creates player follow camera
	CreatePlayerCamera(scnMgr);
}

Doodle::~Doodle()
{
}

Camera* Doodle::GetPlayerCamera()
{
	return camera;
}

int Doodle::GetScore()
{
	return m_iScore;
}

int Doodle::GetLivesRemaining()
{
	return m_iLivesRemaining;
}

bool Doodle::GetIsFacingLeft()
{
	return isFacingLeft;
}

bool Doodle::GetGameOver()
{
	return m_bGameOver;
}

bool Doodle::GetGameWon()
{
	return m_bGameWon;
}

float Doodle::GetVelocityX()
{
	return m_velocityX;
}

float Doodle::GetVelocityZ()
{
	return m_velocityZ;
}

SceneNode* Doodle::GetCameraNode()
{
	return cameraNode;
}

void Doodle::SetScore(int score)
{
	m_iScore = score;
}

void Doodle::SetLivesRemaining(int livesRemaining)
{
	m_iLivesRemaining = livesRemaining;
}


void Doodle::SetIsFacingLeft(bool dir)
{
	isFacingLeft = dir;
}

void Doodle::SetGameOver(bool m_bGameOver)
{
	this->m_bGameOver = m_bGameOver;
}

void Doodle::SetGameWon(bool m_bGameWon)
{
	this->m_bGameWon = m_bGameWon;
}

void Doodle::SetVelocityX(float velocityX)
{
	m_velocityX = velocityX;
}

void Doodle::SetVelocityZ(float velocityZ)
{
	m_velocityZ = velocityZ;
}

void Doodle::SetLiveLabel(Label* label)
{
	m_liveLabel = label;
}

void Doodle::SetScoreLabel(Label* label)
{
	m_scoreLabel = label;
}

void Doodle::CheckBounds()
{
	float m_xBounds = 220;
	float m_zBounds = 165;

	//Check if the player is out of border
	if (GetAttachedSceneNode()->getPosition().x <= -m_xBounds)
	{
		GetAttachedSceneNode()->setPosition(Vector3(m_xBounds - 10, GetAttachedSceneNode()->getPosition().y, GetAttachedSceneNode()->getPosition().z));
	}
	else if (GetAttachedSceneNode()->getPosition().x >= m_xBounds)
	{
		GetAttachedSceneNode()->setPosition(Vector3(-m_xBounds + 10, GetAttachedSceneNode()->getPosition().y, GetAttachedSceneNode()->getPosition().z));
	}
	else if (distanceFromCameraToPlayerZAxis <= playerDiedZValue)
	{
		//Check if the player is dead based on Z position
		//std::cout << distanceFromCameraToPlayerZAxis << std::endl;
		//
		//SetVelocity(Ogre::Vector3(0, 0, GetSpeed()));
		DecrementLivesRemaining();
		if (m_iLivesRemaining <= 0 && !m_bGameOver)
		{
			m_bGameOver = true;
			SetVelocityX(0.0f);
			SetVelocityZ(0.0f);
			GetAttachedSceneNode()->setPosition(0, 0, cameraNode->getPosition().z);
			m_bGameOver = true;
			m_bGameWon = false;
		}
		else
		{
			SetVelocityX(0.0f);
			SetVelocityZ(0.0f);
			GetAttachedSceneNode()->setPosition(0, 0, cameraNode->getPosition().z);
		}
	}
}

void Doodle::IncrementScore()
{
	m_iScore++;
	if (m_scoreLabel != nullptr)
	{
		std::string scoreLabelText= "Score: " + std::to_string(m_iScore);
		m_scoreLabel->setCaption(scoreLabelText);
	}
	//SoundManager::Instance()->PlaySound("Assets/Audio/Ding.wav", 0);
}

void Doodle::DecrementLivesRemaining()
{
	m_iLivesRemaining--;
	if (m_liveLabel != nullptr)
	{
		std::string liveLabelText = "Lives: " + std::to_string(m_iLivesRemaining);
		m_liveLabel->setCaption(liveLabelText);
		std::cout << "lives: " << m_iLivesRemaining << std::endl;
	}
	else
		std::cout << "Live label null" << std::endl;
}

bool Doodle::frameStarted(const Ogre::FrameEvent& evt)
{
	if (!m_bGameOver)
	{
		//Change velocity based on gravity
		m_fTotalGameTime += evt.timeSinceLastFrame;
		m_velocityZ += (50.0f * evt.timeSinceLastFrame);

		//Do necessery check and translate
		GetAttachedSceneNode()->translate(m_velocityX * evt.timeSinceLastFrame, 0.0f, m_velocityZ * evt.timeSinceLastFrame);

		CheckBounds();
		UpdateCameraPosition(evt);
		if (m_iLivesRemaining <= 0)
		{
			GetAttachedSceneNode()->setPosition(Ogre::Vector3(0, 0, 0));
			SetVelocityX(0.0f);
			SetVelocityZ(0.0f);
		}
	}

	return true;
}

void Doodle::CheckForCollisionWithPlatform(Platform* platform)
{
	AxisAlignedBox playerBox = GetAttachedSceneNode()->_getWorldAABB();
	AxisAlignedBox platformBox = platform->GetAttachedSceneNode()->_getWorldAABB();
	if (playerBox.intersects(platformBox))
	{
		//std::cout << "Peng Le player: " << GetAttachedSceneNode()->getPosition().z << " platform: " << platform->GetAttachedSceneNode()->getPosition().z << std::endl;
		if (GetAttachedSceneNode()->getPosition().z <= platform->GetAttachedSceneNode()->getPosition().z - 50.0f && m_velocityZ>=0.0f)
		{
			PlayerHitPlatform();
			if(!platform->GetPointEarned())
			{
				IncrementScore();
				platform->SetPointEarned(true);
			}
		}
	}
}

void Doodle::CreatePlayerCamera(Ogre::SceneManager* scnMgr)
{
	cameraNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	// create the camera
	camera = scnMgr->createCamera("myCam");
	camera->setNearClipDistance(5); // specific to this sample
	camera->setAutoAspectRatio(true);
	cameraNode->attachObject(camera);
	cameraNode->setPosition(0, 400, 0);
	cameraNode->lookAt(Ogre::Vector3(0, 0, 0), Node::TS_WORLD);
}

void Doodle::UpdateCameraPosition(const Ogre::FrameEvent& evt)
{
	distanceFromCameraToPlayerZAxis = cameraNode->getPosition().z - GetAttachedSceneNode()->getPosition().z;
	if (distanceFromCameraToPlayerZAxis > 20)
	{
		cameraNode->translate(0, 0, m_velocityZ * evt.timeSinceLastFrame);
	}
}

void Doodle::UpdatePlayerDirection(char input)
{
	if (input == 'a' && !isFacingLeft)
	{
		isFacingLeft = true;
		GetAttachedSceneNode()->yaw(Degree(-180));
	}
	else if (input == 'd' && isFacingLeft)
	{
		isFacingLeft = false;
		GetAttachedSceneNode()->yaw(Degree(180));
	}
}

void Doodle::PlayerHitPlatform()
{
	SetVelocityZ(-125.0f);
	//std::cout << "Tan Qi Lai" << std::endl;
}