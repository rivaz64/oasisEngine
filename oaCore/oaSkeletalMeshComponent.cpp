#include "oaSkeletalMeshComponent.h"
#include "oaSkeletalModel.h"
#include "oaResoureManager.h"
namespace oaEngineSDK
{

COMPONENT_TYPE::E 
SkeletalMeshComponent::getType()
{
  return COMPONENT_TYPE::kSkeletalMesh;
}

void 
SkeletalMeshComponent::save(Serializer& serializer)
{
  serializer.encodeString(m_model.lock()->getName());
}

void 
SkeletalMeshComponent::load(Serializer& serializer)
{
  auto modelName = serializer.decodeString();
  setModel(cast<SkeletalModel>(ResoureManager::instance().getResourse(modelName)));
}

}

