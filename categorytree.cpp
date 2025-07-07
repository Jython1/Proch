#include "categorytree.h"



CategoryTree::CategoryTree()
{
    treeWidget = new QTreeWidget();
    treeWidget->setColumnCount(1);
    treeWidget->setHeaderLabel("Категории");
    connect(treeWidget, &QTreeWidget::itemDoubleClicked,
            this, &CategoryTree::onItemDoubleClicked);
}
void CategoryTree::AddItem(int categoryId, int connectWithId, QString name)
{

    QTreeWidgetItem* newItem = new QTreeWidgetItem();
    newItem->setText(0, name);
    newItem->setData(0, Qt::UserRole, static_cast<int>(categoryId));
    newItem->setData(0, Qt::UserRole + 1, static_cast<int>(connectWithId));

    if(connectWithId == 0)
    {
        treeWidget->addTopLevelItem(newItem);
    }
     else
    {
        QTreeWidgetItem* parentItem = FindItemById(connectWithId);
        if (parentItem)
            parentItem->addChild(newItem);
        else
            treeWidget->addTopLevelItem(newItem);
    }

}

QTreeWidgetItem* CategoryTree::FindItemById(int id) const
{
    QTreeWidgetItemIterator it(treeWidget);
    while (*it) {
        int itemId = (*it)->data(0, Qt::UserRole).toUInt();
        if (itemId == id)
            return *it;
        ++it;
    }
    return nullptr;
}


QTreeWidget* CategoryTree::GetTreeWidget()
{
    return treeWidget;
}

void CategoryTree::onItemDoubleClicked(QTreeWidgetItem *item, int column)
{

    if (!item)
        return;

    int categoryId = item->data(0, Qt::UserRole).toUInt();
    QString categoryName = item->text(0);

    emit itemDoubleClicked(categoryId, categoryName);

}

void CategoryTree::LoadFromDB(QString filePath)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(filePath);

    if (!db.open())
    {
        qDebug() << "Database connection failed:" << db.lastError().text();
        return;
    }

    QSqlQuery query(db);
    if (!query.exec("SELECT id, parent_id, name FROM categories"))
    {
        qDebug() << "Ошибка запроса:" << query.lastError().text();
        db.close();
        return;
    }

    while (query.next())
    {
        int id = query.value(0).toInt();
        int parentId = query.value(1).toInt();
        QString name = query.value(2).toString();
        AddItem(id, parentId, name);
    }
    db.close();

}

