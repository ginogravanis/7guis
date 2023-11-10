#pragma once

#include <memory>
#include <QWidget>

class QPushButton;
class QLabel;

class Window : public QWidget {
   Q_OBJECT

   public:
      explicit Window(QWidget* parent = nullptr);
      ~Window();

   private slots:
      void onButtonReleased();

   private:
      int m_count;
      std::unique_ptr<QPushButton> m_button;
      std::unique_ptr<QLabel> m_label;
};
