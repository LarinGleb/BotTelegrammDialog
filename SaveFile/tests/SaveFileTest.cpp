#include <gtest/gtest.h>

#include "../SaveFile.h"

class TestSave : public ::testing::Test {
public:
    TestSave() {}
    ~TestSave() {}
    void SetUp() {

    }
    void TearDown() { }
};

TEST_F(TestSave, TestAddProperties) {
    

    // std::cout << "\n --- Test AddProperties --- " << "\n";

    SaveFile Save;

    ASSERT_FALSE(Save.AddProperty(";;;1231313"));
    ASSERT_TRUE(Save.AddProperty("1231313"));
    ASSERT_TRUE(Save.AddProperty("weferwe1231313"));
    ASSERT_TRUE(Save.AddProperty("DDDDDDDDDDDDqwwqwqw1231313"));
    ASSERT_FALSE(Save.AddProperty("..__1231313"));

    std::cout << "\n";
}

TEST_F(TestSave, TestSetPropertiesErrorName) {
    
    // std::cout << "\n --- Test SetProperties --- " << "\n";
    SaveFile Save;

    Save.AddProperty("1231313");
    ASSERT_FALSE(Save.SetProperty(";;;1231313", "1321322"));
    ASSERT_TRUE(Save.SetProperty("1231313", "1321322"));
    ASSERT_FALSE(Save.SetProperty(";1233132332;;1231313", "1321322"));

    std::cout << "\n";
}

TEST_F(TestSave, TestReadMakePropertiesError) {
    
    SaveFile Save;

    // std::cout << "\n --- Test Read and Save Properties --- " << "\n";

    Save.AddProperty("1231313");
    Save.SetProperty("1231313", "111");
    std::string old_Property = Save.ReadProperty("1231313");

    ASSERT_TRUE(Save.MakeSave("test.txt"));

    ASSERT_TRUE(Save.ReadSave("test.txt"));
    ASSERT_FALSE(Save.ReadSave("uncorrecttest.txt"));


    std::string new_Property = Save.ReadProperty("1231313");

    ASSERT_EQ(old_Property, new_Property);

    std::cout << "\n";
}



int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}