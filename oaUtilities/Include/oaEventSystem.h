#pragma once

#include "oaPrerequisitesUtilities.h"
#include "oaModule.h" 

namespace oaEngineSDK{


template <typename... _Types>
struct Event
{
  void* objectPtr;
  void (*function)(void* object_ptr, _Types&&...);
};



template<typename... Types>
class EventHandler
{
 public:

  /**
   * @brief suscribes an event
   * @tparam T 
   * @tparam ..._Types 
   * @param eventid 
   * @param objectPtr 
  */
  template <class T,void (T::*Method)(Types...)>
  void
  suscribe(uint64 eventId, T* objectPtr){
    Event<Types...> newEvent;
    newEvent.objectPtr = objectPtr;
    newEvent.function = &methodToFunction<T,Method>;
    events[eventId].push_back(newEvent);
  }

  /**
   * @brief executes all the events subscribed
   * @tparam ..._Types 
  */
  void 
  publish(uint64 eventId, Types... _Args){
    for(auto &thisEvent : events[eventId]){
      (*thisEvent.function)(thisEvent.objectPtr,std::forward<Types>(_Args)...);
    }
  }

 private:
  
  template <class T,void (T::*method)(Types...)>
  static void methodToFunction(void* object_ptr, Types&&... _Args)
  {
    T* p = static_cast<T*>(object_ptr);
    return (p->*method)(std::forward<Types>(_Args)...); 
  }

  Map<uint64, vector<Event<Types...>>> events;
};

}


/*#pragma once

#include "oaPrerequisitesUtilities.h"
#include "oaModule.h" 

namespace oaEngineSDK{

typedef ;

struct EventInterface{};

template <class Type>
struct Event : 
  public EventInterface
{
  void* objectPtr;
  void (*function)(void* object_ptr, Type);
};

template <class T,class Type, void (T::*Method)(Type)>
static void methodToFunction(void* object_ptr, Type arguments)
{
  T* p = static_cast<T*>(object_ptr);
  return (p->*Method)(arguments); 
}

class EventSystem :
  public Module<EventSystem>
{
 public:
   
  /**
   * @brief suscribes an event
   * @tparam T 
   * @tparam ..._Types 
   * @param eventid 
   * @param objectPtr 
  
  template <class T,class Type,void (T::*Method)(Type)>
  void
  suscribe(uint64 eventId, T* objectPtr){
    Event newEvent;
    newEvent.objectPtr = objectPtr;
    newEvent.function = &methodToFunction<T,Type,Method>;
  }

  /**
   * @brief executes all the events subscribed
   * @tparam ..._Types 
  
  template <class Type>
  void 
  publish(uint64 eventId, Type  arguments){
    for(auto &thisEvent : events[eventId]){
      auto& eventCasted = reinterpret_cast<Event<Type>>(thisEvent);
      (*eventCasted.function)(eventCasted.object, arguments);
    }
  }

 private:
  
  Map<uint64, vector<EventInterface*>> events;
  
  friend class Module<EventSystem>;
};

}
*/