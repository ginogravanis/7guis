#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "window.h"

Window::Window(QWidget* parent)
   : QWidget(parent),
     m_count(0),
     m_button(std::make_unique<QPushButton>(tr("Count"))),
     m_label(std::make_unique<QLabel>(QString::number(m_count))) {
   setWindowTitle(tr("GUI 1: Counter"));
   QHBoxLayout* layout = new QHBoxLayout;
   layout->addWidget(m_label.get());
   layout->addWidget(m_button.get());
   setLayout(layout);

   connect(
      m_button.get(), &QPushButton::released,
      this, &Window::onButtonReleased
   );
}

Window::~Window() {
}

void Window::onButtonReleased() {
   m_count++;
   m_label->setText(QString::number(m_count));
}
