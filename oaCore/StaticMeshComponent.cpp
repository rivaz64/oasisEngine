#include "oaStaticMeshComponent.h"
#include "oaSerializer.h"
#include "oaModel.h"
#include "oaResoureManager.h"

namespace oaEngineSDK
{

REGISTER_CLASS(Component,StaticMeshComponent);

COMPONENT_TYPE::E 
StaticMeshComponent::getType()
{
  return COMPONENT_TYPE::kStaticMesh;
}

void 
StaticMeshComponent::save(Serializer& serializer)
{
  serializer.encodeString(m_model.lock()->getName());
}

void 
StaticMeshComponent::load(Serializer& serializer)
{
  auto modelName = serializer.decodeString();
  setModel(cast<Model>(ResoureManager::instance().getResourse(modelName)));
}

}

