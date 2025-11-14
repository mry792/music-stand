#pragma once

#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>


namespace music_stand {
class Application : public QGuiApplication {
  public:
    Application (int argc, char* argv[]);

  private:
    QQmlApplicationEngine engine_;
};
}  // namespace music_stand
