#ifndef _SCENEMANAGER_H
#define _SCENEMANAGER_H
#include "Sprite.h"
#include "InputManager.h"
#include "AudioManager.h"
//!  SceneManager Class. 
/*!
  Singleton
  Virtual class.
  In charge of scene state changes.
*/
class SceneManager {
private:
	//! sInstance private static SceneManager pointer variable.
	/*!
	 Pointer to this class to make it a singleton.
	*/
	static SceneManager* sInstance;

public:
	//! SceneState enum.
   /*! The states of the scene that the game is playing */
	enum SceneState {RUNNING,/*!< Enum value RUNNING. */ 
		GOTO_PLAY,			 /*!< Enum value GOTO_PLAY. */ 
		GOTO_COLLISION,		 /*!< Enum value GOTO_COLLISION. */ 
		EXIT};				 /*!< Enum value EXIT. */ 
	
	
	//! getSceneState function.
	/*!
	  \return SceneState enum value.
	*/
	SceneState getSceneState();
	
	//! mSceneState variable.
   /*!
	 Stores the scene state.
   */
	SceneState mSceneState;

	//! Instance static SceneManager pointer function.
   /*!
		Creates an instance of an object of this class or returns that instance of the object if it already exists.
   */
	static SceneManager* Instance();
	//! Release function.
   /*!
	 Deletes the instance (sInstance) of this class.
   */
	static void Release();
	
	//! EarlyUpdate virtual function.
   /*!
	Used for handeling events in child classes.
   */
	virtual void EarlyUpdate();

	//! Update virtual function.
   /*!
	Used for updating objects in child classes.
   */
	virtual void Update();

	//! LateUpdate virtual function.
   /*!
	Used for handeling collisions in child classes.
   */
	virtual void LateUpdate();

	//! Render virtual function.
   /*!
	Used for rendering objects in child classes.
   */
	virtual void Render();

	//! SceneManager Constructor.
   /*!
	 Initializes mSceneState
	 \sa ~SceneManager()
   */
	SceneManager();

	//! SceneManager Destructor.
   /*!
	 Empty.
	 \sa SceneManager()
   */
	~SceneManager();

	

};
#endif 

