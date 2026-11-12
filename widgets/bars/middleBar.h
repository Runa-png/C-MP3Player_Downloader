#include <QWidget>
#include <QStackedWidget>

class middleBarLeft : public QWidget {
  public:
    middleBarLeft();
};

class middleBarRight : public QWidget {
  public:
    middleBarRight();

    QStackedWidget *stackedWidget;
};

class middleBar : public QWidget {
  public:
    middleBar();

    middleBarLeft *middleBarLeftWidget = nullptr;
    middleBarRight *middleBarRightWidget = nullptr;
};