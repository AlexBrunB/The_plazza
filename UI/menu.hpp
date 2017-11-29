/*
** menu.h for menu in /home/abrun/delivery/Tek2/Cpp/cpp_plazza/UI
** 
** Made by Alexandre Brun
** Login   <abrun@epitech.net>
** 
** Started on  Thu Apr 20 15:56:13 2017 Alexandre Brun
// Last update Sat Apr 29 10:44:58 2017 Alexandre Brun
*/

#ifndef		__MENU_HPP__
# define	__MENU_HPP__

# include <QWidget>
# include <QDir>
# include <queue>
# include <mutex>

class QComboBox;
class QLabel;
class QPushButton;
class QTableWidget;
class QTableWidgetItem;

class Window: public QWidget
{
  Q_OBJECT

public:
  Window(QWidget *parent = 0);

private slots:
  void			find();
  void			openFileOfItem(int row, int column);

private:
  QStringList		findFiles(const QStringList &files, const QString &text);
  void			showFiles(const QStringList &files);
  QPushButton		*createButton(const QString &text, const char *member);
  QComboBox		*createComboBox(const QString &text = QString());
  void			createFilesTable();

  QComboBox				*fileComboBox;
  QComboBox				*textComboBox;
  QComboBox				*directoryComboBox;
  QLabel				*fileLabel;
  QLabel				*textLabel;
  QLabel				*directoryLabel;
  QLabel				*filesFoundLabel;
  QPushButton				*findButton;
  QTableWidget				*filesTable;

  QDir			currentDir;
};

#endif	//	__MENU_HPP__
