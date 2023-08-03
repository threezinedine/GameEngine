#pragma once


namespace ntt
{
    class Application
    {
        public:
            Application();
            virtual ~Application();

            virtual void Setup();
            virtual void Run();
    }; 
} // namespace ntt
