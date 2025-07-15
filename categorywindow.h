#ifndef CATEGORYWINDOW_H
#define CATEGORYWINDOW_H

#include <QWidget>
#include <qboxlayout.h>

class CategoryWindow : public QWidget
{
    Q_OBJECT
public:
    explicit CategoryWindow(QWidget *parent = nullptr);

private:
    void CreateDB();
    void SetUI();

    QVBoxLayout *m_scrollLayout;
    QWidget *m_scrollContent;

private slots:
    void addCategory();
    void removeCategory(QWidget *fieldWidget);
    void clearCategories();



};

#endif
