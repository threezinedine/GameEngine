#include "Storage.hpp"

class StaticFileSystem: public ntt::IFileSystem
{
    public:
        StaticFileSystem(std::string data);

        std::string Read() override { return data_; }
        void Save(std::string data) { data_ = data; }

    private:
        std::string data_;
};