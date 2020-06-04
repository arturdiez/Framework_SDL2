#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H
#include "PhysObject.h"
#include <bitset>

//!  PhysicsManager Class. 
/*!
  Singleton
  Sets collision for physic objects.
  Creates collision layers.
  Updates physic objects.
*/
class PhysicsManager {

public: 
	//! CollisionLayers enum.
   /*! Types of collision where objects in the game belong
       \sa CollisionFlags
   */
	enum class CollisionLayers {
		Friendly = 0,			/*!< Enum value Friendly. */
		FriendlyProjectiles,	 /*!< Enum value FriendlyProjectiles. */
		Hostile,				/*!< Enum value Hostile. */
		HostileProjectiles,		/*!< Enum value HostileProjectiles. */
		//To know length of layers
		MaxLayers				/*!< Enum value MaxLayers. */
	};
	//! CollisionFlags enum.
   /*! Types of collision to check for collisions with other types
	   \sa CollisionLayers
   */
	enum class CollisionFlags {
		None				= 0x00,/*!< Enum value None. */
		Friendly			= 0x01,/*!< Enum value Friendly. */
		FriendlyProjectiles = 0x02,/*!< Enum value FriendlyProjectiles. */
		Hostile				= 0x04,/*!< Enum value Hostile. */
		HostileProjectiles  = 0x08/*!< Enum value HostileProjectiles. */
	};

private:
	//! Instance static PhysicsManager pointer function.
   /*!
		Creates an instance of an object of this class or returns that instance of the object if it already exists.
   */
	static PhysicsManager* sInstance;

	//! mCollisionLayers vector of PhysObject pointer array.
   /*!
	Array that Contains a vector of physic objects for each collision layer.
	Keeps track of the physic objects that are in a collision layer.
   */
	std::vector<PhysObject*>mCollisionLayers[static_cast<unsigned int>(CollisionLayers::MaxLayers)];
	
	//! mLayerMasks bitset of MaxLayers array
   /*!
	Array that contains a bitset of collision flags
	Keeps track of the collision Masks being used in a scene.
   */
	std::bitset<static_cast<unsigned int>(CollisionLayers::MaxLayers)> mLayerMasks[static_cast<unsigned int>(CollisionLayers::MaxLayers)];
	
	//! mLastId unsigned long
   /*!
	ID of physic objects that will be contained in mCollisionLayers
	\sa mCollisionLayers
   */
	unsigned long mLastId;

public:
	//! Instance static PhysicsManager pointer function.
	/*!
		Creates an instance of an object of this class or returns that instance of the object if it already exists.
	*/
	static PhysicsManager* Instance();
	//! Release function.
	/*!
	  Deletes the instance (sInstance) of this class.
	*/
	static void Release();


	//! SetLayerCollisionMask function.
	/*!
	 Creates collision masks between flags given a layer.
	 \param layer CollisionLayers
	 \param flags CollisionFlags
	*/
	void SetLayerCollisionMask(CollisionLayers layer, CollisionFlags flags);

	//! RegisterObject function.
	/*!
		Adds a physics object to the collision layer.
	 \param object PhysObject pointer
	 \param layers CollisionLayers
	 \return mLastId unsigned long
	 \sa mLastId, UnregisterObject
	*/
	unsigned long RegisterObject(PhysObject* object, CollisionLayers layers);

	//! UnregisterObject function.
	/*!
		Gets rid of the object in the collision layer given its id.
	 \param id unsigned long
	 \sa mLastId, RegisterObject
	*/
	void UnregisterObject(unsigned long id);

	//! Update function.
	/*!
		Checks for collisions in the collision layer mask
		\sa SetLayerCollisionMask
	*/
	void Update();
private:
	//! PhysicsManager Constructor.
	/*!
		Initializes mLayerMasks
		\sa mLayerMasks, ~PhysicsManager
	*/
	PhysicsManager();

	//! PhysicsManager Destructor.
	/*!
		clears mCollisionLayers
		\sa mCollisionLayers, Physicsmanager
	*/
	~PhysicsManager();
};
//! operator |
   /*!
	OR bit wise check between collision flags.
   */
inline PhysicsManager::CollisionFlags operator |(PhysicsManager::CollisionFlags a, PhysicsManager::CollisionFlags b) {
	return static_cast<PhysicsManager::CollisionFlags>(static_cast<unsigned int>(a) | static_cast<unsigned int>(b));
}
//! operator &
   /*!
	 AND bit wise check between collision flags.
   */
inline PhysicsManager::CollisionFlags operator &(PhysicsManager::CollisionFlags a, PhysicsManager::CollisionFlags b) {
	return static_cast<PhysicsManager::CollisionFlags>(static_cast<unsigned int>(a) & static_cast<unsigned int>(b));
}

#endif // !PHYSICSMANAGER_H

