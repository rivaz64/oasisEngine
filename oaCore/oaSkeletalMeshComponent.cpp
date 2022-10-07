#include "oaSkeletalMeshComponent.h"
#include "oaSkeletalModel.h"
#include "oaResoureManager.h"
#include "oaSkeletalMesh.h"
#include "oaSkeleton.h"
#include "oaAnimation.h"

namespace oaEngineSDK
{

SkeletalMeshComponent::SkeletalMeshComponent(WPtr<SkeletalModel> wModel)
{
  setModel(wModel);
  auto model = wModel.lock();
  auto numOfMeshes = model->getNumOfMeshes();
  for(SIZE_T i = 0; i<numOfMeshes; ++i){
    m_bones.push_back({});
    m_bones[i].resize(1024);
  }
  
}

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

void
readNodeHeirarchy(
  SPtr<SkeletalNode> node, 
  const Matrix4f& parentTransform,
  float time,
  SPtr<Animation> animation,
  SPtr<SkeletalModel> model,
  Vector<Vector<Matrix4f>>& bones,
  const Matrix4f& globalInverse
  )
{
  Matrix4f nodeTransform = Matrix4f::IDENTITY;
  if(animation->hasChannel(node->name)){
    nodeTransform = animation->getTransformOfChannelAtTime(node->name,time);
  }
  auto globalTransform = parentTransform*nodeTransform;

  auto numOfMeshes = model->getNumOfMeshes();

  for(SIZE_T i = 0; i<numOfMeshes; ++i){

    auto wMesh = model->getMesh(i);

    if(wMesh.expired()) continue;

    auto mesh = wMesh.lock();

    if(mesh->hasBone(node->name)){
      auto id = mesh->getBoneId(node->name);
      bones[i][id] = globalInverse*globalTransform*mesh->getBoneAt(id);
    }
  }
  

  for(auto child : node->childs){
    readNodeHeirarchy(child,globalTransform,time,animation,model,bones,globalInverse);
  }
}

void
SkeletalMeshComponent::setAtSecond(float time)
{
  if(m_model.expired()) return;
  auto model = m_model.lock();

  auto wAnimation = model->getAnimation();
  if(wAnimation.expired()) return;
  auto animation = wAnimation.lock();

  auto wSkeleton = model->getSkeleton();
  if(wSkeleton.expired()) return;
  auto skeleton = wSkeleton.lock();

  float timeInTicks = time;// * animation->getSecondPerTicks();

  readNodeHeirarchy(skeleton->getRoot(),Matrix4f::IDENTITY,timeInTicks,animation,model,m_bones,skeleton->getGlobalInverse());
}

}

