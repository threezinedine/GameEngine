#include <iostream>

#include "Storage.hpp"


int main()
{
    std::string key = "new";
    auto file = std::make_shared<ntt::RealFileSystem>("./data-test.json");   

    auto storage = ntt::Storage(file);
    std::cout << storage.GetValue<float>(key, 0) << std::endl;
    storage.SetValue<float>(key, storage.GetValue<float>(key, 0) + 1);

    storage.Save();
    
    return 0;
}