#include "PlayerStateDeadAnimation.h"

using namespace Engine;
using namespace Engine::Objects;
using namespace Engine::Manager;
using namespace Engine::Transform;

void PlayerStateDeadAnimation::Initialize([[maybe_unused]] Player* p)
{
	gameObjectInstance_ = GameObjectManager::GetInstance();

	filePath_ = "FallDown";
	AnimationManager::GetInstance()->LoadAnimation(filePath_);
	deadAnimationData_ = AnimationManager::GetInstance()->GetData(filePath_);
}


void PlayerStateDeadAnimation::Update([[maybe_unused]] Player* p)
{

}
