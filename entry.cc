//
// Created by dpksharma on 12/24/22.
//

#include "entry.h"
#define ENCRYPT_KEY 27

namespace PasswordManager {

namespace {

  std::string encrypt_func(const std::string &input) {
    std::string encrypted;
    for(int n = input.size()-1; n >= 0; n--){
      encrypted.push_back(input[n]);
    }
    return encrypted;
  }

  std::string decrypt_func(const std::string &encrypted) {
    return encrypt_func(encrypted);
  }

}

  SecretEntry create_entity(unsigned long key, const std::string &name,
                          const std::string &login, const std::string &pword,
                          const std::string &context) {
    std::time_t creation_time = std::time(0);
    std::vector<std::string> pword_vector = {encrypt_func(pword)};
    struct SecretEntry entry = {key, name, login, pword_vector,
      creation_time, creation_time,
      context};
    return entry;
  }

  SecretEntry update_entry(const SecretEntry &entry, const std::string &parameter_name,
                  const std::string &parameter) {

    struct SecretEntry new_entry = {entry.key, entry.name, entry.login,
        entry.passwords, entry.time_of_creation,
        entry.time_of_last_update,entry.custom};
    if (parameter_name == "name") {
      new_entry.name = parameter;
      new_entry.time_of_last_update = std::time(0);
    }
    else if (parameter_name == "login") {
      new_entry.login = parameter;
      new_entry.time_of_last_update = std::time(0);
    }
    else if (parameter_name == "password") {
      new_entry.passwords.push_back(encrypt_func(parameter));
      new_entry.time_of_last_update = std::time(0);
    }
    else if (parameter_name == "custom") {
      new_entry.custom = parameter;
      new_entry.time_of_last_update = std::time(0);
    }
    return new_entry;
  }

  std::string pretty_read_print(const SecretEntry &entry) {
    std::string pretty_string = "Name: " + entry.name + "\n";
    pretty_string = pretty_string + "Login: " + entry.login + "\n";
    pretty_string = pretty_string + "Password: " +
        decrypt_func(entry.passwords.back()) + "\n";

    std::tm* now = std::localtime(&(entry.time_of_last_update));
    std::string date_string = std::to_string(now->tm_year+1900) + "-"
      + std::to_string(now->tm_mon+1) + "-" +
      std::to_string(now->tm_mday);

    pretty_string = pretty_string + "Last updated on: " + date_string + "\n";
    return pretty_string;
  }

  std::string print_content(const SecretEntry &entry) {
    return entry.custom;
  }

}
