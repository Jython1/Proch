#include "products.h"
#include "ui_categories.h"

Categories::Categories(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Categories)
{
    ui->setupUi(this);
}

Categories::~Categories()
{
    delete ui;
}
