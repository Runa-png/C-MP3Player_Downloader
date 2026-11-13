#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <string>
#include <QByteArray>

#include "functions/convertDictToJson.h"

QJsonObject convertDictToJson(QByteArray dict) {
  QJsonDocument document = QJsonDocument::fromJson(dict);

  if (!document.isObject()) {
    return {};
  }

  QJsonObject songdata = document.object();
  return songdata;
}