#pragma once
#include <opencv2/opencv.hpp>


namespace ntt
{
    class ImGuiImage
    {
        public:
            ImGuiImage();
            ~ImGuiImage();

            void Bind();
            void SetImage(cv::Mat image);
            void UnBind();

            inline unsigned int* GetId() { return &id_; }

        private:
            unsigned int id_;
    };
}