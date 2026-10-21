#include "select_gui.h"
#include <QVBoxLayout>
#include <QFont>

StartupGUI::StartupGUI(Services& service, FileAdoptionList* adoptionList, QWidget* parent)
    : QWidget(parent), service(service), adoptionList(adoptionList),
      adminWindow(nullptr), userWindow(nullptr) {

    setupUI();
    connectSignalsAndSlots();
}

void StartupGUI::setupUI() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // Title
    titleLabel = new QLabel("Welcome to the Pet Shelter!", this);
    titleLabel->setAlignment(Qt::AlignCenter);

    // Make the title look nice
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(16);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setMinimumHeight(80);

    mainLayout->addWidget(titleLabel);

    // Buttons
    btnAdmin = new QPushButton("Administrator Mode", this);
    btnAdmin->setMinimumHeight(40); // Make the button a bit taller and easier to click

    btnUser = new QPushButton("User Mode", this);
    btnUser->setMinimumHeight(40);

    mainLayout->addWidget(btnAdmin);
    mainLayout->addWidget(btnUser);

    // Window properties
    this->setWindowTitle("Pet Shelter - Launcher");
    this->resize(300, 200);
}

void StartupGUI::connectSignalsAndSlots() {
    connect(btnAdmin, &QPushButton::clicked, this, &StartupGUI::openAdminMode);
    connect(btnUser, &QPushButton::clicked, this, &StartupGUI::openUserMode);
}

void StartupGUI::openAdminMode() {
    // We only create the window if it hasn't been created yet
    if (!adminWindow) {
        adminWindow = new GUI(service);
    }
    adminWindow->show();
    this->hide(); // Hide the startup menu
}

void StartupGUI::openUserMode() {
    // We only create the window if it hasn't been created yet
    if (!userWindow) {
        userWindow = new UserGUI(service, adoptionList);
    }
    userWindow->show();
    this->hide(); // Hide the startup menu
}