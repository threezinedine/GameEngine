#include <memory>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Storage.hpp"
#include "StaticFileSystem.hpp"


class StorageTest: public ::testing::Test
{
    protected:
        std::shared_ptr<ntt::Storage> storage_;
        std::shared_ptr<ntt::IFileSystem> file_;

        void SetUp() override
        {
            file_ = std::make_shared<StaticFileSystem>(R"(
                {
                    "test": 3.141,
                    "happy": true
                }
            )");

            storage_ = std::make_unique<ntt::Storage>(file_);
        }
};

TEST_F(StorageTest, getTestValue)
{
    ASSERT_THAT(storage_->GetValue<float>("test", 0), ::testing::FloatEq(3.141));
}

TEST_F(StorageTest, saveTestValue)
{
    storage_->SetValue<float>("test", 12.3);
    storage_->Save();

    ntt::Storage newStorage(file_);
    ASSERT_THAT(newStorage.GetValue<float>("test", 0), ::testing::FloatEq(12.3));
}