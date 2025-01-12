#include <string>
#include <iostream>

#include "mini_rpc/serialization/SerializableObjectBegin.macro.h"
#include <gtest/gtest.h>

OBJECT(person)
    MEMBERS(
        int age = 30;
        std::string name;
        )
ENDOBJECT(person)

TEST(TestPerson, PersonInit){
    person p;
    ASSERT_EQ(31, p.age);
}

int main(int argc, char ** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

