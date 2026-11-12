#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

#include "widgets/bars/topBar.h"
#include "colors/colors.h"

topBar::topBar() : QWidget() {
  auto *topLayout = new QVBoxLayout(this);
  topLayout->setContentsMargins(0,0,0,0);

  auto *mainWidget = new QWidget();
  mainWidget->setStyleSheet(
    QString::fromStdString(
      std::format(R"(
        background-color: {};
      )",
      colors::color1
    )
    )
  );

  auto *mainLayout = new QVBoxLayout(mainWidget);
  mainLayout->setContentsMargins(0,0,0,0);

  mainLayout->addWidget(new QLabel("Hello From Top Bar"));

  topLayout->addWidget(mainWidget);
}