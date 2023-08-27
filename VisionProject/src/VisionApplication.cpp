#include <memory>
#include <VisionApplication.hpp>
#include <ImageDisplay.hpp>
#include <MQTTWindow.hpp>


VisionApplication::VisionApplication()
    : ntt::Application(600, 800, "Vision App"), 
        // webcam_(0), 
        // webcam_(std::string("C:/Users/Acer/C_Language/C++/GameEngine/VisionProject/edge-detect-obj.mp4")),
        webcam_(std::string("C:/Users/Acer/C_Language/C++/GameEngine/VisionProject/data.mp4")),
        // webcam_(std::string("C:/Users/Acer/C_Language/C++/GameEngine/VisionProject/color-detect.mp4")),
        client_("tcp://localhost:1883", "test")
{
    NTT_APPLICATION_DEBUG("Start Initialize Vision application");
    NTT_APPLICATION_DEBUG("Finish Initialize Vision application");
}

VisionApplication::~VisionApplication()
{

}

void VisionApplication::OnSetupImpl()
{
    auto imageProcessingContainer = std::make_shared<ImageProcessingContainer>();
    imageProcessingContainer->AppendStep(std::make_shared<ImageResize>(400));
    imageProcessingContainer->AppendStep(std::make_shared<ConvertImageToRGB>());
    imageProcessingContainer->AppendStep(std::make_shared<FlipImage>());
    imageProcessingContainer->AppendStep(std::make_shared<ExtractByColor>());
    imageProcessingContainer->AppendStep(std::make_shared<ConvertToBinary>());
    imageProcessingContainer->AppendStep(std::make_shared<ExtractByContour>());
    imageProcessingContainer->AppendStep(std::make_shared<QRDetect>());
    imageProcessingContainer->AppendStep(std::make_shared<ExtractCircularObject>());
    imageProcessingContainer->AppendStep(std::make_shared<PnPAlgorithm>());

    webcam_.SetImageProcessingContainer(imageProcessingContainer);

    auto imguiLayer = std::make_shared<ntt::ImGuiLayer>("ImGuiLayer");
    // imguiLayer->AddApplication(new ImageImguiTool());
    imguiLayer->AddApplication(imageProcessingContainer);
    imguiLayer->AddApplication(std::make_shared<ntt::WindowDemoApplication>());
    imguiLayer->AddApplication(std::make_shared<ImageDisplay>());
    // imguiLayer->AddApplication(std::make_shared<MQTTWindow>(), false);
    imguiLayer->AddApplication(std::make_shared<ntt::PerformanceApplication>(1));

    layerStack_.PushOverlayLayer(imguiLayer);
    webcam_.OnRun();
    // client_.Connect();
}

void VisionApplication::OnUpdateImpl(ntt::Timestep ts)
{

}


void VisionApplication::OnWindowCloseImpl(ntt::WindowCloseEvent& event)
{
    webcam_.Stop();
    // client_.Disconnect();
}