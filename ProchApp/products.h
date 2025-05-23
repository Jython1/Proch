#ifndef PRODUCTS_H
#define PRODUCTS_H

#include <QDialog>

namespace Ui {
class Categories;
}

class Categories : public QDialog
{
    Q_OBJECT

public:
    explicit Categories(QWidget *parent = nullptr);
    ~Categories();

private:
    Ui::Categories *ui;
};

#endif // PRODUCTS_H
