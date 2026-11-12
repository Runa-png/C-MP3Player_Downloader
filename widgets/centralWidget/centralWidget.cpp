#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

#include "widgets/centralWidget/centralWidget.h"
#include "widgets/bars/middleBar.h"
#include "widgets/bars/topBar.h"
#include "widgets/bars/bottomBar.h"

// Stacked Widgets
#include "widgets/stackedWidgets/downloadMusic.h"
#include "widgets/stackedWidgets/managePlaylists.h"

centralWidget::centralWidget() : QWidget() {
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    auto *topWidget = new QWidget(this);
    auto *topLayout = new QVBoxLayout(topWidget);
    topLayout->setSpacing(0);
    topLayout->setContentsMargins(0, 0, 0, 0);

    auto topBarWidget = new topBar();
    topLayout->addWidget(topBarWidget, 4);

    // Middle Section
    auto middleBarWidget = new middleBar();
    topLayout->addWidget(middleBarWidget, 86);
    middleBarWidget->middleBarRightWidget->stackedWidget->addWidget(new downloadMusic());
    middleBarWidget->middleBarRightWidget->stackedWidget->addWidget(new managePlaylists());
    middleBarWidget->middleBarRightWidget->stackedWidget->setCurrentIndex(0);

    auto bottomBarWidget = new bottomBar();
    topLayout->addWidget(bottomBarWidget, 10);

    mainLayout->addWidget(topWidget, 1);
}