#pragma once
#include <iostream>
#ifndef A6_7_DOMAIN_H
#define A6_7_DOMAIN_H

class Pet {
private:
    std::string breed{};
    std::string name{};
    int age{};
    std::string photo{};

public:
    Pet();
    Pet(const std::string& breed,const std::string& name);
    Pet(std::string breed,std::string name,int age,std::string photo);

    std::string get_breed() const;

    std::string get_name() const;
    int get_age() const;

    std::string get_photo() const;

    void set_breed(const std::string breed);
    void set_name(std::string name);
    void set_age(int age);
    void set_photo(std::string photo);

    friend std::ostream& operator<<(std::ostream& os, const Pet& pet);

    bool operator==(const Pet& pet) const;
};


#endif //A6_7_DOMAIN_H