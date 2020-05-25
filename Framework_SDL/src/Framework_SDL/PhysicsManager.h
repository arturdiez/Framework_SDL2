#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H
#include "PhysObject.h"
#include <bitset>

class PhysicsManager {

public: 
	//Colision capas
	enum class CollisionLayers {
		Friendly = 0,
		FriendlyProjectiles,
		Hostile,
		HostileProjectiles,
		//To know lngth of layers
		MaxLayers
	};
	//Colision flags
	enum class CollisionFlags {
		None				= 0x00,
		Friendly			= 0x01,
		FriendlyProjectiles = 0x02,
		Hostile				= 0x04,
		HostileProjectiles  = 0x08
	

	};
private:
	static PhysicsManager* sInstance;

	//Vector de capas de colision
	std::vector<PhysObject*>mCollisionLayers[static_cast<unsigned int>(CollisionLayers::MaxLayers)];
	//Mascaras
	std::bitset<static_cast<unsigned int>(CollisionLayers::MaxLayers)> mLayerMasks[static_cast<unsigned int>(CollisionLayers::MaxLayers)];
	
	unsigned long mLastId;

public:
	static PhysicsManager* Instance();
	static void Release();

	void SetLayerCollisionMask(CollisionLayers layer, CollisionFlags flags);

	unsigned long RegisterObject(PhysObject* object, CollisionLayers layers);
	void UnregisterObject(unsigned long id);

	void Update();
private:
	PhysicsManager();
	~PhysicsManager();
};

inline PhysicsManager::CollisionFlags operator |(PhysicsManager::CollisionFlags a, PhysicsManager::CollisionFlags b) {
	return static_cast<PhysicsManager::CollisionFlags>(static_cast<unsigned int>(a) | static_cast<unsigned int>(b));
}

inline PhysicsManager::CollisionFlags operator &(PhysicsManager::CollisionFlags a, PhysicsManager::CollisionFlags b) {
	return static_cast<PhysicsManager::CollisionFlags>(static_cast<unsigned int>(a) & static_cast<unsigned int>(b));
}

#endif // !PHYSICSMANAGER_H

