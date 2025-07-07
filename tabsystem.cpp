#include "tabsystem.h"



TabSystem::TabSystem(QWidget *parent): QTabWidget(parent)
{
    setTabsClosable(true);
    connect(this, &QTabWidget::tabCloseRequested,
            this, &TabSystem::tabCloseRequested);
}

void TabSystem::AddTab(QWidget *page, const QString &title)
{
    if(tabPages.contains(title))
        return;

    int index = addTab(page, title);
    tabPages.insert(title, page);


    QPushButton *closeButton = new QPushButton("×");
    closeButton->setMaximumSize(16, 16);

    connect(closeButton, &QPushButton::clicked, [this, page]() {
        int currentIndex = indexOf(page);

        if (currentIndex != -1) {
            handleTabCloseRequested(currentIndex);
        }

    });

    tabBar()->setTabButton(index, QTabBar::RightSide, closeButton);

    setCurrentWidget(page);
}

void TabSystem::handleTabCloseRequested(int index)
{
    if (index <= 0 || index >= count())
        return;

    QString title = tabText(index);
    QWidget *page = widget(index);

    tabPages.remove(title);
    removeTab(index);

    if (page) {
        page->deleteLater();
    }
}

bool TabSystem::IsTabExists(const QString &title)
{
    return tabPages.contains(title);
}
