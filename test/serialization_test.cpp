#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <vector>

#include "mini_rpc/serialization/IByteStream.h"
#include "mini_rpc/serialization/OByteStream.h"
#include "mini_rpc/serialization/SerializableObjectBegin.macro.h"
#include "mini_rpc/serialization/Serializer.h"

using namespace mini_rpc;
OBJECT(Friend)
MEMBERS(std::string name;)
ENDOBJECT(Friend)

OBJECT(BasicInfo)
MEMBERS(std::string ID; int age;)
ENDOBJECT(BasicInfo)

OBJECT(Person)
MEMBERS(std::string name;
        // BasicInfo info;
        // std::vector<Friend> friends;
)
ENDOBJECT(Person)

using SerializeBuffer = mini_rpc::Serializer<mini_rpc::OByteStream>;
using DeserializeBuffer = mini_rpc::Deserializer<mini_rpc::IByteStream>;

class SerializeStringFixture : public testing::TestWithParam<std::string> {};

TEST_P(SerializeStringFixture, SerializeString) {
  std::string str = GetParam();
  OByteStream os;
  SerializeBuffer se_buffer(os);
  se_buffer << str;
  auto is = std::make_shared<IByteStream>(os.bytes());
  DeserializeBuffer de_buffer(*is);
  std::string newStr;
  de_buffer >> newStr;
  EXPECT_STREQ(newStr.c_str(), str.c_str());
  std::cout << newStr << std::endl;
}
INSTANTIATE_TEST_CASE_P(
    SerializeStringCompare, SerializeStringFixture,
    testing::Values(
        std::string(""), std::string("abcd"),
        std::string(
            "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do "
            "eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut "
            "enim ad minim veniam, quis nostrud exercitation ullamco laboris "
            "nisi ut aliquip ex ea commodo consequat."),
        std::string("The quick brown fox jumps over the lazy dog."),
        std::string("A long sentence designed to test the serialization and "
                    "deserialization "
                    "with a fairly substantial amount of text to ensure it can "
                    "handle more "
                    "complex inputs."),
        std::string("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ012345"
                    "6789!@#$%^&*()_+-=~`{}[]:;,.<>?/|\\\"'"),
        std::string("Short string for testing."),
        std::string("Edge case with symbols! @#$%^&*(){}[]|><,./?"),
        std::string(
            "This is a test string that is a bit longer but still under the "
            "256 character limit to test serialization of various lengths."),
        std::string("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ012345"
                    "6789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01"
                    "234567"),  // 255 characters
        std::string(
            "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
            "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
            "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
            "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa")));

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}