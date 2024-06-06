#pragma once
#include <functional>
#include <unordered_map>
#include <any>
#include <stdexcept>

#include "Singleton.h"

namespace dae
{
    class EventManager : public Singleton<EventManager>
    {
    public:
        
        template <typename ClassType, typename... Args>
        void AddFunction(const int& id, ClassType* obj, void (ClassType::* memFunc)(Args...), Args&&... args)
        {
            m_Functions[id].emplace_back([obj, func = std::bind(memFunc, obj, std::forward<Args>(args)...)]() {
                func();
                });
        }


        void CallFunction(const int id)
        {
            auto it = m_Functions.find(id);
            if(it != m_Functions.end())
            {
	            for (auto element : it->second)
	            {
                    element();
	            }
            }
        }
    private:
        std::unordered_map<int, std::vector<std::function<void()>>> m_Functions;
    };
}



