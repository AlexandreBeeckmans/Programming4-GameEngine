#pragma once
#include <functional>
#include <unordered_map>
#include <any>
#include <stdexcept>

#include "Singleton.h"

namespace dae
{
	class BaseComponent;
}

namespace dae
{
    enum class EventType
    {
	    
    };

    class EventManager : public Singleton<EventManager>
    {
    public:

        template <typename ClassType, typename... Args>
        void AddFunction(const int& id, ClassType* obj, void (ClassType::* memFunc)(Args...), Args&&... args)
        {
            auto pair = std::make_pair([obj, func = std::bind(memFunc, obj, std::forward<Args>(args)...)]() {
                func();
                }, nullptr
            );
            m_Functions[id].emplace_back(pair);
        }
        
        template <typename ClassType, typename... Args>
        void AddFunctionWithComp(const int& id, dae::BaseComponent* pComp, ClassType* obj, void (ClassType::* memFunc)(Args...), Args&&... args)
        {
            auto pair = std::make_pair([obj, func = std::bind(memFunc, obj, std::forward<Args>(args)...)]() {
                func();
                }, pComp
            );
            m_Functions[id].emplace_back(pair);
        }


        void CallFunction(const int id)
        {
            auto it = m_Functions.find(id);
            if(it != m_Functions.end())
            {
	            for (auto element : it->second)
	            {
                    element.first();

                    
	            }
            }
        }

        void CallFunctionFromComponent(const int id, const dae::BaseComponent* pComp)
        {
            auto it = m_Functions.find(id);
            if (it != m_Functions.end())
            {
                for (auto element : it->second)
                {
                    if(element.second == pComp)
						element.first();


                }
            }
        }

        void ClearFunctions()
        {
            m_Functions.clear();
        }
    private:
        std::unordered_map<int, std::vector<std::pair<std::function<void()>,dae::BaseComponent*>>> m_Functions;
    };
}



