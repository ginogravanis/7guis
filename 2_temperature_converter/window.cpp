#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include "window.h"

Window::Window(QWidget* parent)
   : QWidget(parent),
     m_temperature_celsius(0),
     m_label_celsius(std::make_unique<QLabel>(tr("Celsius"))),
     m_label_eq(std::make_unique<QLabel>(tr("="))),
     m_label_fahrenheit(std::make_unique<QLabel>(tr("Fahrenheit"))) {
   auto celsius = QString::number(m_temperature_celsius);
   m_field_celsius = std::make_unique<QLineEdit>(celsius);

   auto fahrenheit = QString::number(toFahrenheit(m_temperature_celsius));
   m_field_fahrenheit = std::make_unique<QLineEdit>(fahrenheit);

   QHBoxLayout* layout = new QHBoxLayout;
   layout->addWidget(m_field_celsius.get());
   layout->addWidget(m_label_celsius.get());
   layout->addWidget(m_label_eq.get());
   layout->addWidget(m_field_fahrenheit.get());
   layout->addWidget(m_label_fahrenheit.get());
   setLayout(layout);
   setWindowTitle(tr("TempConv"));

   connect(
      m_field_celsius.get(), &QLineEdit::textEdited,
      this, &Window::onCelsiusEdited
   );
   connect(
      m_field_fahrenheit.get(), &QLineEdit::textEdited,
      this, &Window::onFahrenheitEdited
   );
}

Window::~Window() {
}

void Window::onCelsiusEdited(const QString& text) {
   bool ok;
   float new_celsius = text.toFloat(&ok);
   if (ok) {
      float new_fahrenheit = toFahrenheit(new_celsius);
      m_field_fahrenheit->setText(QString::number(new_fahrenheit));
   }
}


void Window::onFahrenheitEdited(const QString& text) {
   bool ok;
   float new_fahrenheit = text.toFloat(&ok);
   if (ok) {
      float new_celsius = toCelsius(new_fahrenheit);
      m_field_celsius->setText(QString::number(new_celsius));
   }
}

float toFahrenheit(float celsius) {
   return celsius * 9.0 / 5.0 + 32;
}

float toCelsius(float fahrenheit) {
   return (fahrenheit - 32) * 5.0 / 9.0;
}
