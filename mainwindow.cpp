#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    LoadStyleSheet("/home/jython/Programming/ProchApp/Themes/DefaultDark.qss");//TODO: ADD GETTING DIR PATH
    CreateMenu();
    setupUI();
    setupLogo();
    createMainTab();
    setFixedSize(400, 600);

}
MainWindow::~MainWindow()
{


}

void MainWindow::LoadStyleSheet(const QString& path) {
    QFile file(path);
    if (file.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(file.readAll());
        qApp->setStyleSheet(styleSheet);
    }
}

void MainWindow::setupUI()
{
    mainWidget = new QWidget(this);
    setCentralWidget(mainWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(mainWidget);
    mainWidget->setLayout(mainLayout);

    // Logo at the top of the main window (outside tabs)
    imageLogo = new QLabel(this);
    mainLayout->addWidget(imageLogo);

    // Add TabSystem
    tabSystem = new TabSystem(this);
    mainLayout->addWidget(tabSystem);

}

void MainWindow::createMainTab()
{
    QWidget *mainTab = new QWidget();
    QVBoxLayout *tabLayout = new QVBoxLayout(mainTab);

    // Search layout
    QHBoxLayout *searchLayout = new QHBoxLayout;
    searchString = new QLineEdit(mainWidget);
    searchButton = new QPushButton("Поиск", mainWidget);
    searchLayout->addWidget(searchString);
    searchLayout->addWidget(searchButton);
    tabLayout->addLayout(searchLayout);

    categoryTree = new CategoryTree();

    tabLayout->addWidget(categoryTree->GetTreeWidget());

    tabSystem->AddTab(mainTab, "Главная");


    connect(searchButton, &QPushButton::clicked, this, &MainWindow::onSearchClicked);
    connect(categoryTree, &CategoryTree::itemDoubleClicked,this, &MainWindow::onCategoryDoubleClicked);

}

void MainWindow::onCategoryDoubleClicked(int categoryId, const QString& categoryName)
{
    QWidget *productsTab = new QWidget();
    tabSystem->AddTab(productsTab, categoryName);
    qDebug() << "Category double-clicked:" << categoryName << "with ID:" << categoryId;
}

void MainWindow::CreateMenu()
{
    menuBar = new QMenuBar(this);
    setMenuBar(menuBar);


    QMenu *fileMenu = menuBar->addMenu("Файл");

    QAction *addProductAction = new QAction("Создать Товар", this);
    QAction *exitAction = new QAction("Выход", this);
    fileMenu->addAction(addProductAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    connect(addProductAction, &QAction::triggered, this, &MainWindow::onCreateProductClicked);
    connect(exitAction, &QAction::triggered, qApp, &QApplication::quit);


    QMenu *categoryMenu = menuBar->addMenu("Категории");

    QAction *editCategoriesAction = new QAction("Редактировать", this);
    QAction *openAction = new QAction("Импортировать...", this);
    categoryMenu->addAction(editCategoriesAction);
    categoryMenu->addAction(openAction);

    connect(editCategoriesAction, &QAction::triggered, this, &MainWindow::onEditCategoriesClicked);
    connect(openAction, &QAction::triggered, this, &MainWindow::onImportCategoriesClicked);

    QMenu *helpMenu = menuBar->addMenu("Справка");
    QAction *aboutAction = new QAction("О программе", this);
    helpMenu->addAction(aboutAction);

    connect(aboutAction, &QAction::triggered, this, []() {
        QMessageBox::about(nullptr, "О программе", "ProchApp\nВерсия 1.0\n(c) 2025");
    });
}


void MainWindow::onSearchClicked()
{
    QString searchText = searchString->text();
    if (!searchText.isEmpty()) {
        QTextEdit *resultsTab = new QTextEdit();
        resultsTab->setText("Результаты поиска для: " + searchText);
        tabSystem->AddTab(resultsTab, "Поиск: " + searchText);
    }
}

void MainWindow::onEditCategoriesClicked()
{
    QTextEdit *categoriesTab = new QTextEdit();
    categoriesTab->setText("Редактор категорий");
    tabSystem->AddTab(categoriesTab, "Редактор категорий");
}

void MainWindow::onImportCategoriesClicked()
{
    QString path = QFileDialog::getOpenFileName(
        this, "Выберите файл категорий",
        QDir::homePath(),
        "Базы данных (*.db);;Все файлы (*)"
        );
    if (!path.isEmpty())
        categoryTree->LoadFromDB(path);

    if (!path.endsWith(".db", Qt::CaseInsensitive))
    {
        QMessageBox::critical(this, "Ошибка", "Выбранный файл не является файлом базы данных (*.db)");
        return;
    }

}

void MainWindow::onCreateProductClicked()
{
    prodWindow = new productsWindow();
    prodWindow->setAttribute(Qt::WA_DeleteOnClose);
    prodWindow->show();



}


void MainWindow::setupLogo()
{
    QString logoPath = QApplication::applicationDirPath() + "/img/ProchLogo.png";
    QPixmap imagePixmap("/home/jython/Programming/Proch/img/ProchLogo.png");

    if (!imagePixmap.isNull()) {
        imageLogo->setPixmap(imagePixmap);
    } else {
        qDebug() << "Не удалось загрузить логотип из:" << logoPath;
        imageLogo->setText("Logo");
    }
}





