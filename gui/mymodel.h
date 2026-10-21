#ifndef A10_MYMODEL_H
#define A10_MYMODEL_H
#include <QAbstractTableModel>
#include "../domain/domain.h"

class MyModel : public QAbstractTableModel{
    Q_OBJECT
private:
    std::vector<Pet> m_pets;
public:
    explicit MyModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void setPets(const std::vector<Pet>& pets);
};
#endif //A10_MYMODEL_H