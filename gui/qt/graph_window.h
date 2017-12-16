#pragma once

#include <QMainWindow>
#include "graph_widget.h"

class AltWindow : public QWidget
{
  Q_OBJECT
public:
  AltWindow(QWidget *parent = 0);
  ~AltWindow();




  void setup_ui();
  graph_widget *grabbedWidget;
  void closeEvent(QCloseEvent *);
  QWidget *centralwidget;
  QVBoxLayout *verticalLayout;
  QPushButton *backBtn;
  QHBoxLayout *horizontal_layout;
  QGridLayout *centralLayout;
  QGridLayout *mainLayout;
  QHBoxLayout *plotLayout;
  QHBoxLayout *bottomControlLayout;
  QVBoxLayout *plotRangeLayout;
  QVBoxLayout *plotVisibleLayout;
  void retranslate_ui();

signals:
  void pass_widget(graph_widget* widget);

public slots:
  void receive_widget(graph_widget *widget);
};