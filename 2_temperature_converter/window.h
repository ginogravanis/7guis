#pragma once

#include <memory>
#include <QWidget>

class QLabel;
class QLineEdit;

class Window : public QWidget {
   Q_OBJECT

   public:
      explicit Window(QWidget* parent = nullptr);
      ~Window();

   private slots:
      void onCelsiusEdited(const QString&);
      void onFahrenheitEdited(const QString&);

   private:
      float m_temperature_celsius;
      std::unique_ptr<QLabel> m_label_celsius;
      std::unique_ptr<QLabel> m_label_eq;
      std::unique_ptr<QLabel> m_label_fahrenheit;
      std::unique_ptr<QLineEdit> m_field_celsius;
      std::unique_ptr<QLineEdit> m_field_fahrenheit;
};

float toFahrenheit(float celsius);
float toCelsius(float fahrenheit);
