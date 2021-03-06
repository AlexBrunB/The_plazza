//
// menu.cpp for menu in /home/abrun/delivery/Tek2/Cpp/cpp_plazza/UI
// 
// Made by Alexandre Brun
// Login   <abrun@epitech.net>
// 
// Started on  Thu Apr 20 16:03:42 2017 Alexandre Brun
// Last update Sat Apr 29 10:48:15 2017 Alexandre Brun
//


#include "menu.hpp"

#include <string>
#include <QtGui>
#include <queue>
#include <mutex>

Window::Window(QWidget *parent)
  : QWidget(parent)
{
  setStyleSheet("background-color:grey");
  findButton = createButton(tr("&Find"), SLOT(find()));

  fileComboBox = createComboBox(tr("*"));
  textComboBox = createComboBox();
  directoryComboBox = createComboBox(QDir::currentPath());
  
  textLabel = new QLabel(tr("Containing text:"));
  directoryLabel = new QLabel(tr("In directory:"));
  filesFoundLabel = new QLabel;

  createFilesTable();

  QGridLayout *mainLayout = new QGridLayout;
  mainLayout->setSizeConstraint(QLayout::SetNoConstraint);
  mainLayout->addWidget(textLabel, 1, 0);
  mainLayout->addWidget(textComboBox, 1, 1, 1, 2);
  mainLayout->addWidget(directoryLabel, 2, 0);
  mainLayout->addWidget(directoryComboBox, 2, 1);
  mainLayout->addWidget(filesTable, 3, 0, 1, 3);
  mainLayout->addWidget(filesFoundLabel, 4, 0, 1, 2);
  mainLayout->addWidget(findButton, 4, 2);
  setLayout(mainLayout);

  setWindowTitle(tr("PLAZZA"));
}

static void updateComboBox(QComboBox *comboBox)
{
  if (comboBox->findText(comboBox->currentText()) == -1)
    comboBox->addItem(comboBox->currentText());
}

void Window::find()
{
  filesTable->setRowCount(0);

  QString fileName = fileComboBox->currentText();
  QString text = textComboBox->currentText();
  QString path = directoryComboBox->currentText();
  
  updateComboBox(fileComboBox);
  updateComboBox(textComboBox);
  updateComboBox(directoryComboBox);

  currentDir = QDir(path);

  QStringList files;
  if (fileName.isEmpty())
    fileName = "*";
  files = currentDir.entryList(QStringList(fileName), QDir::Files | QDir::NoSymLinks);

  if (!text.isEmpty())
    files = findFiles(files, text);
  showFiles(files);
}

QStringList Window::findFiles(const QStringList &files, const QString &text)
{
  QProgressDialog progressDialog(this);
  progressDialog.setCancelButtonText(tr("&Cancel"));
  progressDialog.setRange(0, files.size());
  progressDialog.setWindowTitle(tr("Find Files"));

  QStringList foundFiles;

  for (int i = 0; i < files.size(); ++i)
    {
      progressDialog.setValue(i);
      progressDialog.setLabelText(tr("Searching file number %1 of %2...")
				  .arg(i).arg(files.size()));
      qApp->processEvents();

      if (progressDialog.wasCanceled())
	break;

      QFile file(currentDir.absoluteFilePath(files[i]));

      if (file.open(QIODevice::ReadOnly)) {
	QString line;
	QTextStream in(&file);
	while (!in.atEnd()) {
	  if (progressDialog.wasCanceled())
	    break;
	  line = in.readLine();
	  if (line.contains(text)) {
	    foundFiles << files[i];
	    break;
	  }
	}
      }
    }
  return (foundFiles);
}

void Window::showFiles(const QStringList &files)
{
  for (int i = 0; i < files.size(); ++i)
    {
      QFile file(currentDir.absoluteFilePath(files[i]));
      qint64 size = QFileInfo(file).size();

      QTableWidgetItem *fileNameItem = new QTableWidgetItem(files[i]);
      fileNameItem->setFlags(fileNameItem->flags() ^ Qt::ItemIsEditable);
      QTableWidgetItem *sizeItem = new QTableWidgetItem(tr("%1 KB")
						.arg(int((size + 1023) / 1024)));
      sizeItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
      sizeItem->setFlags(sizeItem->flags() ^ Qt::ItemIsEditable);

      int row = filesTable->rowCount();
      filesTable->insertRow(row);
      filesTable->setItem(row, 0, fileNameItem);
      filesTable->setItem(row, 1, sizeItem);
    }
  filesFoundLabel->setText(tr("%1 file(s) found").arg(files.size()));
  filesFoundLabel->setWordWrap(true);
}

QPushButton *Window::createButton(const QString &text, const char *member)
{
  QPushButton *button = new QPushButton(text);
  connect(button, SIGNAL(clicked()), this, member);
  return (button);
}

QComboBox *Window::createComboBox(const QString &text)
{
  QComboBox *comboBox = new QComboBox;
  comboBox->setEditable(true);
  comboBox->addItem(text);
  comboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  return (comboBox);
}

void Window::createFilesTable()
{
  filesTable = new QTableWidget(0, 2);
  filesTable->setSelectionBehavior(QAbstractItemView::SelectRows);

  QStringList labels;
  labels << tr("Filename") << tr("Size");
  filesTable->setHorizontalHeaderLabels(labels);
  filesTable->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
  filesTable->verticalHeader()->hide();
  filesTable->setShowGrid(false);

  connect(filesTable, SIGNAL(cellActivated(int,int)), this, SLOT(openFileOfItem(int,int)));
}

void Window::openFileOfItem(int row, int /* column */)
{
  QTableWidgetItem *item = filesTable->item(row, 0);

  QDesktopServices::openUrl(QUrl::fromLocalFile(currentDir.absoluteFilePath(item->text())));
}
