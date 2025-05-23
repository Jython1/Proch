#ifndef CATEGORYTREE_H
#define CATEGORYTREE_H

#include <QTreeWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>

class CategoryTreeItem {
public:
    CategoryTreeItem(QTreeWidgetItem* item, const QString& name, int id, int parentId);

    int id() const;
    int parentId() const;
    QString name() const;
    QTreeWidgetItem* widgetItem() const;

private:
    QTreeWidgetItem* m_item;
    QString m_name;
    int m_id;
    int m_parentId;
};

class CategoryTree : public QObject {
    Q_OBJECT

public:
    CategoryTree();
    ~CategoryTree();

    QTreeWidget* GetTreeWidget() const;

    void LoadFromDatabase(const QString& dbPath);
    void SaveToDatabase(const QString& dbPath);
    void Clear();

private:
    QTreeWidget* m_treeWidget;
    QList<CategoryTreeItem*> m_items;

    void BuildTree();
    void AddItem(const QString& name, int id, int parentId);
    CategoryTreeItem* FindItemById(int id) const;



signals:
    void categoryActivated(int id, const QString& name);

private slots:
    void onItemActivated(QTreeWidgetItem* item, int column);
};

#endif // CATEGORYTREE_H
