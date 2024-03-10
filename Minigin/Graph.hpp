#pragma once
//#include <imgui.h>
#include <imgui_plot.h>

#include "TrashTheCache.h"


namespace dae
{
    template <typename T>
    struct Graph
    {
        bool canCompute = false;
        bool hasComputedOnce = false;
        float times[11];

        static inline  int samples{ 100 };

        void Render()
        {
            if (canCompute)
            {
                hasComputedOnce = true;
                canCompute = false;

                //reset
                for (int i{ 0 }; i < 11; ++i)
                {
                    times[i] = 0;
                }

                //do calculation with the number of samples
                for (int i{ 0 }; i < samples; ++i)
                {
                    static size_t iterations{ 100000 };
                    T* integerOperations{ new T[iterations]{} };
                    dae::TrashCache<T>(integerOperations, iterations, times);
                    delete[] integerOperations;
                }

                //divide result by nbr of samples
                for (int i{ 0 }; i < 11; ++i)
                {
                    times[i] /= samples;
                }
                
            }


            ImGui::PlotConfig testConfig{};

            float xValues[11]{ 1,2,3,4,5,6,7,8,9,10,11 };
            float* yValues{ times };

            testConfig.values = { xValues, yValues, 11 };
            testConfig.scale = { -1, times[0] };

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

