#include "oaScene.h"
#include "oaActor.h"

namespace oaEngineSDK{

void
Scene::init(){
  m_root = newSPtr<Actor>();
}

}
