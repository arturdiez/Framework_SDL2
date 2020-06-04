#ifndef _GAMEMANAGER_H
#define _GAMEMANAGER_H

#include "SceneManager.h"

//!  GameManager Class. 
/*!
  Singleton
  In charge of the game loop.
  In charge of scene changes.
*/

class GameManager {
private:
	//! FRAME_RATE private variable
   /*! target frame rate for the game */
	const int FRAME_RATE = 60;
	
	//! sInstance private static GameManager pointer variable.
   /*! 
		Pointer to this class to make it a singleton.
   */
	static GameManager* sInstance;

public:
	//! Instance static GameManager pointer function.
   /*!
		Creates an instance of an object of this class or returns that instance of the object if it already exists.
   */
	static GameManager* Instance();


	 //! Release function.
    /*!
      Deletes the instance (sInstance) of this class.
    */
	static void Release();
	
	//! GameState enum.
   /*! The states of the game are the scenes where you can be when the game is running */
	enum GameState {MENU,  /*!< Enum value MENU. */
		PLAY,			  /*!< Enum value PLAY. */
		COLLISIONTEST,	 /*!< Enum value COLLISIONTEST. */
		EXIT			 /*!< Enum value EXIT. */
	};

	//! mGameState variable.
   /*!
	 Stores the game state.
   */
	GameState mGameState;

	//! mCurrentScene SceneManager pointer.
   /*!
	 used to keep track of the running scene
   */
	SceneManager* mCurrentScene;

	//! mTimer Timer pointer.
   /*!
	 Used to limit the frame rate
   */
	Timer* mTimer;

	//! Run void function.
   /*!
	 Contains the game loop.
   */
	void Run();
	
	//! GameManager Constructor.
   /*!
	 Initializes mGameState, mCurrentScene and mTimer.
	 \sa mGameState, mCurrentScene, mTimer, ~GameManager
   */
	GameManager();

	//! GameManager Destructor.
   /*!
	 Releases mGameState, mCurrentScene, and mTimer.
	 \sa mGameState, mCurrentScene, mTimer, GameManager
   */
	~GameManager();
};

#endif 
