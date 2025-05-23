#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include "categorytree.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openCategoriesWindow();
    void performSearch();
    void importCategories();
    void refreshCategories();
    void onCategoryTabRequested(int id, const QString &name);
    void closeTab(int index);

private:
    void setupUI();
    void setupLogo();
    void setupConnections();
    void setupCategories();


    // Главное окно
    QWidget *mainWidget = nullptr;
    QTabWidget *tabs = nullptr;

    // Вкладка "Главная"
    QWidget *mainTab = nullptr;
    QVBoxLayout *mainLayout = nullptr;

    // Вкладка "Настройки"
    QWidget *settingsTab = nullptr;

    // Виджеты
    QLabel *imageLogo = nullptr;
    QLineEdit *searchString = nullptr;
    QPushButton *searchButton = nullptr;
    QPushButton *editCategoriesBtn = nullptr;
    QPushButton *importCategoriesBtn = nullptr;

    CategoryTree *categories = nullptr;
};

#endif // MAINWINDOW_H
