#pragma once
#include <iostream>
#include <chrono>

namespace dae
{
    struct TrashTransform
    {
        float matrix[16] =
        {
            1,0,0,0,
            0,1,0,0,
            0,0,1,0,
            0,0,0,1
        };
    };

    struct TrashGameObject
    {
    public:
        TrashTransform local;
        int id{};

        TrashGameObject* operator*=(int other)
        {
            this->id *= other;
            return this;
        }
    };

    struct TrashGameObjectAlt
    {
    public:
        TrashTransform* local;
        int id;

        TrashGameObjectAlt* operator*=(int other)
        {
            this->id *= other;
            return this;
        }
    };

    template<class T>
    void TrashCache(T* buffer, size_t size, std::vector<std::vector<float>>& timeSamples)
    {

        for (size_t step{ 1 }; step <= 1024; step *= 2)
        {
            const auto start = std::chrono::high_resolution_clock::now();
            for (size_t i = 0; i < size; i += step)
            {
                buffer[i] *= 2;
            }

            const auto end = std::chrono::high_resolution_clock::now();
            const long long total = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();


            //Calculate place in array
            const float castedStep{ static_cast<float>(step) };
            const float arrayPositionF{ std::log2f(castedStep) };
            const int placeInArray{ static_cast<int>(arrayPositionF) };

            timeSamples[placeInArray].emplace_back(static_cast<float>(total));
        }
    }

}

