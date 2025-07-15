#ifndef PRODUCTSWINDOW_H
#define PRODUCTSWINDOW_H

#include <QWidget>
#include <qboxlayout.h>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <qsqlerror.h>



class productsWindow : public QWidget
{
    Q_OBJECT
public:
    explicit productsWindow(QWidget *parent = nullptr);

private:
    void SetUI();
    void LoadFromDB(QString filePath);


    QVBoxLayout *m_scrollLayout;
    QWidget *m_scrollContent;
    QHash<QString, int> categories;

private slots:
    void addField();
    void removeField(QWidget *fieldWidget);
    void clearFields();

signals:
};

#endif
