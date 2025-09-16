#include "test.h"

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}

TEST(number_1_2, test_1) {
  BinaryFileHandler *binary_file_handler =
      new BinaryFileHandler("answ/out.bin");

  UserInfo user1("qwer", "+7-916-254-76-23", "@qwer");
  UserInfo user2("asdf", "+7-456-632-81-28", "@asdf");

  binary_file_handler->input_to_file(user1);
  binary_file_handler->input_to_file(user2);

  binary_file_handler->output_from_file();

  delete binary_file_handler;
}