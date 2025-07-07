#ifndef TABSYSTEM_H
#define TABSYSTEM_H

#include <QTabWidget>
#include <QWidget>
#include <QMap>
#include <QString>
#include <QList>
#include "qpushbutton.h"
#include "qtabbar.h"


class TabSystem : public QTabWidget
{
public:
    explicit TabSystem(QWidget *parent = nullptr);
    void AddTab(QWidget *page, const QString &title);
    bool IsTabExists(const QString &title);

private:
QHash<QString, QWidget*> tabPages;

private slots:
    void handleTabCloseRequested(int index);

};

#endif // TABSYSTEM_H
