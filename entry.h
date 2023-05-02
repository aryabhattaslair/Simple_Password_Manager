//
// Created by dpksharma on 12/24/22.
//

#ifndef _ENTRY_H_
#define _ENTRY_H_

#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>

namespace PasswordManager {

  struct SecretEntry {
    unsigned long key;
    std::string name; // What is the entry for
    std::string login; //The login of the date
    std::vector<std::string> passwords; //The password. We store all the passwords
    std::time_t time_of_creation; //when was this entry added
    std::time_t time_of_last_update; //when were things last modified
    std::string custom; //Any additional string you want to use

    template <typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & key;
      ar & name;
      ar & login;
      ar & passwords;
      ar & time_of_creation;
      ar & time_of_last_update;
      ar & custom;
    }
  };

  struct SecretEntryCollection {
    std::map<std::string, SecretEntry> entry_map;

    template <typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & entry_map;
    }
  };


  SecretEntry create_entity(unsigned long key, const std::string &name,
                          const std::string &login, const std::string &pword,
                          const std::string &context);

  SecretEntry update_entry(const SecretEntry &entry, const std::string &parameter_name,
                  const std::string &parameter);

  std::string pretty_read_print(const SecretEntry &entry);

  std::string print_content(const SecretEntry &entry);

}

#endif //_ENTRY_H_
