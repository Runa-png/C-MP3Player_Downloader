#include "widgets/stackedWidgets/downloadMusic.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollArea>

#include <iostream>

void searchButtonPressed(downloadMusic* parent) {
  std::cout << parent->lineEdit->text().toStdString() << std::endl;
}

downloadMusic::downloadMusic() : QWidget() {
  auto *topLayout = new QVBoxLayout(this);

  auto *mainWidget = new QWidget();
  auto *mainLayout = new QVBoxLayout(mainWidget);
  mainLayout->setContentsMargins(0,0,0,0);

  // User Inputs
  auto *userInputsWidget = new QWidget();
  auto *userInputsLayout = new QHBoxLayout(userInputsWidget);
  userInputsLayout->setContentsMargins(0,0,0,0);

  lineEdit = new QLineEdit();
  lineEdit->setPlaceholderText("CSV Location...");
  auto *searchButton = new QPushButton("Search");
  auto *downloadButton = new QPushButton("Download");

  userInputsLayout->addWidget(lineEdit);
  userInputsLayout->addWidget(searchButton);
  userInputsLayout->addWidget(downloadButton);

  mainLayout->addWidget(userInputsWidget);

  QObject::connect(searchButton, &QPushButton::clicked, [this]() {searchButtonPressed(this);});
  // END User Inputs

  // Scrollable Area
  auto *scrollableArea = new QScrollArea();

  auto *scrollableAreaWidget = new QWidget();
  auto *scrollableAreaLayout = new QVBoxLayout(scrollableAreaWidget);
  scrollableAreaLayout->setContentsMargins(0,0,0,0);

  scrollableArea->setWidgetResizable(true);
  scrollableArea->setWidget(scrollableAreaWidget);

  mainLayout->addWidget(scrollableArea, 1);
  // END Scrollable Area

  topLayout->addWidget(mainWidget);
}
