#include <string>
#include <QJsonObject>
#include <QObject>

class Searcher : public QObject {
  Q_OBJECT
  
  signals:
    void FINISHED();
    void SONGFOUND(QJsonObject);
  
  public:
    explicit Searcher(QObject* parent = nullptr);  
    
    void searchSongs(const std::string& searchQuery, std::list<QJsonObject>& songList);
};