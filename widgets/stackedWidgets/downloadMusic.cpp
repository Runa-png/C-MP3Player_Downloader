#include "widgets/stackedWidgets/downloadMusic.h"

#include "functions/checkFileExists.h"
#include "colors/colors.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollArea>
#include <QJsonObject>
#include <QLabel>

#include <string>
#include <iostream>
#include <list>

void downloadButtonPressed(downloadMusic* parent) {
  if (parent->currentlyRunning) {return;}

  std::cout << "Download pressed" << std::endl;
}

void searchButtonPressed(downloadMusic* parent) {
  if (!parent->currentlyRunning){
    if (!parent->scrollableAreaWidgets.empty()) {
      for (auto it = parent->scrollableAreaWidgets.begin(); it != parent->scrollableAreaWidgets.end(); ++it) {
        (*it)->hide();
      }
    }
    
    parent->currentlyRunning = true;
    parent->songList.clear(); // Clear song list, prevent duplicate searches
    std::string csvLocation = parent->lineEdit->text().toStdString();
    
    if (!checkFileExists(csvLocation)) {parent->lineEdit->setText("CSV Was not found"); return;}
    
    parent->searcher->searchSongs(csvLocation, parent->songList);
  }
}

void addSongWidget(downloadMusic* parent, QJsonObject songData) {
  if (songData.empty()) {
    return;
  }

  songObjectWidget* songWidget = new songObjectWidget(songData);
  parent->scrollableAreaLayout->addWidget(songWidget);
  parent->scrollableAreaWidgets.push_back(songWidget);
}

songObjectWidget::songObjectWidget(const QJsonObject& songData) : QWidget() {
  this->songData = songData; 
  
  auto *topLayout = new QVBoxLayout(this);
  this->setFixedHeight(150);

  auto *mainWidget = new QWidget();
  mainWidget->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Preferred);
  mainWidget->setStyleSheet(QString::fromStdString(
    std::format(R"(
      background-color: {};
      color: {};
      border-radius:10px;
    )",
      colors::color4,
      colors::text1
    )
  ));
  auto *mainLayout = new QHBoxLayout(mainWidget);

  // Song Details
  auto *songDetailsWidget = new QWidget();
  auto *songDetailsLayout = new QVBoxLayout(songDetailsWidget);
  
  // Song name
  QLabel *songName = new QLabel(songData["Song"].toString());
  songName->setStyleSheet(QString::fromStdString(
    std::format(R"(
      font-size:17px;
      font-weight:700;
      color: {}
    )",
    colors::text1
  )
  ));
  songDetailsLayout->addWidget(songName);

  // Artist Name
  QLabel *artistName = new QLabel(songData["Artist"].toString());
  artistName->setStyleSheet(QString::fromStdString(
    std::format(R"(
      font-size:13px;
      font-weight:700;
      color: {}
    )",
    colors::text2
  )
  ));
  songDetailsLayout->addWidget(artistName);

  // Album Name
  QLabel *albumName = new QLabel(songData["Album"].toString());
  albumName->setStyleSheet(QString::fromStdString(
    std::format(R"(
      font-size:10px;
      font-weight:700;
      color: {}
    )",
    colors::text3
  )
  ));
  songDetailsLayout->addWidget(albumName);

  mainLayout->addWidget(songDetailsWidget);
  topLayout->addWidget(mainWidget);
}

downloadMusic::downloadMusic() : QWidget() {
  std::list<QJsonObject> songList;  
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
  QObject::connect(downloadButton, &QPushButton::clicked, [this]() {downloadButtonPressed(this);});
  // END User Inputs

  // Scrollable Area
  auto *scrollableArea = new QScrollArea();

  auto *scrollableAreaWidget = new QWidget();
  scrollableAreaLayout = new QVBoxLayout(scrollableAreaWidget);
  scrollableAreaLayout->setContentsMargins(0,0,0,0);
  scrollableAreaLayout->setAlignment(Qt::AlignTop);

  scrollableArea->setWidgetResizable(true);
  scrollableArea->setWidget(scrollableAreaWidget);

  mainLayout->addWidget(scrollableArea, 1);
  
  std::list<songObjectWidget*> scrollableAreaWidgets;
  // END Scrollable Area

  topLayout->addWidget(mainWidget);

  // Searchers
  searcher = new Searcher(this);
  QObject::connect(searcher,&Searcher::FINISHED, this, [this]() {currentlyRunning = false; std::cout << "Search Finished" << std::endl;}); // Unlock the 
  QObject::connect(searcher,&Searcher::SONGFOUND, this, [this](QJsonObject jsonObject) {addSongWidget(this, jsonObject);});
}
