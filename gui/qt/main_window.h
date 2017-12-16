#pragma once

#include <array>

#include <QMainWindow>
#include <QList>
#include <QAction>
#include <QMenu>
#include <QContextMenuEvent>
#include <QShowEvent>
#include <QCloseEvent>
#include "qcustomplot.h"
#include "graph_widget.h"
#include "graph_window.h"
#include "jrk.hpp"

class pid_constant_control;
class errors_control;
class main_controller;

struct error_row
{
	unsigned int count;
	QLabel *bit_mask_label = NULL;
	QLabel *error_label = NULL;
	QRadioButton *disabled_radio;
	QRadioButton *enabled_radio;
	QRadioButton *latched_radio;
	QLabel *stopping_value = NULL;
	QLabel *count_value = NULL;
	QWidget *errors_frame;
};

class main_window : public QMainWindow
{
	Q_OBJECT

public:
	main_window(QWidget * parent = 0);
  void set_controller(main_controller * controller);

  // This causes the window to call the controller's update() function
  // periodically, on the same thread as everything else.
  //
  // interval_ms is the amount of time between updates, in milliseconds.
  void set_update_timer_interval(uint32_t interval_ms);
  void start_update_timer();
  void on_update_timer_timeout();

  // Show an OK/Cancel dialog, return true if the user selects OK.
  bool confirm(std::string const & question);

  void show_info_message(std::string const & message);
  void show_error_message(std::string const & message);
 	void set_device_name(std::string const & name, bool link_enabled);
 	void set_serial_number(std::string const & serial_number);
 	void set_firmware_version(std::string const & firmware_version);
 	void set_device_reset(std::string const & device_reset);
 	void reset_error_counts();

  bool suppress_events = false;
  main_controller * window_controller() const;
  main_controller * controller;
	void set_device_list_contents(std::vector<jrk::device> const & device_list);
  void set_device_list_selected(jrk::device const & device);

  // Sets the label that shows the connection status/error.
  void set_connection_status(std::string const & status, bool error);

  void set_manual_target_enabled(bool enabled);

  // Controls whether the apply settings action/button is enabled or
  // disabled.
  void set_apply_settings_enabled(bool enabled);

  void set_vin_calibration(int16_t vin_calibration);

  void set_never_sleep(bool never_sleep);

  void set_accel_max_forward(uint32_t accel_max);
	void set_decel_max_forward(uint32_t decel_max);
	void set_accel_max_reverse(uint32_t accel_max);
	void set_decel_max_reverse(uint32_t decel_max);

	void set_input_scaling_degree(uint8_t input_scaling_degree);

  void set_input_invert(bool input_invert);
	void set_input_min(uint16_t input_min);
  void set_input_neutral_min(uint16_t input_neutral_min);
  void set_input_neutral_max(uint16_t input_neutral_max);
  void set_input_max(uint16_t input_max);
  void set_output_min(int32_t output_min);
  void set_output_max(int32_t output_max);

  void set_serial_baud_rate(uint32_t serial_baud_rate);
  void set_serial_device_number(uint8_t serial_device_number);

	void set_motor_status_message(std::string const & message, bool stopped = true);

	void set_resume_button_enabled(bool enabled);

	void increment_errors_occurred(uint32_t errors_occurred);

	void set_error_status(uint16_t error_status);

	void set_current_velocity(int32_t current_velocity);

	void set_current_position(int32_t current_position);

	void set_target_none();

	void set_target_velocity(int32_t target_velocity);

	void set_vin_voltage(uint32_t vin_voltage);

	void set_up_time(uint32_t up_time);

	// Controls whether the main controls of the application are enabled or
  // disabled.
  void set_tab_pages_enabled(bool enabled);

	// Controls whether the open and save settings file actions are enabled or
  // disabled.
  void set_open_save_settings_enabled(bool enabled);

  // Controls whether the disconnect action is enabled or disabled.
  void set_disconnect_enabled(bool enabled);

  // Controls whether the reload settings from device action is enabled.
  void set_reload_settings_enabled(bool enabled);

  // Controls whether the restore defaults option is enabled.
  void set_restore_defaults_enabled(bool enabled);

signals:
	void pass_widget(graph_widget *widget);

private slots:
	void receive_widget(graph_widget *widget);
	void on_launchGraph_clicked(QMouseEvent*);



protected:
	// void context_menu_event(QContextMenuEvent *event);

  // This is called by Qt just before the window is shown for the first time,
  // and is also called whenever the window becomes unminimized.
  void showEvent(QShowEvent *) override;

  // This is called by Qt when the "close" slot is triggered, meaning that
  // the user wants to close the window.
  void closeEvent(QCloseEvent *) override;


private:
	QFont font;

	std::array<error_row,32> error_rows;

	QTimer *update_timer = NULL;

	QLabel * device_name_label = NULL;
  QLabel * device_name_value = NULL;
  QLabel * serial_number_label = NULL;
  QLabel * serial_number_value = NULL;
  QLabel * firmware_version_label = NULL;
  QLabel * firmware_version_value = NULL;
  QLabel * device_reset_label = NULL;
  QLabel * device_reset_value = NULL;

	QWidget *central_widget;
	QGridLayout *grid_layout;
	QHBoxLayout *horizontal_layout;
	graph_widget *preview_window;
	AltWindow *altw;
	QWidget *preview_plot;
	QMenuBar * menu_bar;
	QMenu * file_menu;
	QAction * open_settings_action;
	QAction * save_settings_action;
	QAction * exit_action;
	QMenu * device_menu;
	QAction * disconnect_action;
	QAction * reload_settings_action;
	QAction * restore_defaults_action;
	QAction * apply_settings_action;
	QAction * upgrade_firmware_action;
	QMenu * help_menu;
	QAction * documentation_action;
	QAction * about_action;

	QHBoxLayout * header_layout;
	QLabel * device_list_label;
	QComboBox * device_list_value;
	QLabel * connection_status_value;
	QCheckBox *stop_motor;

	QTabWidget *tab_widget;
	QWidget *status_page_widget;

	// input tab

	QWidget *input_page_widget;
	QGridLayout *input_page_layout;
	QLabel *input_mode_label;
	QComboBox *input_mode_combobox;

	// input tab "Analog to digital conversion" groupbox

	QGroupBox *input_analog_groupbox;
	QLabel *input_analog_samples_label;
	QCheckBox *input_disconnect_with_aux_checkbox;
	QComboBox *input_analog_samples_combobox;

	// input tab "Scaling (Analog and Pulse Width mode only)" groupbox

	QGroupBox *input_scaling_groupbox;
	QLabel *input_scaling_order_warning_label;
	QLabel *input_absolute_max_label;
	QSpinBox *input_absolute_max_spinbox;
	QLabel *input_maximum_label;
	QSpinBox *input_maximum_spinbox;
	QLabel *input_neutral_max_label;
	QSpinBox *input_neutral_max_spinbox;
	QLabel *input_neutral_min_label;
	QSpinBox *input_neutral_min_spinbox;
	QLabel *input_minimum_label;
	QSpinBox *input_minimum_spinbox;
	QLabel *input_absolute_min_label;
	QSpinBox *input_absolute_min_spinbox;
	QLabel *input_degree_label;
	QComboBox *input_degree_combobox;
	QCheckBox *input_invert_checkbox;
	QPushButton *input_learn_button;
	QPushButton *input_reset_range_button;
	QLabel *input_input_label;
	QLabel *input_target_label;
	QSpinBox *input_output_maximum_spinbox;
	QSpinBox *input_output_neutral_spinbox;
	QSpinBox *input_output_minimum_spinbox;

	// input tab "Serial interface" groupbox

	QGroupBox *input_serial_groupbox;
	QCheckBox *input_never_sleep_checkbox;
	QRadioButton *input_usb_dual_port_radio;
	QRadioButton *input_usb_chained_radio;
	QLabel *input_device_label;
	QSpinBox *input_device_spinbox;
	QSpinBox *input_uart_fixed_baud_spinbox;
	QRadioButton *input_uart_detect_baud_radio;
	QCheckBox *input_enable_crc_checkbox;
	QLabel *input_timeout_label;
	QRadioButton *input_uart_fixed_baud_radio;
	QDoubleSpinBox *input_timeout_spinbox;

	// feedback tab

	QWidget *feedback_page_widget;
	QGridLayout *feedback_page_layout;
	QLabel *feedback_mode_label;
	QComboBox *feedback_mode_combobox;

	// feedback tab "Scaling (Analog and Tachometer mode only)" groupbox

	QGroupBox *feedback_scaling_groupbox;
	QCheckBox *feedback_invert_feedback_checkbox;
	QLabel *feedback_absolute_max_label;
	QLabel *feedback_maximum_label;
	QLabel *feedback_minimum_label;
	QLabel *feedback_absolute_min_label;
	QLabel *feedback_calibration_label;
	QLabel *feedback_scaling_order_warning_label;
	QDoubleSpinBox *feedback_absolute_max_spinbox;
	QDoubleSpinBox *feedback_maximum_spinbox;
	QDoubleSpinBox *feedback_minimum_spinbox;
	QDoubleSpinBox *feedback_absolute_min_spinbox;
	QPushButton *feedback_learn_button;
	QPushButton *feedback_reset_range_button;

	// feedback tab "Analog to digital conversion" groupbox

	QGroupBox *feedback_analog_groupbox;
	QLabel *feedback_analog_samples_label;
	QComboBox *feedback_analog_samples_combobox;
	QCheckBox *feedback_disconnect_with_aux_checkbox;

	// pid tab

	QWidget *pid_page_widget;
	QGridLayout *pid_page_layout;
	QLabel *pid_period_label;
	QDoubleSpinBox *pid_period_spinbox;
	QLabel *pid_integral_limit_label;
	QDoubleSpinBox *pid_integral_limit_spinbox;
	QCheckBox *pid_reset_integral_checkbox;
	QLabel *pid_deadzone_label;
	QDoubleSpinBox *pid_deadzone_spinbox;

	// pid tab constant controls

	pid_constant_control *pid_proportional_coefficient;
	pid_constant_control *pid_integral_coefficient;
	pid_constant_control *pid_derivative_coefficient;

	// motor tab

	QWidget *motor_page_widget;
	QGridLayout *motor_page_layout;
	QLabel *motor_frequency_label;
	QComboBox *motor_frequency_combobox;
	QCheckBox *motor_invert_checkbox;
	QPushButton *motor_detect_motor_button;
	QCheckBox *motor_asymmetric_checkbox;
	QLabel *motor_forward_label;
	QLabel *motor_reverse_label;
	QLabel *motor_duty_label;
	QDoubleSpinBox *motor_duty_forward_spinbox;
	QDoubleSpinBox *motor_duty_reverse_spinbox;
	QLabel *motor_duty_means_label;
	QLabel *motor_acceleration_label;
	QDoubleSpinBox *motor_acceleration_forward_spinbox;
	QDoubleSpinBox *motor_acceleration_reverse_spinbox;
	QLabel *motor_acceleration_means_label;
	QLabel *motor_duration_label;
	QDoubleSpinBox *motor_duration_forward_spinbox;
	QDoubleSpinBox *motor_duration_reverse_spinbox;
	QLabel *motor_current_label;
	QDoubleSpinBox *motor_current_forward_spinbox;
	QDoubleSpinBox *motor_current_reverse_spinbox;
	QLabel *motor_current_means_label;
	QLabel *motor_calibration_label;
	QDoubleSpinBox *motor_calibration_forward_spinbox;
	QDoubleSpinBox *motor_calibration_reverse_spinbox;
	QLabel *motor_outofrange_label;
	QDoubleSpinBox *motor_outofrange_spinbox;
	QLabel *motor_outofrange_means_label;
	QLabel *motor_off_label;
	QRadioButton *motor_brake_radio;
	QRadioButton *motor_coast_radio;

	QWidget *errors_page_widget;
	QGridLayout *errors_page_layout;
	QLabel *errors_bit_mask_label;
	QLabel *errors_error_label;
	QLabel *errors_setting_label;
	QLabel *errors_stopping_motor_label;
	QLabel *errors_occurence_count_label;
	errors_control *awaiting_command;
	errors_control *no_power;
	errors_control *motor_driven_error;
	errors_control *input_invalid;
	errors_control *input_disconnect;
	errors_control *feedback_disconnect;
	errors_control *max_current_exceeded;
	errors_control *serial_signal_error;
	errors_control *serial_overrun;
	errors_control *serial_rx_buffer_full;
	errors_control *serial_crc_error;
	errors_control *serial_protocol_error;
	errors_control *serial_timeout_error;
	QPushButton *errors_clear_errors;
	QPushButton *errors_reset_counts;


	QHBoxLayout *footer_layout;
	QPushButton *motorOffButton;
	QPushButton *motorOnButton;
	QPushButton *apply_settings;


	QAction *sepAct;
	bool widgetAtHome;

	QWidget * setup_status_tab();
  QWidget * setup_input_tab();
	QWidget * setup_feedback_tab();
	QWidget * setup_pid_tab();
	QWidget * setup_motor_tab();
	QWidget * setup_errors_tab();


	void setup_ui();
	void retranslate_ui(QMainWindow *main_window);


	QLabel * up_time_value;
	QLabel * vin_voltage_value;

	// Helper method for setting the index of a combo box, given the desired
  // uint8_t item value. Sets index of -1 for no selection if the specified
  // value is not found.
  void set_u8_combo_box(QComboBox * combo, uint8_t value);
  void set_spin_box(QSpinBox * box, int value);
  void set_double_spin_box(QDoubleSpinBox * spin, double value);
  void set_check_box(QCheckBox * check, bool value);

  void center_at_startup_if_needed();

  bool start_event_reported = false;
};

class pid_constant_control : public QGroupBox
{
	Q_OBJECT
public:
	pid_constant_control(const QString& group_box_title, const QString& object_name, QWidget *parent = 0);
	~pid_constant_control();

private:
	QWidget *central_widget;
	QFrame *pid_control_frame;
	QFrame *pid_proportion_frame;
	QLineEdit *pid_constant_control_textbox;
	QLabel *pid_equal_label;
	QSpinBox *pid_multiplier_spinbox;
	QLabel *pid_base_label;
	QSpinBox *pid_exponent_spinbox;
};

class errors_control : public QWidget
{
	Q_OBJECT
public:
  errors_control(int row_number, const QString& object_name, const QString& bit_mask_text,
      const QString& error_label_text, const bool& disabled_visible,
      const bool& enabled_visible, error_row &er, QWidget *parent = 0);

	QGridLayout *errors_central;
	QWidget *errors_frame;


};