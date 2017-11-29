//
// main.cpp for main in /home/abrun/delivery/Tek2/Cpp/cpp_plazza/UI
//
// Made by Alexandre Brun
// Login   <abrun@epitech.net>
// 
// Started on  Thu Apr 20 13:52:25 2017 Alexandre Brun
// Last update Thu Apr 27 07:55:37 2017 Alexandre Brun
//

#include "menu.hpp"

#include <QApplication>

int main(int argc, char **argv)
{
  QApplication app(argc, argv);  

  Window window;
  
  window.resize(1200, 980);
  window.setWindowTitle("Plazza");
  window.show();

  return (app.exec());
}
