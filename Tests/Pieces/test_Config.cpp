#include <gtest/gtest.h>
#include "Config.h"


TEST(Config_Suite, Init_Test)
{
    const Config *config = Config::GetInstance();
    ASSERT_NE(config, nullptr);
}

TEST(Config_Suite, Read_Config_Test)
{
    const Config *config = Config::GetInstance();
    ASSERT_EQ(config->GetConfigString("window", "width"), "800");
    
    ASSERT_EQ(true, true);
}
