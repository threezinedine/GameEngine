#pragma once
#include <NTTEngine/NTTEngine.hpp>


class GameExampleApplication: public ntt::Application
{
    public:
        GameExampleApplication()
            : Application(900, 1200, "Example")
        {
            PROFILE_SCOPE();
        } 

        ~GameExampleApplication()
        {
            PROFILE_SCOPE();
        }

        void OnSetupImpl() override;
        void OnUpdateImpl(ntt::Timestep ts) override;
    private:
        unsigned int vao_, vbo_, vio_;
};