#ifndef GUI_H
#define GUI_H

#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QShortcut>
#include "../services/services.h"


class GUI : public QWidget {
    Q_OBJECT
private:
    Services& services;


    QListWidget* petList;
    QLineEdit* breedEdit;
    QLineEdit* nameEdit;
    QLineEdit* ageEdit;
    QLineEdit* photoEdit;
    QPushButton* addButton;
    QPushButton* removeButton;
    QPushButton* updateButton;
    QPushButton* undoButton;
    QPushButton* redoButton;
    QShortcut* undoShortcut;
    QShortcut* redoShortcut;


    void setupUI();
    void connectSignalsAndSlots();
    void populateList();
private slots:
    void addPet();
    void removePet();
    void updatePet();
    void onListSelectionChanged();
    void undo();
    void redo();
public:
    GUI(Services& services, QWidget* parent = nullptr);
    ~GUI() = default;

};

#endif // GUI_H