#include "productsWindow.h"
#include <QComboBox>
#include <qapplication.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <QScrollArea>
#include <QDebug>
#include <QDir>
#include <qsqlerror.h>
#include <QMessageBox>



productsWindow::productsWindow(QWidget *parent)
    : QWidget{parent}
{
    setFixedSize(600, 700);
    QString path = QCoreApplication::applicationDirPath() + "/Data/categories.db";
    qDebug() << "Путь к БД:" << path;
    LoadFromDB(path);
    SetUI();
}

void productsWindow::SetUI()
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *categoryHint = new QLabel("Категория", this);
    categoryHint->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    QComboBox *categoryList = new QComboBox(this);
    categoryList->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    QHashIterator<QString, int> it(categories);
    while(it.hasNext())
    {
        it.next();
        categoryList->addItem(it.key());
    }
    categoryList->setCurrentIndex(0);

    QPushButton *addFieldButton = new QPushButton("Добавить", this);
    QPushButton *clearButton = new QPushButton("Очистить", this);
    QPushButton *saveButton = new QPushButton("Сохранить", this);


    QHBoxLayout *buttonsHorizonPlacing = new QHBoxLayout(this);
    buttonsHorizonPlacing->addWidget(addFieldButton);
    buttonsHorizonPlacing->addWidget(clearButton);
    buttonsHorizonPlacing->addSpacing(30);
    buttonsHorizonPlacing->addWidget(saveButton);

    QLabel *keyLable = new QLabel("Ключ", this);
    QLabel *valueLable = new QLabel("Значение");

    QHBoxLayout *titleLables = new QHBoxLayout(this);
    titleLables->addWidget(keyLable);
    titleLables->addWidget(valueLable);

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

    layout->addWidget(categoryHint);
    layout->addWidget(categoryList);
    layout->addSpacing(50);
    layout->addLayout(buttonsHorizonPlacing);
    layout->addSpacing(10);
    layout->addLayout(titleLables);
    layout->addWidget(scrollArea);

    connect(addFieldButton, &QPushButton::clicked, this, &productsWindow::addField);
    connect(clearButton, &QPushButton::clicked, this, &productsWindow::clearFields);

}




void productsWindow::addField()
{

    QWidget *fieldWidget = new QWidget(m_scrollContent);
    QHBoxLayout *fieldLayout = new QHBoxLayout(fieldWidget);

    QLineEdit *keyEdit = new QLineEdit(fieldWidget);
    QLineEdit *valueEdit = new QLineEdit(fieldWidget);
    QPushButton *deleteButton = new QPushButton("x", fieldWidget);

    fieldLayout->addWidget(keyEdit);
    fieldLayout->addWidget(valueEdit);
    fieldLayout->addWidget(deleteButton);

    fieldWidget->setLayout(fieldLayout);

    m_scrollLayout->insertWidget(0, fieldWidget);



    connect(deleteButton, &QPushButton::clicked, this, [this, fieldWidget]()
    {
        removeField(fieldWidget);
    });

}


void productsWindow::removeField(QWidget *fieldWidget)
{
    if(!fieldWidget)
        return;

    m_scrollLayout->removeWidget(fieldWidget);
    fieldWidget->deleteLater();

}

void productsWindow::clearFields()
{
    while(QLayoutItem *item = m_scrollLayout->takeAt(0))
    {
        if(QWidget *widget = item->widget())
        {
            widget->deleteLater();
        }
        delete item;
    }
    m_scrollContent->update();
    m_scrollLayout->addStretch();

}

void productsWindow::LoadFromDB(QString filePath)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(filePath);

    if (!db.open())
    {
        qDebug() << "Database connection failed:" << db.lastError().text();
        return;
    }

    QSqlQuery query(db);
    if (!query.exec("SELECT id, parent_id, name FROM categories"))
    {
        qDebug() << "Ошибка запроса:" << query.lastError().text();
        db.close();
        return;
    }

    while (query.next())
    {
        QString name = query.value(2).toString();
        int id = query.value(0).toInt();
        categories.insert(name, id);

    }
    db.close();

}
