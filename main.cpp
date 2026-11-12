#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>

#include "widgets/centralWidget/centralWidget.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  QMainWindow window;

  window.setCentralWidget(new centralWidget());

  window.show();

  return app.exec();
}
