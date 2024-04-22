#pragma once
#include <algorithm>
#include <numeric>

#include <vector>

#include <imgui_plot.h>
#include "TrashTheCache.h"


namespace dae
{
    template <typename T>
    struct Graph
    {
        bool canCompute = false;
        bool hasComputedOnce = false;
        std::vector<std::vector<float>> times{};

        std::vector<float> averageTimes{};

        int samples{ 100 };

        void Render(const ImColor& color)
        {
            if (canCompute)
            {
                hasComputedOnce = true;
                canCompute = false;

                //reset
                for (std::vector<float>& curr : times)
                {
                    curr.clear();
                }
                times.clear();
                times.resize(11);
                averageTimes.clear();

                //do calculation with the number of samples
                for (int i{ 0 }; i < samples; ++i)
                {
                    static size_t iterations{ 1'000'000 };
                    T* integerOperations{ new T[iterations]{} };
                    dae::TrashCache<T>(integerOperations, iterations, times);
                    delete[] integerOperations;
                }

                //calculate average time
                for (const std::vector<float>& currVec : times)
                {
                    auto minmax = std::minmax_element(std::begin(currVec), std::end(currVec));


                    float sum = static_cast<float>(std::accumulate(std::begin(currVec), std::end(currVec), 0.0f) - (*minmax.first) - (*minmax.second));
                    auto averageDuration = static_cast<float>(sum) / (currVec.size() - 2);

                    averageTimes.push_back(averageDuration);
                }
                
            }


            ImGui::PlotConfig testConfig{};

            float xValues[11]{ 1,2,3,4,5,6,7,8,9,10,11 };
            float* yValues{ averageTimes.data() };

            testConfig.values = { xValues, yValues, 11 };
            testConfig.scale = { -1, averageTimes[0] };

            testConfig.values.color = color;

            testConfig.tooltip.show = true;
            testConfig.tooltip.format = "x=%.2f, y=%.2f";
            testConfig.grid_x.show = true;
            testConfig.grid_y.show = true;
            testConfig.frame_size = ImVec2(200, 100);
            testConfig.line_thickness = 2.f;

            ImGui::Plot("test", testConfig);
        }
    };
}

