#pragma once

#include <memory>
#include <QStringList>
#include <QWidget>

class QComboBox;
class QLineEdit;
class QPushButton;

class Window : public QWidget {
   Q_OBJECT

   public:
      static const QString dateFormat;
      static const QString errorStyle;
      explicit Window(QWidget* parent = nullptr);
      ~Window();

   private:
      void applyConstraints();
      void applyConstraintsForOneWay();
      void applyConstraintsForReturnFlight();
      bool containsValidDate(QLineEdit* field);
      bool isFlightTypeReturnFlight() const;

   private slots:
      void flightTypeSelected();
      void flightDateChanged();
      void returnDateChanged();
      void submitReleased();

   private:
      std::unique_ptr<QStringList> m_flight_types;
      std::unique_ptr<QComboBox> m_field_flight_type;
      std::unique_ptr<QPushButton> m_button_submit;
      std::unique_ptr<QLineEdit> m_field_flight_date;
      std::unique_ptr<QLineEdit> m_field_return_date;
};
