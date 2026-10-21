/*
*The “Keep calm and adopt a pet” shelter needs a software application to help them find adoptive parents for the dogs
*they are taking care of. The application can be used in two modes: administrator and user. When the application is
*started, it will offer the option to select the mode.
Administrator mode: The application will have a database that holds all the dogs in the shelter at a given moment.
The shelter employees must be able to update the database, meaning: add a new dog, delete a dog (when the dog is adopted)
and update the information of a dog. Each Dog has a breed, a name, an age and a photograph. The photograph is memorised
as a link towards an online resource (the photograph on the presentation site of the centre). The administrators will also
have the option to see all the dogs in the shelter.
User mode: A user can access the application and choose one or more dogs to adopt. The application will allow the user to:

See the dogs in the database, one by one. When the user chooses this option, the data of the first dog (breed, name, age)
is displayed, along with its photograph.
Choose to adopt the dog, in which case the dog is added to the user’s adoption list.
Choose not to adopt the dog and to continue to the next. In this case, the information corresponding to the next dog
is shown and the user is again offered the possibility to adopt it. This can continue as long as the user wants, as
when arriving to the end of the list, if the user chooses next, the application will again show the first dog.
See all the dogs of a given breed, having an age less than a given number. If no breed is provided, then all the dogs
will be considered. The functionalities outlined above apply again in this case.
See the adoption list.
 */

#include "domain.h"
#include <cstring>

#include <iostream>
// Notice the colon : and the list of variables before the {
Pet :: Pet () = default;
Pet :: Pet(const std::string& breed, const std::string& name) {
    this->breed = breed;
    this->name = name;
    this->age = 0;
    this->photo = "";
}
Pet :: Pet(std::string breed, std::string name, int age, std::string photo) {
    /*
     *Constructor with parameters
     */
    this->breed = breed;
    this->name =name;
    this->age = age;
    this->photo = photo;
}


std::ostream& operator<<(std::ostream& os, const Pet& pet) {
    /*
     *Overwrite of the "<<" operator, to print the pets nicely
     */
    // If it's an empty pet, print a placeholder
    if (pet.get_name().empty()) {
        os << "[Empty Pet]\n";
    } else {
        // Build the output format you want
        os << "Name: " << pet.name
           << " | Breed: " << pet.breed
           << " | Age: " << pet.age
           << " | Photo: " << pet.photo <<'\n';
    }

    return os;
}

//Getters
std::string Pet::get_breed() const{
    return this->breed;
}

std::string Pet::get_name() const{
    return this->name;
}
int Pet::get_age() const {
    return this->age;
}

std::string Pet::get_photo() const{
    return this->photo;
}
void Pet::set_breed(const std::string breed) {
    this->breed = breed;
}
void Pet::set_name(const std::string name) {
    this->name = name;
}
void Pet::set_age(const int age) {
    this->age = age;
}
void Pet::set_photo(const std::string photo) {
    this->photo = photo;
}
bool Pet::operator==(const Pet &pet) const {
    return this->breed == pet.breed && this->name == pet.name;
}
