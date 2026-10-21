#ifndef A8_9_SELECT_GUI_H
#define A8_9_SELECT_GUI_H

#include "../services/services.h"
#include "../repository/repository.h"
#include "gui.h"
#include "user_gui.h"
#include "file_gui.h"
#include <QWidget>
#include <QLabel>
#include <QPushButton>

class StartupGUI : public QWidget {
    Q_OBJECT

private:
    Services& service;
    FileAdoptionList* adoptionList;

    // UI Elements
    QLabel* titleLabel;
    QPushButton* btnAdmin;
    QPushButton* btnUser;

    // Pointers to our other windows
    GUI* adminWindow;
    UserGUI* userWindow;
    FileGUI* FileWindow;

    void setupUI();
    void connectSignalsAndSlots();

private slots:
    void openAdminMode();
    void openUserMode();

public:
    StartupGUI(Services& service, FileAdoptionList* adoptionList, QWidget* parent = nullptr);
    ~StartupGUI() = default;
};
#endif //A8_9_SELECT_GUI_H