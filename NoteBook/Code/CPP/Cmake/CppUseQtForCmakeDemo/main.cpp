#include <iostream>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLayout>
class MyWindow :public QWidget
{
private:
    QGridLayout layout();
public:
    MyWindow(/* args */);
    ~MyWindow();
};

MyWindow::MyWindow(/* args */)
{
    this->setWindowTitle("Qt Camke Test");
    this->show();
    QWidget::QWidget();
}

MyWindow::~MyWindow()
{
}

int main(int argc, char** argv) {
    QApplication app(argc,argv);
    MyWindow win;
    return app.exec();
}
