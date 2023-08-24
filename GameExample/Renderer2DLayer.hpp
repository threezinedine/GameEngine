#pragma once
#include <queue>
#include "Storage.hpp"
#include "NTTEngine/NTTEngine.hpp"


class Renderer2DLayer: public ntt::Layer
{
    public:
        Renderer2DLayer(std::shared_ptr<ntt::Camera>& camera);
        ~Renderer2DLayer();
        virtual void OnUpdate(ntt::Timestep ts) override;

        void OnImGuiRenderImpl(ntt::Timestep ts) override;

    protected:
        void OnKeyPress(ntt::KeyPressEvent& event) override;
        void Reset();
        void Lose();

    private:
        std::shared_ptr<ntt::Camera>& camera_;

        std::unique_ptr<ntt::ThreadValue<float>> movingSpeed_;
        std::unique_ptr<ntt::ThreadValue<float>> pillarYShift_;
        std::unique_ptr<ntt::ThreadValue<float>> pillarDistance_;
        std::unique_ptr<ntt::ThreadValue<float>> pillarRandomRange_;
        std::unique_ptr<ntt::ThreadArray<float>> pillarSize_;
        std::unique_ptr<ntt::ThreadValue<float>> pillarStartX_;

        std::unique_ptr<ntt::ThreadArray<float>> birdOffset_;
        std::unique_ptr<ntt::ThreadArray<float>> birdSize_;

        std::unique_ptr<ntt::ThreadValue<float>> gravity_;
        std::unique_ptr<ntt::ThreadValue<float>> pushVelocity_;

        std::unique_ptr<ntt::ThreadValue<float>> loseOffset_;
        std::unique_ptr<ntt::ThreadValue<float>> birdColisionFactor_;

        std::unique_ptr<ntt::NTTVec3> squareColor_;
        std::shared_ptr<ntt::Storage> storage_;
        std::shared_ptr<ntt::Texture2D> birdTexture_, backgroundTexture_, pillarTexture_;

        bool running_ = false;
        bool lose_ = false;

        float birdYPosition = 0.0f;
        float upVelocity = 0.0f;
        int popNum = 0;
        int score = 0;

        float testSpeed = 1.0f;

        glm::vec2 pillarOffset;
        std::vector<float> randomYShift;
};