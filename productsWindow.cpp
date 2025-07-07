#include "productsWindow.h"
#include <QComboBox>
#include <qboxlayout.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <QScrollArea>


productsWindow::productsWindow(QWidget *parent)
    : QWidget{parent}
{
    setFixedSize(400, 600);
    SetUI();
}

void productsWindow::SetUI()
{

    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *categoryHint = new QLabel("Категория", this);
    categoryHint->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    QComboBox *categoryList = new QComboBox(this);
    categoryList->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    categoryList->addItems({"Пункт 1", "Пункт 2", "Пункт 3"});
    categoryList->setCurrentIndex(0);

    QPushButton *addFieldButton = new QPushButton("Добавить", this);

    QScrollArea *scrollArea = new QScrollArea(this);


    layout->addWidget(categoryHint);
    layout->addWidget(categoryList);
    layout->addSpacing(50);
    layout->addWidget(addFieldButton);
    layout->addWidget(scrollArea);

    layout->addStretch();
    connect(addFieldButton, &QPushButton::clicked, this, &productsWindow::addField);
}

void productsWindow::addField()
{

}
