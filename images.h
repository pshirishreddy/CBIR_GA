#ifndef IMAGES_H
#define IMAGES_H

#include <QDialog>
#include <QMainWindow>
#include <QPrinter>
#include "ui_seqImg.h"
#include <fstream>
class QMenu;

/**
 * Declaration of SIGNALS and SLOTS and private variables used by the UI
 */
class SeqImg : public QMainWindow, public Ui::MainWindow
{
		Q_OBJECT
	public:
		SeqImg(QWidget *parent = 0);
		
	private slots:
		void iteration();
		void setImage_wrapper();
		void fileaction();
		void showimage();
		void about();
		void aboutAuthor();
		//void open();
		//void open();
		//void print();
		
	private:
		void setImage();
		
		void createActions();
		void createMenus();
		
		QPrinter printer;
		QAction *openAct;
		QAction *printAct;
		QAction *exitAct;
	 
		QMenu *fileMenu;
		QMenu *viewMenu;
		QMenu *helpMenu;

		QString fileName;
		QString fileName1;
		QString fileName2;
		QString fileName3;
		QString fileName4;
		QString fileName5;
		QString fileName6;
		QString fileName7;
		QString fileName8;
		QString fileName9;
		QString fileName10;
		QString fileName11;
		QString fileName12;
		QString fileName13;

};

#endif

		
		
