#pragma once

#include "qcustomplot.h"

#include <QCheckBox>
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QString>
#include <QWidget>

class dynamic_decimal_spin_box;
class big_hit_check_box;

class graph_widget : public QObject
{
  Q_OBJECT

public:

  graph_widget();

  // The maximum time span that can be displayed, in milliseconds.
  const int max_domain_ms = 90000;

  struct plot
  {
    int index = 0;
    QString id_string;
    QDoubleSpinBox * position;
    dynamic_decimal_spin_box * scale;
    big_hit_check_box * display;
    double default_scale;
    QString default_color;
    QString dark_color;
    QString original_default_color;
    QString original_dark_color;
    QCPAxis * axis;
    QCPGraph * graph;
    double plot_value = 0;
    QCPItemText * axis_label;
    QCPItemText * axis_position_label;
    QCPItemText * axis_scale_label;
    QList<QCPItemText *> overflow_arrows;
  };

  QList<plot *> all_plots;

  plot input;
  plot target;
  plot feedback;
  plot scaled_feedback;
  plot error;
  plot integral;
  plot duty_cycle_target;
  plot duty_cycle;
  plot raw_current;
  plot current;
  plot current_chopping;

  QCustomPlot * custom_plot;
  QGridLayout * controls_layout;

  bool preview_mode = true;

  QMenu * setup_options_menu(const QString &, bool shortcuts = false);
  QMenuBar * setup_menu_bar();

  void set_preview_mode(bool preview_mode);
  void set_paused(bool paused);
  void clear_graphs();
  void plot_data(uint32_t time);

  void set_checkbox_style(plot *, const QString &);
  void change_plot_colors(plot *, const QString &);

protected:
  bool eventFilter(QObject * o, QEvent * e);

private:
  void show_plot_menu(plot *, bool with_title);
  void pick_plot_color(plot *);
  void setup_ui();

  QMenuBar * menu_bar = NULL;
  QAction * dark_theme_action;
  QAction * default_theme_action;

  // Used to add new plot
  void setup_plot(plot &,
    const QString & id_string, const QString & display_text,
    const QString & default_color, const QString & dark_color,
    int typical_max_value, bool default_visible = false);

  QCPItemText * axis_arrow(const plot &, double degrees);
  QPushButton * pause_run_button;
  QSpinBox * domain;
  QPushButton * show_all_none;

  void update_x_axis();
  void remove_old_data();
  void set_graph_interaction_axis(const plot &);
  void reset_graph_interaction_axes();
  void update_plot_text_and_arrows(const plot &);
  void update_plot_overflow_arrows(const plot &);
  void update_position_step_value(const plot &);
  void reset_plot_range(const plot &);
  void set_range(const plot &);
  void set_plot_grid_colors(int value);

  QFont y_label_font;
  QFont x_label_font;

  // time value corresponding to the right edge of the graph
  uint32_t display_time;

  // time value corresponding to the latest data from the device.
  // Should equal display_time if we are not paused.
  uint32_t current_time;

  int row = 1;
  bool graph_paused = false;
  bool dark_theme = false;

public slots:
  void save_settings();
  void load_settings();

private slots:
  void switch_to_dark();
  void switch_to_default();
  void change_ranges(int value);
  void pause_or_run();
  void set_line_visible();
  void show_all_none_clicked();
  void reset_all_colors();
  void reset_all_ranges();
  void mouse_press(QMouseEvent *);
};

// This subclass of QDoubleSpinBox is used to add more control to both the
// value displayed in the QDoubleSpinBox and the steps caused by "arrow up",
// "arrow down", "page up", and "page down" keys.
class dynamic_decimal_spin_box : public QDoubleSpinBox
{
  Q_OBJECT

public:
  explicit dynamic_decimal_spin_box(QWidget * parent = 0) :
    QDoubleSpinBox(parent) {}

protected:
  virtual void stepBy(int steps);
  static int step_up(int);
  static int step_down(int);
  QString textFromValue(double value) const;
  double valueFromText(const QString & text) const;
};

// A checkbox where you can click anywhere within its area to activate it.
// Appropriate for checkboxes that you want to have a border.
class big_hit_check_box : public QCheckBox
{
  bool hitButton(const QPoint & pos) const override
  {
    Q_UNUSED(pos);
    return true;
  }
};
