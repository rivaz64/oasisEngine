#pragma once
#include<vector>
#include<list>
#include <stack>
#include <queue>
#include <deque>
#include <string>
#include <memory>
#include<algorithm>
namespace oaEngineSDK {
/**
 * @brief wraper of the std::vector, can be changed in the future
 * @tparam T 
*/
template <class T>
using Vector = std::vector<T>;

/**
 * @brief wraper of the std::list, can be changed in the future
 * @tparam T 
*/
template <class T>
using List = std::list<T>;

/**
 * @brief wraper of the std::stack, can be changed in the future
 * @tparam T 
*/
template <class T>
using Stack = std::stack<T>;

/**
 * @brief wraper of the std::queue, can be changed in the future
 * @tparam T 
*/
template <class T>
using Queue = std::queue<T>;

/**
 * @brief wraper of the std::priority_queue, can be changed in the future
 * @tparam T 
*/
template <class T>
using PriorityQueue = std::priority_queue<T>;

/**
 * @brief wraper of the std::priority_queue, can be changed in the future
 * @tparam T
*/
template <class T>
using PriorityQueue = std::priority_queue<T>;

/**
 * @brief wraper of the std::string, can be changed in the future
 * @tparam T
*/
using String = std::string;

/**
 * @brief wraper of the std::wstring, can be changed in the future
 * @tparam T
*/
using WString = std::wstring;

/**
 * @brief wraper of the std::shared_ptr, can be changed in the future
 * @tparam T
*/
template <class T>
using SPTr = std::shared_ptr<T>;

}