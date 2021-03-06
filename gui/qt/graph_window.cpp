#include "graph_window.h"
#include "main_window.h"
#include "graph_widget.h"

graph_window::graph_window()
{
  setup_ui();
}

void graph_window::setup_ui()
{
  setObjectName("graph_window");

  setWindowTitle(tr("Graph - Jrk G2"));

  central_layout = new QGridLayout();

  setLayout(central_layout);
}

void graph_window::closeEvent(QCloseEvent * event)
{
  emit pass_widget();
  QWidget::closeEvent(event);
}

void graph_window::receive_widget(graph_widget * widget)
{
  this->widget = widget;

  widget->set_preview_mode(false);

  widget->controls_layout->setParent(0);

  central_layout->addWidget(widget->custom_plot, 0, 0);
  central_layout->addLayout(widget->controls_layout,
    0, 1, Qt::AlignTop | Qt::AlignRight);

  central_layout->setColumnMinimumWidth(0,
    widget->controls_layout->sizeHint().height());

  central_layout->setColumnStretch(0, 1);
  central_layout->setRowStretch(0, 1);

  central_layout->setMenuBar(widget->setup_menu_bar());
}

// Shows the window and directs focus to it.
//
// We use "showNormal" instead of "show" to fix a Qt bug that happens when the
// window is maximized, closed, and then reopened.  The bug causes the window be
// maximized while only painting controls in its upper left corner.
void graph_window::raise_window()
{
  if (!isVisible() || (windowState() & Qt::WindowMinimized))
  {
    showNormal();
  }

  raise();

  activateWindow();
}
