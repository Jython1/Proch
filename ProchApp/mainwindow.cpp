#include "mainwindow.h"
#include "products.h"
#include <QApplication>
#include <QMessageBox>
#include <QFile>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();
    setupLogo();
    setupConnections();
    setupCategories();
}

MainWindow::~MainWindow()
{
    delete categories;
}

void MainWindow::setupUI()
{

    //Main widgets and tabs
    mainWidget = new QWidget(this);
    tabs = new QTabWidget(mainWidget);
    setCentralWidget(tabs);

    // Main tab
    mainTab = new QWidget(this);
    mainLayout = new QVBoxLayout(mainTab);

    //Logo
    imageLogo = new QLabel(this);
    mainLayout->addWidget(imageLogo);

    //Search
    QHBoxLayout *searchLayout = new QHBoxLayout;
    searchString = new QLineEdit(this);
    searchButton = new QPushButton("Поиск", this);
    searchLayout->addWidget(searchString);
    searchLayout->addWidget(searchButton);
    mainLayout->addLayout(searchLayout);

    //Buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    editCategoriesBtn = new QPushButton("Редактировать категории", this);
    importCategoriesBtn = new QPushButton("Импортировать категории", this);
    buttonLayout->addWidget(editCategoriesBtn);
    buttonLayout->addWidget(importCategoriesBtn);
    mainLayout->addLayout(buttonLayout);

    // Main tab
    mainTab->setLayout(mainLayout);
    tabs->addTab(mainTab, "Главная");
    tabs->setTabsClosable(true);

}

void MainWindow::setupLogo()
{
    QString logoPath = QApplication::applicationDirPath() + "/img/logo.png";
    QPixmap imagePixmap(logoPath);

    if (!imagePixmap.isNull()) {
        imageLogo->setPixmap(imagePixmap);
    } else {
        qDebug() << "Не удалось загрузить логотип из:" << logoPath;
        imageLogo->setText("Logo");
    }
}

void MainWindow::setupConnections()
{
    connect(searchButton, &QPushButton::clicked, this, &MainWindow::performSearch);
    connect(searchString, &QLineEdit::returnPressed, this, &MainWindow::performSearch);
    connect(editCategoriesBtn, &QPushButton::clicked, this, &MainWindow::openCategoriesWindow);
    connect(importCategoriesBtn, &QPushButton::clicked, this, &MainWindow::importCategories);
    connect(tabs, &QTabWidget::tabCloseRequested, this, &MainWindow::closeTab);
}

void MainWindow::setupCategories()
{
    categories = new CategoryTree();

    QString dbPath = QApplication::applicationDirPath() + "/Data/categories.db";
    if (!QFile::exists(dbPath)) {
        dbPath = "/home/jython/Programming/Proch/ProchApp/Data/categories.db";
    }

    if (QFile::exists(dbPath)) {
        categories->LoadFromDatabase(dbPath);
        qDebug() << "Категории загружены из:" << dbPath;
    } else {
        qDebug() << "База категорий не найдена по пути:" << dbPath;
    }

    mainLayout->addWidget(categories->GetTreeWidget());

    connect(categories, &CategoryTree::categoryActivated,
            this, &MainWindow::onCategoryTabRequested);
}

void MainWindow::openCategoriesWindow()
{
    Categories cats(this);
    cats.setModal(true);

    if (cats.exec() == QDialog::Accepted) {
        refreshCategories();
    }
}

void MainWindow::performSearch()
{
    QString searchText = searchString->text().trimmed();

    if (searchText.isEmpty()) {
        QMessageBox::information(this, "Поиск", "Введите текст для поиска");
        return;
    }

    QMessageBox::information(this, "Поиск",
                             QString("Выполняется поиск по запросу: \"%1\"\n(Функция ещё не реализована)").arg(searchText));
}

void MainWindow::importCategories()
{
    QMessageBox::information(this, "Импорт", "Функция импорта категорий пока не реализована.");
}

void MainWindow::refreshCategories()
{
    if (!categories) return;

    QString dbPath = QApplication::applicationDirPath() + "/Data/categories.db";
    if (!QFile::exists(dbPath)) {
        dbPath = "/home/jython/Programming/Proch/ProchApp/Data/categories.db";
    }

    if (QFile::exists(dbPath)) {
        categories->LoadFromDatabase(dbPath);
        qDebug() << "Категории обновлены из:" << dbPath;
    } else {
        qDebug() << "Файл базы данных не найден";
    }
}

void MainWindow::onCategoryTabRequested(int id, const QString &name)
{
    // Проверка — уже есть такая вкладка?
    for (int i = 0; i < tabs->count(); ++i) {
        if (tabs->tabText(i) == name) {
            tabs->setCurrentIndex(i);
            return;
        }
    }

    // === Создаём новую вкладку ===
    QWidget *categoryTab = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(categoryTab);

    // === Заголовок категории ===
    QLabel *label = new QLabel(QString("Категория: %1 (ID: %2)").arg(name).arg(id));
    layout->addWidget(label);

    // === Здесь можно добавить виджеты по содержимому категории ===
    // Например, список товаров:
    QListWidget *productList = new QListWidget(this);
    //TODO: Create database with products
    productList->addItem("Товар 1");
    productList->addItem("Товар 2");
    productList->addItem("Товар 3");

    layout->addWidget(productList);

    // === Добавляем вкладку ===
    categoryTab->setLayout(layout);
    tabs->addTab(categoryTab, name);
    tabs->setCurrentWidget(categoryTab);
}

void MainWindow::closeTab(int index)
{
    // Не позволяем закрыть первую (главную) вкладку
    if (index == 0)
        return;

    QWidget *tab = tabs->widget(index);
    tabs->removeTab(index);
    delete tab;
}

