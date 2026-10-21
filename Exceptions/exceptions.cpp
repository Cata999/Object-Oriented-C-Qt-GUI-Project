#include "exceptions.h"
void PetValidator::validate(const Pet &p) {
    std::string breed = p.get_breed();
    std::string name = p.get_name();
    int age = p.get_age();
    std::string photo = p.get_photo();

    std::string errors;
    if (!isupper(static_cast<unsigned char>(p.get_name()[0]))) {
        errors += std::string("The name must start with a capital letter!\n");
    }
    if (!isupper(static_cast<unsigned char>(p.get_breed()[0]))) {
        errors += std::string("The breed must start with a capital letter!\n");
    }
    if (age < 0 || age > 50) {
        errors += std::string("The age must be positive and less then 50!\n");
    }
    if (photo.find("http") != 0) {
        errors += std::string("The photo must be a link!\n");
    }

    if (!errors.empty()) {
        throw ValidationException(errors);
    }

}