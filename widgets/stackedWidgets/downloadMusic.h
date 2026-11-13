#include <QWidget>
#include <QLineEdit>
#include <QJsonObject>
#include <QVBoxLayout>

#include "functions/searcher/search.h"

class songObjectWidget : public QWidget {
  public:
    songObjectWidget(const QJsonObject& songData);
    QJsonObject songData;
};

class downloadMusic : public QWidget {
  public:
    downloadMusic();
    
    QLineEdit *lineEdit;
    Searcher* searcher = nullptr;
    std::list<QJsonObject> songList;
    std::list<songObjectWidget*> scrollableAreaWidgets;
    bool currentlyRunning = false;
    
    QVBoxLayout *scrollableAreaLayout;
};
