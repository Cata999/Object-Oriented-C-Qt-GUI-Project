#include <QApplication>
#include <QMessageBox>
#include <vector>
#include "repository/repository.h"
#include "services/services.h"
#include "gui/select_gui.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    try {
    // Initialize the repository
    Repository<Pet> repo("pets.txt");

    // Initialize the service
    Services service(repo);

    // Initialize the adoption list
    std::vector<Pet> Pets;

    CSVAdoptionList adoptionList("adoption_list.csv",Pets);
    StartupGUI launcher(service, &adoptionList);
    launcher.show();

    return app.exec(); // Starts the Qt event loop
    } catch (const std::exception& e) {
        // If ANYTHING throws an error during startup, catch it and show a popup!
        QMessageBox::critical(nullptr, "Fatal Startup Error",
            QString("The application failed to start. Error:\n\n") + e.what() +
            "\n\nPlease ensure your 'pets.txt' and 'adoption_list.csv' files are in the correct build directory.");

        return -1;
    }
}
