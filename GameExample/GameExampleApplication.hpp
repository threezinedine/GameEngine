#pragma once
#include <NTTEngine/NTTEngine.hpp>


class GameExampleApplication: public ntt::Application
{
    public:
        GameExampleApplication()
            : Application(600, 800, "Example")
        {

        } 

        ~GameExampleApplication()
        {

        }

        void OnSetupImpl() override;
        void OnUpdateImpl() override;
    private:
        unsigned int vao_, vbo_, vio_;
};