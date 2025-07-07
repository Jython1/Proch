#ifndef PRODUCTSWINDOW_H
#define PRODUCTSWINDOW_H

#include <QWidget>



class productsWindow : public QWidget
{
    Q_OBJECT
public:
    explicit productsWindow(QWidget *parent = nullptr);

private:
    void SetUI();
    void addField();


signals:
};

#endif
