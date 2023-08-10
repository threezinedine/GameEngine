#pragma once
#include <NTTEngine/NTTEngine.hpp>

class TestLayer: public ntt::Layer
{
    public:
        TestLayer();
        ~TestLayer();

        void OnUpdate() override;

    private:
        unsigned int vao_;
        unsigned int vbo_;
        unsigned int vio_;
};