#include <QProcess>
#include <QCoreApplication>
#include <QDir>
#include <QDebug>
#include <QString>
#include <list>
#include <QObject>

#include <iostream>
#include "functions/convertDictToJson.h"
#include "functions/searcher/search.h"

Searcher::Searcher(QObject* parent) : QObject(parent) {}

void Searcher::searchSongs(const std::string& location, std::list<QJsonObject>& songList) {
  QString path = "functions/searcher/";
  QStringList params;
  params << "search.py" << QString::fromStdString(location);

  auto* process = new QProcess();
  process->setWorkingDirectory(path);

  QObject::connect( // Text printed to the terminal
    process, // Link to process object
    &QProcess::readyReadStandardOutput, // Text printed
    process,
    [process, &songList, this]() {
      while (process->canReadLine()) { // Iterate over each song that the python script found
        QJsonObject json = convertDictToJson(process->readLine());
        songList.push_front(json);
        emit SONGFOUND(json);
      }
    }
  );

  QObject::connect( // Error happened
    process,
    &QProcess::readyReadStandardError, // Error occurred
    process,
    [process]() {
      qWarning().noquote() << process->readAllStandardError();
    }
  );

  QObject::connect( // Search completed
    process,
    &QProcess::finished,
    process,
    [process, &songList, this]() {
      process->deleteLater();
      emit FINISHED();
    }
  );

  process->start("python3", params);
}