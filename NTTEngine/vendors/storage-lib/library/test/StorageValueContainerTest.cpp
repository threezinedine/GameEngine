#include <memory>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Storage.hpp"


class StorageValueContainerTest: public ::testing::Test
{
    protected:
        std::string data = R"(
            {
                "test": 3.141,
                "happy": true
            }
        )";

        std::unique_ptr<ntt::StorageValueContainer> container;

        void SetUp() override
        {
            container = std::make_unique<ntt::StorageValueContainer>(data);
        }
};


TEST_F(StorageValueContainerTest, extractValueFromJsonString)
{
    ASSERT_THAT(container->GetValue<float>("test", 0), ::testing::FloatEq(3.141));
    ASSERT_THAT(container->GetValue<bool>("happy", true), ::testing::IsTrue());
}

TEST_F(StorageValueContainerTest, getResultString)
{
    auto initString = container->GetJsonString();

    ntt::StorageValueContainer testContainer(initString);
    ASSERT_THAT(testContainer.GetValue<float>("test", 0), ::testing::FloatEq(3.141));
}

TEST_F(StorageValueContainerTest, getResultStringAfterChangeValue)
{
    container->SetValue<float>("test", 5.6);

    ntt::StorageValueContainer testContainer(container->GetJsonString());
    ASSERT_THAT(testContainer.GetValue<float>("test", 0), ::testing::FloatEq(5.6));
}

TEST_F(StorageValueContainerTest, getWrongType)
{
    container->SetValue<float>("test", 5.6);

    ntt::StorageValueContainer testContainer(container->GetJsonString());
    ASSERT_THAT(testContainer.GetValue<int>("test", 5), ::testing::Eq(5));
}

TEST_F(StorageValueContainerTest, insertNewValue)
{
    container->SetValue<float>("newTest", 5.6);

    ntt::StorageValueContainer testContainer(container->GetJsonString());
    ASSERT_THAT(testContainer.GetValue<int>("newTest", 5), ::testing::Eq(5));
}