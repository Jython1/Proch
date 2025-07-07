#ifndef CATEGORYTREE_H
#define CATEGORYTREE_H

#include <QTreeWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>


class CategoryTree : public QObject {
    Q_OBJECT
private:
    QTreeWidget *treeWidget;


public:
    CategoryTree();
    void AddItem(int categoryId, int connectWithId, QString name);
    QTreeWidgetItem* FindItemById(int id) const;
    QTreeWidget* GetTreeWidget();
    void LoadFromDB(QString filePath);

private slots:
    void onItemDoubleClicked(QTreeWidgetItem *item, int column);

signals:
    void itemDoubleClicked(int categoryId, const QString& categoryName);
};

#endif
