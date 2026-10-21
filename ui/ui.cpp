// #include "ui.h"
// #include <iostream>
// #include <limits>
// #include <sstream>
// #include "../Exceptions/exceptions.h"
//
// int getIntegerInput(const std::string &prompt) {
//     int value;
//     std::cout << prompt;
//
//     while (!(std::cin >> value)) {
//         // 1. Clear the error flag
//         std::cin.clear();
//
//         // 2. Remove the "garbage" strings from the buffer
//         // (removes everything until the next newline)
//         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//
//         // 3. Signal the error
//         throw std::invalid_argument("Input was not a valid number!");
//     }
//     return value;
// }
//
//
// UI::UI(Services service, std::string filename) : service(service), filename(filename) {
// }
//
// void UI::print_title() {
//     std::cout << "~~~~~~~~~~Keep calm and adopt a pet~~~~~~~~~~" << '\n' << '\n';
// }
//
// void UI::print_admin_or_user() {
//     std::cout << "Who are you?\n1.Admin\n2.User\n0.Exit\n";
// }
//
// void UI::print_menu_admin() {
//     std::cout << "1.Add a dog. \n2.Remove a dog. \n3.Show all dogs \n4.Update a dog. \n0.Back\n";
// }
//
// void UI::print_menu_add() {
//     std::cout << "Enter the breed: ";
//     std::string breed;
//     std::cin >> breed;
//     std::cout << "Enter the name: ";
//     std::string name;
//     std::cin >> name;
//     int age;
//     while (true) {
//         try {
//             age = getIntegerInput("Enter the age: ");
//             break; // If we reach here, input was successful!
//         } catch (const std::invalid_argument &e) {
//             std::cout << "Error: " << e.what() << " Please try again.\n";
//         }
//     }
//     std::cout << "Enter the photo: ";
//     std::string photo;
//     std::cin >> photo;
//     Pet p = Pet(breed, name, age, photo);
//     try {
//         PetValidator::validate(p);
//
//
//         try {
//             this->service.add_service(breed, name, age, photo);
//             std::cout << "New dog added successfully!\n";
//         } catch (RepositoryException &e) {
//             std::cout << e.what() << "\n";
//         }
//     } catch (ValidationException &e) {
//         std::cout << e.what() << "\n";
//     }
// }
//
// void UI::print_menu_remove() {
//     std::cout << "Enter the name of the dog to remove: ";
//     std::string name;
//     std::cin >> name;
//     std::cout << "Enter the breed of the dog to remove: ";
//     std::string breed;
//     std::cin >> breed;
//     Pet p = Pet(breed, name);
//     try {
//         this->service.remove_service(p);
//         std::cout << "Dog removed successfully!\n";
//     } catch (RepositoryException &e) {
//         std::cout << e.what() << "\n";
//     }
// }
//
// void UI::print_menu_update() {
//     std::cout << "Enter the name of the dog to update: ";
//     std::string name;
//     std::cin >> name;
//     std::cout << "Enter the breed of the dog to update: ";
//     std::string breed;
//     std::cin >> breed;
//     Pet p = Pet(breed, name);
//     std::cout << "What do you want to update?\n1.Breed\n2.Name\n3.Age\n4.Photo\n";
//     std::string choice;
//     std::cin >> choice;
//     if (choice == "1") {
//         std::cout << "Enter the new breed: ";
//         std::string new_breed;
//         std::cin >> new_breed;
//         try {
//             this->service.update_breed_service(p, new_breed);
//             std::cout << "Breed updated successfully\n";
//         } catch (UpdateException &e) {
//             std::cout << e.what() << "\n";
//         }
//     } else if (choice == "2") {
//         std::cout << "Enter the new name: ";
//         std::string new_name;
//         std::cin >> new_name;
//         try {
//             this->service.update_name_service(p, new_name);
//             std::cout << "Name updated successfully!\n";
//         } catch (UpdateException &e) {
//             std::cout << e.what() << "\n";
//         }
//     } else if (choice == "3") {
//         std::cout << "Enter the new age: ";
//         int new_age;
//         std::cin >> new_age;
//         try {
//             this->service.update_age_service(p, new_age);
//             std::cout << "Age updated successfully\n";
//         } catch (UpdateException &e) {
//             std::cout << e.what() << "\n";
//         }
//     } else if (choice == "4") {
//         std::cout << "Enter the new photo: ";
//         std::string new_photo;
//         std::cin >> new_photo;
//         try {
//             this->service.update_photo_service(p, new_photo);
//             std::cout << "Photo updated successfully\n";
//         } catch (UpdateException &e) {
//             std::cout << e.what() << "\n";
//         }
//     } else throw InvalidChoiceException();
// }
//
// void UI::print_menu_show_all() {
//     int size = this->service.get_size();
//     for (int i = 0; i < size; i++) {
//         std::cout << this->service.get_all_dogs().get_elements(i) << '\n';
//     }
// }
//
// void UI::print_menu_user() {
//     /*
// See the dogs in the database, one by one. When the user chooses this option, the data of the first dog (breed, name, age)
// is displayed, along with its photograph.
// Choose to adopt the dog, in which case the dog is added to the user’s adoption list.
// Choose not to adopt the dog and to continue to the next. In this case, the information corresponding to the next dog is shown
// and the user is again offered the possibility to adopt it. This can continue as long as the user wants, as when arriving to the
// end of the list, if the user chooses next, the application will again show the first dog.
// See all the dogs of a given breed, having an age less than a given number. If no breed is provided, then all the dogs wil
// l be considered. The functionalities outlined above apply again in this case.
// See the adoption list.
//      */
//     std::cout <<
//             "1.Show all dogs.\n2.Show dogs by breed and less then a given age(if no breed all the dogs).\n3.See the adoption list\n4.Save to a file\n5.Open the files\n0.Back\n";
// }
//
// void UI::list_dogs(std::vector<Pet> &adoption_list) {
//     while (true) {
//         Pet p = this->service.getNextPet();
//         std::cout << p;
//         //implement the link opener
//         std::string command = "start " + p.get_photo();
//         system(command.c_str());
//         std::cout << "1.Adopt\n2.Next\n0.Exit\n";
//         std::string choice;
//         std::cin >> choice;
//         if (choice == "1") {
//             adoption_list.push_back(p);
//         } else if (choice == "2") {
//             continue;
//         } else break;
//     }
// }
//
// void UI::list_by_breed(std::vector<Pet> &adoption_list) {
//     std::string breed;
//     while (true) {
//         std::cout << "Enter the breed (leave empty to show all dogs): ";
//         std::cin.ignore(1000, '\n');
//         std::getline(std::cin, breed);
//
//         if (breed.empty()) {
//             breed = "";
//             break;
//         } else {
//             break; // We got a valid string, exit the loop
//         }
//     }
//     std::cout << "Enter the minimum age: ";
//     int age;
//     std::cin >> age;
//     std::vector<Pet> list = this->service.get_by_breed_age(breed, age);
//     if (list.empty()) {
//         std::cout << "No dogs found!";
//         return;
//     }
//     int current_index = 0;
//     while (true) {
//         const Pet &p = list[current_index];
//         std::cout << p;
//         std::string command = "start " + p.get_photo();
//         system(command.c_str());
//         std::cout << "1.Adopt\n2.Next\n0.Exit\n";
//         std::string choice;
//         std::cin >> choice;
//         if (choice == "1") {
//             adoption_list.push_back(p);
//             current_index++;
//         } else if (choice == "2") {
//             current_index++;
//         } else break;
//
//         if (current_index == list.size()) {
//             current_index = 0;
//         }
//     }
// }
// void UI::handle_save() {
//     try {
//         // 'my_list' is a FileAdoptionList* // It doesn't matter if it's CSV or HTML, the call is the same!
//         this->my_list->save_to_file();
//     }
//     catch (const FileException& e) {
//         std::cout << "Error: " << e.what() << "\n";
//     }
// }
// void UI::handle_open() {
//     try {
//         this->my_list->open_file();
//     }catch (FileException& e) {
//         std::cout << "Error: " << e.what() << "\n";
//     }
// }
// void UI::print_menu_save_to_file(std::vector<Pet> &adoption_list) {
//     std::cout << "    What file format do you want?\n1.CSV file\n2.HTML file\n0.Cancel\n";
//     std::cout << "Enter your choice: ";
//     int choice;
//     std::cin >> choice;
//     switch (choice) {
//         case 1: {
//             this->my_list = new CSVAdoptionList("adoption_list.csv", adoption_list);
//             handle_save();
//             std::cout<<"Saved to csv file successfully!\n";
//             break;
//         }
//         case 2: {
//             my_list = new HTMLAdoptionList("adoption_list.html", adoption_list);
//             handle_save();
//             std::cout<<"Saved to html file successfully!\n";
//             break;
//         }
//         case 0:
//             break;
//         default: std::cout << "Invalid choice!";
//     }
// }
//
//
// void UI::print_menu_open_file(std::vector<Pet> &adoption_list) {
//     std::cout << "    What file do you want to open?\n1.CSV file\n2.HTML file\n0.Cancel\n";
//     std::cout << "Enter your choice: ";
//     int choice;
//     std::cin >> choice;
//     switch (choice) {
//         case 1: {
//             my_list = new CSVAdoptionList("adoption.csv", adoption_list);
//             handle_open();
//             break;
//         }
//         case 2: {
//             my_list = new HTMLAdoptionList("adoption.html", adoption_list);
//             handle_open();
//             break;
//         }
//         case 0:
//             break;
//         default: std::cout << "Invalid choice!";
//     }
// }
//
// void UI::add_dogs() {
//     this->service.add_service("German Shepherd", "Luna", 3, "https://shorturl.at/4yFg9");
//     this->service.add_service("Bulldog", "Cooper", 5, "https://shorturl.at/8Vig3");
//     this->service.add_service("Labrador Retriever", "Daisy", 6, "https://shorturl.at/OkRHh");
//     this->service.add_service("Golden Retriever", "Olive", 7, "https://shorturl.at/k0TDG");
//     this->service.add_service("French Bulldog", "Echo", 9, "http://tiny.cc/zzt0101");
//     this->service.add_service("Poodle", "Pesto", 2, "http://tiny.cc/a0u0101");
//     this->service.add_service("Beagle", "Rocky", 3,
//                               "https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcTBm3I8tpfRxI83isDtu3tA6Dt-Ldh3fw1HCvz_iUUpcY1FEyvI2wBqoqzrg62ctu7AIg6E4sgLEb3QKnP-uI2uT2-EdVMB8phCq7xUjA&s=10");
//     this->service.add_service("Chihuahua", "Cookie", 5, "https://rb.gy/jbmmtl");
//     this->service.add_service("Chihuahua", "Tommy", 1,
//                               "https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcRItKv36OjM4axai9Ua7WySYTc9MKqKntXg_w&s");
//     this->service.add_service("Unknown", "Spike", 9, "https://news.orvis.com/wp-content/uploads/2019/08/stray.jpg");
//     this->service.add_service("Chihuahua", "Apple", 5, "https://rb.gy/jbmmtl");
//     this->service.add_service("Chihuahua", "Pie", 5, "https://rb.gy/jbmmtl");
// }
//
// void UI::start() {
//     print_title();
//     while (true) {
//         std::string choice;
//         print_admin_or_user();
//         std::cin >> choice;
//         while (choice != "2" && choice != "1" && choice != "0") {
//             std::cout << "Invalid choice!\n";
//             print_admin_or_user();
//             std::cin >> choice;
//             if (choice == "1" || choice == "2" || choice == "0") {
//                 break;
//             }
//         }
//         while (choice == "1") {
//             print_menu_admin();
//             std::string choice2;
//             std::cin >> choice2;
//
//             if (choice2 == "1") {
//                 print_menu_add();
//             } else if (choice2 == "2") {
//                 print_menu_remove();
//             } else if (choice2 == "3") {
//                 print_menu_show_all();
//             } else if (choice2 == "4") {
//                 try {
//                     print_menu_update();
//                 } catch (InvalidChoiceException &e) {
//                     std::cout << e.what() << "\n";
//                 }
//             } else if (choice2 == "0") {
//                 break;
//             } else {
//                 std::cout << "Invalid choice!\n";
//             }
//         }
//
//         std::vector<Pet> adoption_list;
//         while (choice == "2") {
//             print_menu_user();
//             std::string choice2;
//             std::cin >> choice2;
//             if (choice2 == "1") {
//                 //list all dogs
//                 list_dogs(adoption_list);
//             } else if (choice2 == "2") {
//                 //list dogs by breed and less than an age
//                 list_by_breed(adoption_list);
//             } else if (choice2 == "3") {
//                 //show adoption list
//                 for (const auto &i: adoption_list) {
//                     std::cout << i << '\n';
//                 }
//             } else if (choice2 == "4") {
//                 try {
//                     if (adoption_list.empty())
//                         throw ListException("The list is empty!");
//                     UI::print_menu_save_to_file(adoption_list);
//                 }
//                 catch (ListException &e) {
//                     std::cout << e.what() << "\n";
//                 }
//                 catch (RepositoryException &e) {
//                     std::cout << e.what() << '\n';
//                 }
//             }
//             else if (choice2 == "5") {
//                 UI::print_menu_open_file(adoption_list);
//             }
//             else if (choice2 == "0") {
//                 break;
//             } else std::cout << "Invalid choice!\n";
//         }
//         if (choice == "0") {
//             std::cout << "Exiting..." << '\n';
//             break;
//         }
//     }
// }
