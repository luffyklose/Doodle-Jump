#include "Game.h"
#include<SDL.h>

#include <iostream>

Game::Game():ApplicationContext("GAME3121 - Assignment 2 - Zihan Xu & Yiliqi")
{
}

void Game::setup()
{
    // do not forget to call the base first
    ApplicationContext::setup();
    addInputListener(this);

    // get a pointer to the already created root
    root = getRoot();
    scnMgr = root->createSceneManager();

    // register our scene with the RTSS
    RTShader::ShaderGenerator* shadergen = RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(scnMgr);
    
    createScene();
    //createCamera();   
    createFrameListener();

    //SoundManager::Instance()->InitAll();
    //SoundManager::Instance()->PlayMusic("Assets/Audio/Battle_BGM.wav",-1);
}

bool Game::keyPressed(const KeyboardEvent& evt)
{
    switch (evt.keysym.sym)
    {
    //case SDLK_ESCAPE:
        //getRoot()->queueEndRendering();
        //break;
    case 'a':
        //Move Left
        m_doodle->UpdatePlayerDirection('a');
        m_doodle->SetVelocityX(-250.0f);
        break;
    case 'd':
        //Move Right
        m_doodle->UpdatePlayerDirection('d');
        m_doodle->SetVelocityX(250.0f);
        break;
    default:
        break;
    }
    return true;
}

bool Game::keyReleased(const KeyboardEvent& evt)
{
    switch (evt.keysym.sym)
    {
    case 'a':
        m_doodle->SetVelocityX(0.0f);
        break;
    case 'd':
        m_doodle->SetVelocityX(0.0f);
        break;
    default:
        break;
    }
    return true;
}

void Game::createScene()
{
    Ogre::SceneNode* node = scnMgr->createSceneNode("Node1");
    scnMgr->getRootSceneNode()->addChild(node);
    scnMgr->setAmbientLight(ColourValue(0.9, 0.9, 0.9));
    Ogre::Light* light = scnMgr->createLight("Light1");
    light->setType(Ogre::Light::LT_DIRECTIONAL);
    light->setDirection(Ogre::Vector3(1, -1, 0));

    // Set Light Color
    light->setDiffuseColour(1.0f, 1.0f, 1.0f);
    // Set Light Reflective Color
    light->setSpecularColour(1.0f, 1.0f, 0.0f);

    float xPlatformBounds = 125;

    //Generate 15 platforms in random X position and fixed Z position
    for (int i = 0; i < m_platformNumber; i++)
    {
        std::string nodeName = "Platform" + std::to_string((1 + i));
        m_platformVec.push_back(new Platform(scnMgr->createSceneNode(nodeName), scnMgr, (i + 1)));

        float ranXVal = Math::RangeRandom(-xPlatformBounds, xPlatformBounds);
        float ranZVal = Math::RangeRandom(0, 25);
        m_platformVec[i]->GetAttachedSceneNode()->setPosition(ranXVal, 0, -100 * i + 125.f - ranZVal);
    }
    m_platformVec[0]->GetAttachedSceneNode()->setPosition(0, 0, 150);

    mTrayMgr = new OgreBites::TrayManager("InterfaceName", getRenderWindow());

    //you must add this in order to add a tray
    scnMgr->addRenderQueueListener(mOverlaySystem);
    //Once you have your tray manager, make sure you relay input events to it.
    addInputListener(mTrayMgr);

    //Hide mouse cursor and create UI labels
    mTrayMgr->hideCursor();
    m_scoreLabel = mTrayMgr->createLabel(TL_TOPLEFT, "L_SCORE", "SCORE: 0", 150);
    m_liveLabel = mTrayMgr->createLabel(TL_TOPLEFT, "L_LIVES", "LIVES: 5", 150);
    m_timeLabel= mTrayMgr->createLabel(TL_TOPRIGHT, "L_TIME", "TIME: 0.167", 150);
    m_frameLabel = mTrayMgr->createLabel(TL_TOPRIGHT, "L_FRAME", "FPS: 60", 150);

    //Initialize player
    m_doodle = new Doodle(scnMgr->createSceneNode("Ball"), scnMgr);
    m_doodle->SetLiveLabel(m_liveLabel);
    std::string liveLabelText = "Lives: " + std::to_string(m_doodle->GetLivesRemaining());
    m_liveLabel->setCaption(liveLabelText);
    m_doodle->SetScoreLabel(m_scoreLabel);
    std::string scoreLabelText = "Score: " + std::to_string(m_doodle->GetScore());
    m_scoreLabel->setCaption(scoreLabelText);

    //Intialize background image
    m_backgroundImage[0] = new BackgroundImage(scnMgr->createSceneNode("BackgroundNode1"), scnMgr, m_doodle, 0);
    m_backgroundImage[1] = new BackgroundImage(scnMgr->createSceneNode("BackgroundNode2"), scnMgr, m_doodle, 1);
    m_backgroundImage[1]->GetAttachedSceneNode()->setPosition(0, -10, -m_backgroundImage[1]->GetBackgroundZExtent());

    Ogre::Viewport* viewport = getRenderWindow()->addViewport(m_doodle->GetPlayerCamera());
    viewport->setBackgroundColour(Ogre::ColourValue(0.0, 0.0, 0.0));
    m_doodle->GetPlayerCamera()->setAspectRatio(Ogre::Real(viewport->getActualWidth()) / Ogre::Real(viewport->getActualHeight()));
}

void Game::createCamera()
{
    SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();

    // create the camera
    Camera* cam = scnMgr->createCamera("myCam");
    cam->setNearClipDistance(0.0001f); // specific to this sample
    cam->setAutoAspectRatio(true);
    cam->setProjectionType(Ogre::ProjectionType::PT_PERSPECTIVE);
    camNode->attachObject(cam);
    getRenderWindow()->addViewport(cam);

    m_windowWidth = (getRenderWindow()->getViewport(0)->getActualWidth() / 2.0f) - 50.0f;
    m_windowHeight = (getRenderWindow()->getViewport(0)->getActualHeight() / 2.0f) - 50.0f;
    camNode->setPosition(0, 0, m_windowWidth);
}


bool Game::frameRenderingQueued(const FrameEvent& evt)
{
    //check collision between player and every platform
    for(int i=0;i<m_platformVec.size();i++)
    {
        m_doodle->CheckForCollisionWithPlatform(m_platformVec[i]);
    }

    /*
    for(auto platform: m_platformVec)
    {
	    if(platform->GetAttachedSceneNode()->getPosition().z>=200)
	    {
            m_randomPositionX = Math::RangeRandom(m_randomPositionX - 50.0f, m_randomPositionX + 50.0f);
            m_randomPositionX = Math::Clamp(m_randomPositionX, -125.0f, 125.0f);
            platform->GetAttachedSceneNode()->setPosition(m_randomPositionX, 0.0f, -50.0f);
            std::cout << "new position" << platform->GetAttachedSceneNode()->getPosition().x << " " << platform->GetAttachedSceneNode()->getPosition().z << std::endl;
	    }
    }
    */

    //Check if the game is over
    if(m_doodle->GetScore()>= m_platformNumber && !m_doodle->GetGameOver())
    {
        m_doodle->SetGameOver(true);
        m_doodle->SetGameWon(true);
    }

    //Show game over UI
    if(m_doodle->GetGameOver() && !m_gameOverLabel)
    {
        m_gameOverLabel = mTrayMgr->createLabel(TL_CENTER, "Game Over Label", "Game Lost", 250);
        if(m_doodle->GetGameWon())
        {
            m_gameOverLabel->setCaption("YOU WON");
        }
        else
        {
            m_gameOverLabel->setCaption("YOU LOSE");
        }        
        m_doodle->GetAttachedSceneNode()->setVisible(false);
        for (int i = 0; i < m_platformVec.size(); i++)
            m_platformVec[i]->GetAttachedSceneNode()->setVisible(false);
    }

    char time[20];
    sprintf_s(time, "Time/Update:: %.1f", evt.timeSinceLastFrame);
    m_frameLabel->setCaption(time);
    //m_TimeText = "Time/Update: " + std::to_string(evt.timeSinceLastFrame);
    //m_timeLabel->setCaption(m_TimeText);

    char fps[20];
    sprintf_s(fps, "FPS: %.1f", 1 / evt.timeSinceLastFrame);
    m_frameLabel->setCaption(fps);
    //m_FPSText = "FPS: " + std::to_string(1 / evt.timeSinceLastFrame);
    //m_frameLabel->setCaption(m_FPSText);

    return true;
}

void Game::createFrameListener()
{
    Ogre::FrameListener* DoodlePlayerFrameListener = m_doodle;
    Ogre::FrameListener* Background1FrameListener = m_backgroundImage[0];
    Ogre::FrameListener* Background2FrameListener = m_backgroundImage[1];

    mRoot->addFrameListener(DoodlePlayerFrameListener);
    mRoot->addFrameListener(Background1FrameListener);
    mRoot->addFrameListener(Background2FrameListener);
}