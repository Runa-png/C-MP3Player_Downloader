#include "widgets/stackedWidgets/managePlaylists.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

managePlaylists::managePlaylists() : QWidget() {
  auto *topLayout = new QVBoxLayout(this);

  auto *mainWidget = new QWidget();
  auto *mainLayout = new QVBoxLayout(mainWidget);

  mainLayout->addWidget(new QLabel("Managing Playlists!"));
  topLayout->addWidget(mainWidget);
}