#include "categorywindow.h"
#include <qcombobox.h>
#include <qdir.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qscrollarea.h>
#include <qsqldatabase.h>

CategoryWindow::CategoryWindow(QWidget *parent)
    : QWidget{parent}
{
    setFixedSize(500, 700);
    SetUI();

}


void CategoryWindow::CreateDB()
{
    if(QDir("Data").exists())
        return;

    QDir().mkdir("Data");
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("Data/categories.db");

}

void CategoryWindow::SetUI()
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *dbNameLable = new QLabel("Имя базы данных", this);
    QLineEdit *dbName = new QLineEdit(this);

    QPushButton *addCategoryButton = new QPushButton("Добавить", this);
    QPushButton *clearButton = new QPushButton("Очистить", this);
    QPushButton *saveButton = new QPushButton("Сохранить", this);


    QHBoxLayout *buttonsHorizonPlacing = new QHBoxLayout(this);
    buttonsHorizonPlacing->addWidget(addCategoryButton);
    buttonsHorizonPlacing->addWidget(clearButton);
    buttonsHorizonPlacing->addSpacing(30);
    buttonsHorizonPlacing->addWidget(saveButton);

    QLabel *nameLable = new QLabel("Название", this);
    QLabel *idLable = new QLabel("ID");
    QLabel *parentIdLable = new QLabel("Связать с ID");

    QHBoxLayout *titleLables = new QHBoxLayout(this);
    titleLables->addWidget(nameLable);
    titleLables->addWidget(idLable);
    titleLables->addWidget(parentIdLable);

    QScrollArea *scrollArea = new QScrollArea(this);
    QWidget *scrollContent = new QWidget();
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollContent);

    scrollContent->setLayout(scrollLayout);
    m_scrollLayout = scrollLayout;
    m_scrollContent = scrollContent;
    m_scrollLayout->addStretch();


    scrollArea->setWidget(scrollContent);
    scrollArea->setWidgetResizable(true);
    scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


    layout->addWidget(dbNameLable);
    layout->addWidget(dbName);
    layout->addSpacing(10);
    layout->addLayout(buttonsHorizonPlacing);
    layout->addSpacing(10);
    layout->addLayout(titleLables);
    layout->addWidget(scrollArea);

    connect(addCategoryButton, &QPushButton::clicked, this, &CategoryWindow::addCategory);
    connect(clearButton, &QPushButton::clicked, this, &CategoryWindow::clearCategories);

}


void CategoryWindow::addCategory()
{

    QWidget *fieldWidget = new QWidget(m_scrollContent);
    QHBoxLayout *fieldLayout = new QHBoxLayout(fieldWidget);

    QLineEdit *nameEdit = new QLineEdit(fieldWidget);
    QLineEdit *idEdit = new QLineEdit(fieldWidget);
    QLineEdit *parentIdEdit = new QLineEdit(fieldWidget);
    QPushButton *deleteButton = new QPushButton("x", fieldWidget);

    fieldLayout->addWidget(nameEdit);
    fieldLayout->addWidget(idEdit);
    fieldLayout->addWidget(parentIdEdit);
    fieldLayout->addWidget(deleteButton);

    fieldWidget->setLayout(fieldLayout);

    m_scrollLayout->insertWidget(0, fieldWidget);

    connect(deleteButton, &QPushButton::clicked, this, [this, fieldWidget]()
            {
                removeCategory(fieldWidget);
            });

}

void CategoryWindow::removeCategory(QWidget *fieldWidget)
{
    if(!fieldWidget)
        return;

    m_scrollLayout->removeWidget(fieldWidget);
    fieldWidget->deleteLater();

}

void CategoryWindow::clearCategories()
{


}


