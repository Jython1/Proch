#include "categorytree.h"

// === CategoryTreeItem ===

CategoryTreeItem::CategoryTreeItem(QTreeWidgetItem* item, const QString& name, int id, int parentId)
    : m_item(item), m_name(name), m_id(id), m_parentId(parentId) {}

int CategoryTreeItem::id() const { return m_id; }
int CategoryTreeItem::parentId() const { return m_parentId; }
QString CategoryTreeItem::name() const { return m_name; }
QTreeWidgetItem* CategoryTreeItem::widgetItem() const { return m_item; }


// === CategoryTree ===

CategoryTree::CategoryTree() {
    m_treeWidget = new QTreeWidget();
    m_treeWidget->setHeaderLabel("Категории");
    m_treeWidget->setMinimumHeight(300);
    connect(m_treeWidget, &QTreeWidget::itemActivated,
            this, &CategoryTree::onItemActivated);
}

CategoryTree::~CategoryTree() {
    delete m_treeWidget;
    qDeleteAll(m_items);
}

QTreeWidget* CategoryTree::GetTreeWidget() const {
    return m_treeWidget;
}

void CategoryTree::Clear() {
    m_treeWidget->clear();
    qDeleteAll(m_items);
    m_items.clear();
}

CategoryTreeItem* CategoryTree::FindItemById(int id) const {
    for (auto* item : m_items) {
        if (item->id() == id)
            return item;
    }
    return nullptr;
}

void CategoryTree::AddItem(const QString& name, int id, int parentId) {
    auto* item = new QTreeWidgetItem();
    item->setText(0, name);
    m_items.append(new CategoryTreeItem(item, name, id, parentId));
}

void CategoryTree::BuildTree() {
    m_treeWidget->clear();

    for (auto* item : m_items) {
        if (item->parentId() == 0) {
            m_treeWidget->addTopLevelItem(item->widgetItem());
        }
    }

    for (auto* item : m_items) {
        if (item->parentId() != 0) {
            CategoryTreeItem* parent = FindItemById(item->parentId());
            if (parent) {
                parent->widgetItem()->addChild(item->widgetItem());
            } else {
                m_treeWidget->addTopLevelItem(item->widgetItem());
            }
        }
    }
}

void CategoryTree::LoadFromDatabase(const QString& dbPath) {
    Clear();

    QSqlDatabase db = QSqlDatabase::contains("CategoryConnection")
                          ? QSqlDatabase::database("CategoryConnection")
                          : QSqlDatabase::addDatabase("QSQLITE", "CategoryConnection");

    db.setDatabaseName(dbPath);

    if (!db.open()) {
        qWarning() << "Could not open database. ERROR:" << db.lastError().text();
        return;
    }

    QSqlQuery query(db);
    if (!query.exec("SELECT id, name, parent_id FROM Categories ORDER BY parent_id ASC")) {
        qWarning() << "SQL request error: " << query.lastError().text();
        db.close();
        return;
    }

    while (query.next()) {
        int id = query.value("id").toInt();
        QString name = query.value("name").toString();
        int parentId = query.value("parent_id").toInt();
        AddItem(name, id, parentId);
    }

    BuildTree();
    db.close();
}

void CategoryTree::SaveToDatabase(const QString& dbPath) {
    QSqlDatabase db = QSqlDatabase::contains("CategoryConnection")
                          ? QSqlDatabase::database("CategoryConnection")
                          : QSqlDatabase::addDatabase("QSQLITE", "CategoryConnection");

    db.setDatabaseName(dbPath);

    if (!db.open()) {
        qWarning() << "Ошибка открытия базы:" << db.lastError().text();
        return;
    }

    QSqlQuery query(db);
    db.transaction();

    if (!query.exec("DELETE FROM Categories")) {
        qWarning() << "Ошибка очистки таблицы Categories:" << query.lastError().text();
        db.rollback();
        db.close();
        return;
    }

    for (auto* item : m_items) {
        query.prepare("INSERT INTO Categories (id, name, parent_id) VALUES (?, ?, ?)");
        query.addBindValue(item->id());
        query.addBindValue(item->name());
        query.addBindValue(item->parentId());

        if (!query.exec()) {
            qWarning() << "Ошибка вставки:" << query.lastError().text();
            db.rollback();
            db.close();
            return;
        }
    }

    db.commit();
    db.close();
    qDebug() << "Категории успешно сохранены.";
}

void CategoryTree::onItemActivated(QTreeWidgetItem* item, int column) {
    Q_UNUSED(column);
    qDebug() << "ItemActivated";
    for (CategoryTreeItem* cti : m_items) {
        if (cti->widgetItem() == item) {
            emit categoryActivated(cti->id(), cti->name());
            return;
        }
    }
}
