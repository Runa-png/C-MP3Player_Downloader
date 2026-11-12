#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QHBoxLayout>
#include <QStackedWidget>

#include "widgets/bars/middleBar.h"
#include "colors/colors.h"

middleBarLeft::middleBarLeft() : QWidget() {
  auto *topLayout = new QVBoxLayout(this);
  topLayout->setContentsMargins(0,0,0,0);

  auto *mainWidget = new QWidget();
  mainWidget->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Preferred);
  mainWidget->setMinimumWidth(100);
  mainWidget->setStyleSheet(
    QString::fromStdString(
      std::format(R"(
        background-color: {};
      )",
      colors::color2
    )
    )
  );

  auto *mainLayout = new QVBoxLayout(mainWidget);
  mainLayout->setContentsMargins(0,0,0,0);

  topLayout->addWidget(mainWidget);
}

middleBarRight::middleBarRight() : QWidget() {
  auto *topLayout = new QVBoxLayout(this);
  topLayout->setContentsMargins(0,0,0,0);

  auto *mainWidget = new QWidget();
  mainWidget->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Preferred);
  mainWidget->setStyleSheet(
    QString::fromStdString(
      std::format(R"(
        background-color: {};
      )",
      colors::color3
    )
    )
  );

  
  auto *mainLayout = new QVBoxLayout(mainWidget);
  mainLayout->setContentsMargins(0,0,0,0);
  
  stackedWidget = new QStackedWidget();
  mainLayout->addWidget(stackedWidget);
  
  topLayout->addWidget(mainWidget);
}

middleBar::middleBar() : QWidget() {
  auto *topLayout = new QVBoxLayout(this);
  topLayout->setContentsMargins(0,0,0,0);

  auto *mainWidget = new QWidget();
  auto *mainLayout = new QHBoxLayout(mainWidget);
  mainLayout->setContentsMargins(0,0,0,0);
  mainLayout->setSpacing(0);

  middleBarLeftWidget = new middleBarLeft();
  mainLayout->addWidget(middleBarLeftWidget, 5);
  
  middleBarRightWidget = new middleBarRight();
  mainLayout->addWidget(middleBarRightWidget, 95);

  topLayout->addWidget(mainWidget);
}