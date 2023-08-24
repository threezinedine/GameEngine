#include <queue>
#include "Renderer2DLayer.hpp"


Renderer2DLayer::Renderer2DLayer(std::shared_ptr<ntt::Camera>& camera)
    : Layer("2DRendererLayer"), camera_(camera), pillarOffset(2.0f, 0.0f)
{
    PROFILE_SCOPE();

    storage_ = std::make_shared<ntt::Storage>(
        std::make_shared<ntt::RealFileSystem>("./" + GetName() + "-layer.json"));

    squareColor_ = 
        std::make_unique<ntt::NTTVec3>(
            std::vector<float>{0, 0, 0}, storage_, "squareColor"
        );
    movingSpeed_ = 
        std::make_unique<ntt::ThreadValue<float>>(
            1.0f, 0.0f, 5.0f, storage_, "movingSpeed"
        );

    pillarDistance_ =
        std::make_unique<ntt::ThreadValue<float>>(
            1.0f, 0.0f, 2.0f, storage_, "pillarDistance"
        );

    pillarSize_ =
        std::make_unique<ntt::ThreadArray<float>>(
            std::vector<float>{ 1.0, 1.0 }, 0.0f, 2.0f, storage_, "pillarSize"
        );
    pillarYShift_ =
        std::make_unique<ntt::ThreadValue<float>>(
            0.0f, -2.0f, 2.0f, storage_, "pillarYShift"
        );

    pillarRandomRange_ = 
        std::make_unique<ntt::ThreadValue<float>>(
            0.7, 0.0, 1.0f, storage_, "pillarRandomRange"
        );

    pillarStartX_ = 
        std::make_unique<ntt::ThreadValue<float>>(
            2.0f, 0, 5.0f, storage_, "pillarStartX_"
        );

    pillarOffset.x = pillarStartX_->GetValue();

    birdSize_ =
        std::make_unique<ntt::ThreadArray<float>>(
            std::vector<float>{ 1.0, 1.0 }, 0.0f, 2.0f, storage_, "birdSize"
        );

    birdOffset_ =
        std::make_unique<ntt::ThreadArray<float>>(
            std::vector<float>{ 1.0, 1.0 }, 0.0f, 4.0f, storage_, "birdOffset"
        );

    gravity_ =
        std::make_unique<ntt::ThreadValue<float>>(
            -9.8f, -10.0f, 10.0f, storage_, "gravity"
        );

    pushVelocity_ = 
        std::make_unique<ntt::ThreadValue<float>>(
            5.0f, 0, 20.0f, storage_, "pushVelocity"
        );

    loseOffset_ = 
        std::make_unique<ntt::ThreadValue<float>>(
            0, -2, 2.0f, storage_, "loseOffset"
        );

    birdColisionFactor_ =
        std::make_unique<ntt::ThreadValue<float>>(
            0.9f, 0, 1.5f, storage_, "birdCollisionFactor"
        );

    birdTexture_ = std::make_shared<ntt::Texture2D>(
        // "C:/Users/Acer/OneDrive - Hanoi University of Science and Technology/Pictures/Game/FlappyBird/bird - Copy.png"
        "C:/Users/Acer/OneDrive - Hanoi University of Science and Technology/Pictures/Game/FlappyBird/bird.png"
    );
    backgroundTexture_ = std::make_shared<ntt::Texture2D>(
        "C:/Users/Acer/OneDrive - Hanoi University of Science and Technology/Pictures/Game/FlappyBird/background.jpg"
    );
    pillarTexture_ = std::make_shared<ntt::Texture2D>(
        "C:/Users/Acer/OneDrive - Hanoi University of Science and Technology/Pictures/Game/FlappyBird/pillar.png"
        // "C:/Users/Acer/OneDrive - Hanoi University of Science and Technology/Pictures/Game/FlappyBird/pillar - Copy.png"
    );
}

Renderer2DLayer::~Renderer2DLayer()
{
    PROFILE_SCOPE();

    squareColor_->Save(); 

    movingSpeed_->Save();

    pillarDistance_->Save();
    pillarSize_->Save();
    pillarYShift_->Save();
    pillarRandomRange_->Save();
    pillarSize_->Save();
    pillarStartX_->Save();

    birdSize_->Save();
    birdOffset_->Save();

    gravity_->Save();
    pushVelocity_->Save();
    loseOffset_->Save();
    birdColisionFactor_->Save();

    storage_->Save();
}

static bool IsCollision(const std::vector<float>& pos1, const std::vector<float>& size1,
                        const std::vector<float>& pos2, const std::vector<float>& size2,
                        float collisionFactor = 1.0f)
{
    float halfWidth1 = size1[0] / 2.0f * collisionFactor;
    float halfHeight1 = size1[1] / 2.0f * collisionFactor;

    float halfWidth2 = size2[0] / 2.0f;
    float halfHeight2 = size2[1] / 2.0f;

    float left1 = pos1[0] - halfWidth1 ;
    float right1 = pos1[0] + halfWidth1;
    float top1 = pos1[1] - halfHeight1;
    float bottom1 = pos1[1] + halfHeight1;

    float left2 = pos2[0] - halfWidth2;
    float right2 = pos2[0] + halfWidth2;
    float top2 = pos2[1] - halfHeight2;
    float bottom2 = pos2[1] + halfHeight2;

    if (left1 <= right2 && right1 >= left2 && top1 <= bottom2 && bottom1 >= top2) 
    {
        return true;
    }

    return false;
}

void Renderer2DLayer::OnUpdate(ntt::Timestep ts)
{
    PROFILE_SCOPE();
    static glm::vec2 backgroundOffset = { -1.0f, 0.0f };
    static float posX = 0.0f;
    static float posY = 0.0f;


    ntt::Renderer2D::BeginScence(camera_, ts);

    ntt::Renderer2D::DrawQuad({ 0, 0, 0.1 }, { 15, 1 }, squareColor_->GetGlmVec3());
    ntt::Renderer2D::DrawQuad({ 0, 3, 0.1 }, { 15, 1 }, squareColor_->GetGlmVec3());

    for (int i=0; i<10; i++)
    {
        ntt::Renderer2D::DrawQuad(
            { backgroundOffset.x + i, 1, -0.1 }, 
            { 1, 1 }, 
            backgroundTexture_
        );
        ntt::Renderer2D::DrawRotateQuad(
            { backgroundOffset.x + i, 2, -0.1 }, 
            { 1, 1 }, 
            180, 
            backgroundTexture_
        );
    }

    ntt::Renderer2D::DrawRotateQuad(
        { birdOffset_->GetVector()[0], birdOffset_->GetVector()[1] + birdYPosition, -0.05 },
        { birdSize_->GetVector()[0], birdSize_->GetVector()[1] },
        upVelocity == 0 ? 0 : (upVelocity > 0 ? 20 : -20),
        birdTexture_
    );

    for (int i=0; i<25; i++)
    {
        auto pillarsXPos = pillarOffset.x + i * pillarDistance_->GetValue();

        if (pillarsXPos <= birdOffset_->GetVector()[0])
        {
            score = popNum + i + 1;
        }

        float pillarsYShiftForGame = 0;
        if (i < randomYShift.size())
        {
            pillarsYShiftForGame = randomYShift[i];
        }
        else 
        {
            pillarsYShiftForGame = ntt::NTTRandom::NormRandom(0, 1, -pillarRandomRange_->GetValue(), pillarRandomRange_->GetValue());
            randomYShift.push_back(pillarsYShiftForGame);
        }

        auto bottomYPos = 1 + pillarYShift_->GetValue() - pillarsYShiftForGame;
        auto upperYPos = 2 - pillarYShift_->GetValue() - pillarsYShiftForGame;

        if (IsCollision({ birdOffset_->GetVector()[0], birdOffset_->GetVector()[1] + birdYPosition }, birdSize_->GetVector(),
                { pillarsXPos, bottomYPos }, pillarSize_->GetVector(), birdColisionFactor_->GetValue())
                || 
            IsCollision({ birdOffset_->GetVector()[0], birdOffset_->GetVector()[1] + birdYPosition }, birdSize_->GetVector(),
                { pillarsXPos, upperYPos }, pillarSize_->GetVector(), birdColisionFactor_->GetValue()))
        {
            running_ = false;
            lose_ = true;
        }

        ntt::Renderer2D::DrawQuad(
            { pillarsXPos, bottomYPos }, 
            glm::vec2( pillarSize_->GetVector()[0], pillarSize_->GetVector()[1] ), 
            pillarTexture_
        );
        ntt::Renderer2D::DrawRotateQuad(
            { pillarsXPos, upperYPos }, 
            glm::vec2( pillarSize_->GetVector()[0], pillarSize_->GetVector()[1] ), 
            180, 
            pillarTexture_
        );
    }

    ntt::Renderer2D::End();

    if (running_)
    {
        backgroundOffset.x -= movingSpeed_->GetValue() * ts.GetTime();
        pillarOffset.x -= movingSpeed_->GetValue() * ts.GetTime();

        if (backgroundOffset.x <= -1 - 1)
        {
            backgroundOffset.x = -1;
        }

        if (pillarOffset.x <= -1 - pillarDistance_->GetValue())
        {
            pillarOffset.x = -1;
            randomYShift.erase(randomYShift.begin());
            randomYShift.push_back(ntt::NTTRandom::NormRandom(0, 1, -pillarRandomRange_->GetValue(), pillarRandomRange_->GetValue()));
            popNum++;
        }

        upVelocity += (float)ts * gravity_->GetValue();
        birdYPosition += upVelocity * (float)ts + 1/2 * gravity_->GetValue() * (float)ts * (float)ts;

        if (birdOffset_->GetVector()[1] + birdYPosition <= 0 + loseOffset_->GetValue() || birdOffset_->GetVector()[1] + birdYPosition >= 2.0f + loseOffset_->GetValue())
        {
            running_ = false;
            lose_ = true;
        }
    }
}

void Renderer2DLayer::OnKeyPress(ntt::KeyPressEvent& event) 
{
    if (event.GetKey() == NTT_KEY_SPACE)
    {
        upVelocity = pushVelocity_->GetValue();
    }
    if (event.GetKey() == NTT_KEY_ESCAPE)
    {
        running_ = !running_;
    }
    if (event.GetKey() == NTT_KEY_ENTER)
    {
        if (lose_)
        {
            Reset();
        }
    }
}


void Renderer2DLayer::OnImGuiRenderImpl(ntt::Timestep ts)
{
    PROFILE_SCOPE();

    ImGui::ColorPicker3("Squared Color", squareColor_->GetFirstPointer());
    camera_->OnImGuiRender(ts);

    ImGui::Separator();
    ImGui::Text("Game Parameters");
    ImGui::SliderFloat("Moving Speed", movingSpeed_->GetPointer(), 
                        movingSpeed_->GetMinValue(),
                        movingSpeed_->GetMaxValue());

    ImGui::SliderFloat("Pillar Distance", pillarDistance_->GetPointer(), 
                        pillarDistance_->GetMinValue(),
                        pillarDistance_->GetMaxValue());

    ImGui::SliderFloat("Pillar Y Shift", pillarYShift_->GetPointer(), 
                        pillarYShift_->GetMinValue(),
                        pillarYShift_->GetMaxValue());

    ImGui::SliderFloat("Pillar Random Range", pillarRandomRange_->GetPointer(), 
                        pillarRandomRange_->GetMinValue(),
                        pillarRandomRange_->GetMaxValue());
    
    ImGui::SliderFloat2("Pillar Size", pillarSize_->GetPointer(),
                        pillarSize_->GetMinValue(),
                        pillarSize_->GetMaxValue());

    ImGui::SliderFloat("Pillar Start X", pillarStartX_->GetPointer(),
                        pillarStartX_->GetMinValue(),
                        pillarStartX_->GetMaxValue());

    ImGui::SliderFloat2("Bird Offset", birdOffset_->GetPointer(),
                        birdOffset_->GetMinValue(),
                        birdOffset_->GetMaxValue());

    ImGui::SliderFloat2("Bird Size", birdSize_->GetPointer(),
                        birdSize_->GetMinValue(),
                        birdSize_->GetMaxValue());

    ImGui::SliderFloat("Gravity", gravity_->GetPointer(),
                        gravity_->GetMinValue(),
                        gravity_->GetMaxValue());

    ImGui::SliderFloat("Up Velocity", pushVelocity_->GetPointer(),
                        pushVelocity_->GetMinValue(),
                        pushVelocity_->GetMaxValue());

    ImGui::SliderFloat("Lose Offset", loseOffset_->GetPointer(), 
                        loseOffset_->GetMinValue(),
                        loseOffset_->GetMaxValue());

    ImGui::SliderFloat("Bird Colision Factor", birdColisionFactor_->GetPointer(), 
                        birdColisionFactor_->GetMinValue(),
                        birdColisionFactor_->GetMaxValue());

    ImGui::Separator();

    if (running_)
    {
        if (ImGui::Button("Stop"))
        {
            running_ = false;
        }
    }
    else 
    {
        if (!lose_)
        {
            if (ImGui::Button("Start"))
            {
                running_ = true;
            }
        }
        else 
        {
            if (ImGui::Button("Reset"))
            {
                Reset();
            }
        }
    }

    ImGui::Text("Score:");
    ImGui::SameLine();
    ImGui::Text(std::to_string(score).c_str());
}

void Renderer2DLayer::Reset()
{
    running_ = true;
    lose_ = false;
    score = 0;
    popNum = 0;
    birdYPosition = 0.0f;
    upVelocity = 0.0f;
    pillarOffset.x = pillarStartX_->GetValue();
    randomYShift.clear();
}

void Renderer2DLayer::Lose()
{
    running_ = false;
    lose_ = true;
}
