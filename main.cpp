#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    // Створення екземпляру додатку
    QApplication a(argc, argv);

    // Додавання метаданих (корисно для налаштувань та ідентифікації)
    QApplication::setApplicationName("Image Analyzer");
    QApplication::setOrganizationName("StudentProject");
    QApplication::setApplicationVersion("1.0");

    // Створення та відображення головного вікна
    MainWindow w;
    w.show();

    // Запуск головного циклу подій (Event Loop)
    return a.exec();
}
