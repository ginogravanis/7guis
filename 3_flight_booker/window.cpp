#include <QComboBox>
#include <QDate>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QStringList>
#include <QVBoxLayout>
#include "window.h"

const QString Window::dateFormat = "dd.MM.yyyy";
const QString Window::errorStyle = "background-color:#FF6961;";

Window::Window(QWidget* parent)
   : QWidget(parent),
     m_flight_types(std::unique_ptr<QStringList>(
         new QStringList{tr("one-way flight"), tr("return flight")}
     )),
     m_field_flight_type(std::make_unique<QComboBox>()),
     m_button_submit(std::make_unique<QPushButton>(tr("Book")))
{
   auto today = QDate::currentDate().toString(Window::dateFormat);
   m_field_flight_date = std::make_unique<QLineEdit>(today);
   m_field_return_date = std::make_unique<QLineEdit>(today);

   m_field_flight_type->addItems(*m_flight_types);

   QVBoxLayout* layout = new QVBoxLayout;
   layout->addWidget(m_field_flight_type.get());
   layout->addWidget(m_field_flight_date.get());
   layout->addWidget(m_field_return_date.get());
   layout->addWidget(m_button_submit.get());
   setLayout(layout);

   connect(
      m_field_flight_type.get(), &QComboBox::currentIndexChanged,
      this, &Window::flightTypeSelected
   );
   connect(
      m_field_flight_date.get(), &QLineEdit::textEdited,
      this, &Window::flightDateChanged
   );
   connect(
      m_field_return_date.get(), &QLineEdit::textEdited,
      this, &Window::returnDateChanged
   );
   connect(
      m_button_submit.get(), &QPushButton::released,
      this, &Window::submitReleased
   );

   applyConstraints();
}

Window::~Window() {
}

void Window::applyConstraints() {
   if (isFlightTypeReturnFlight()) {
      applyConstraintsForReturnFlight();
   } else {
      applyConstraintsForOneWay();
   }
}

void Window::applyConstraintsForOneWay() {
   m_field_return_date->setEnabled(false);

   bool flight_valid = true;
   if (!containsValidDate(m_field_flight_date.get()))
      flight_valid = false;
   m_button_submit->setEnabled(flight_valid);
}

void Window::applyConstraintsForReturnFlight() {
   m_field_return_date->setEnabled(true);

   bool flight_valid = true;
   bool flight_date_valid = containsValidDate(m_field_flight_date.get());
   bool return_date_valid = containsValidDate(m_field_return_date.get());
   if (flight_date_valid && return_date_valid) {
      auto flight_date = QDate::fromString(
         m_field_flight_date->text(),
         Window::dateFormat
      );
      auto return_date = QDate::fromString(
         m_field_return_date->text(),
         Window::dateFormat
      );
      if (flight_date > return_date) {
         flight_valid = false;
      }
   } else {
      flight_valid = false;
   }
   m_button_submit->setEnabled(flight_valid);
}

bool Window::containsValidDate(QLineEdit* field) {
   QDate flight_date = QDate::fromString(
      field->text(),
      Window::dateFormat
   );
   if (flight_date.isValid()) {
      field->setStyleSheet("");
      return true;
   } else {
      field->setStyleSheet(Window::errorStyle);
      return false;
   }
}

bool Window::isFlightTypeReturnFlight() const {
   return m_field_flight_type->currentIndex() == 1;
}

void Window::flightTypeSelected() {
   applyConstraints();
}

void Window::flightDateChanged() {
   applyConstraints();
}

void Window::returnDateChanged() {
   applyConstraints();
}

void Window::submitReleased() {
   QString message;
   if (isFlightTypeReturnFlight()) {
      message = QString("You booked a flight on %1 with a return on %2.").arg(
         m_field_flight_date->text(),
         m_field_return_date->text()
      );
   } else {
      message = QString("You booked a one-way flight on %1.").arg(
         m_field_flight_date->text()
      );
   }
   QMessageBox::information(this, "Booking", message);
}
