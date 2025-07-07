// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include "categorytree.h"
#include <QMenuBar>
#include "tabsystem.h"
#include "productsWindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void CategoryDoubleClicked(int categoryId, const QString &name);

private slots:
    void onSearchClicked();
    void onEditCategoriesClicked();
    void onImportCategoriesClicked();
    void onCategoryDoubleClicked(int categoryId, const QString& categoryName);
    void onCreateProductClicked();

private:
    void setupUI();
    void setupLogo();
    void createMainTab();
    void LoadStyleSheet(const QString& path);
    void CreateMenu();

    QWidget *mainWidget;
    QLabel *imageLogo;
    QLineEdit *searchString;
    QPushButton *searchButton;
    QPushButton *editCategoriesBtn;
    QPushButton *importCategoriesBtn;
    TabSystem *tabSystem;
    CategoryTree *categoryTree;
    QMenuBar *menuBar;
    productsWindow *prodWindow;
};

#endif // MAINWINDOW_H
