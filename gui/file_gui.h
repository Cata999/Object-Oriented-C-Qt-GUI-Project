
#ifndef A8_9_FILE_GUI_H
#define A8_9_FILE_GUI_H
#include <QWidget>
#include <QLabel>
#include <QPushButton>

#include "../repository/repository.h"
class FileGUI : public QWidget {
    Q_OBJECT
private:
    FileAdoptionList* adoptionList;

    QLabel* titleLabel;
    QPushButton* btnCSV;
    QPushButton* btnHTML;
    void setupUI();
    void connectSignalsAndSlots();


private slots:
    void openCSV();
    void openHTML();
    public:
    FileGUI(FileAdoptionList* adoption_list ,QWidget* parent = nullptr);
    ~FileGUI() = default;
};
#endif //A8_9_FILE_GUI_H