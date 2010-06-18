#include <QtGui>
#include <QMainWindow>
#include <QApplication>
#include <QPrinter>
#include <QLayout>
#include <fstream>
#include <iostream>
#include <string.h>
#include "Similarity.h"
#include "Chromosome.h"
#include "headers.h"
#include "HaarWavelet.h"

#include "images.h"

 class QAction;
 class QLabel;
 class QMenu;
 class QMenuBar;
 class QScrollArea;
 class QScrollBar;

 using namespace std;
/**
 * Qt Programming
 * Initialization of UI Constructor connects signals and slots
 */
SeqImg :: SeqImg (QWidget* parent) : QMainWindow(parent)
{
	setupUi(this);
	
	connect(spinBox1, SIGNAL(valueChanged(int)), horizontalSlider1, SLOT(setValue(int)));
	connect(horizontalSlider1, SIGNAL(valueChanged(int)), spinBox1, SLOT(setValue(int)));
	cout<<"\n"<<spinBox1->value()<<"\n";

	connect(spinBox2, SIGNAL(valueChanged(int)), horizontalSlider2, SLOT(setValue(int)));
	connect(horizontalSlider2, SIGNAL(valueChanged(int)), spinBox2, SLOT(setValue(int)));
	
	connect(spinBox3, SIGNAL(valueChanged(int)), horizontalSlider3, SLOT(setValue(int)));
	connect(horizontalSlider3, SIGNAL(valueChanged(int)), spinBox3, SLOT(setValue(int)));
	
	connect(spinBox4, SIGNAL(valueChanged(int)), horizontalSlider4, SLOT(setValue(int)));
	connect(horizontalSlider4, SIGNAL(valueChanged(int)), spinBox4, SLOT(setValue(int)));
	
	connect(spinBox5, SIGNAL(valueChanged(int)), horizontalSlider5, SLOT(setValue(int)));
	connect(horizontalSlider5, SIGNAL(valueChanged(int)), spinBox5, SLOT(setValue(int)));
	
	connect(spinBox6, SIGNAL(valueChanged(int)), horizontalSlider6, SLOT(setValue(int)));
	connect(horizontalSlider6, SIGNAL(valueChanged(int)), spinBox6, SLOT(setValue(int)));
	
	connect(spinBox7, SIGNAL(valueChanged(int)), horizontalSlider7, SLOT(setValue(int)));
	connect(horizontalSlider7, SIGNAL(valueChanged(int)), spinBox7, SLOT(setValue(int)));
	
	connect(spinBox8, SIGNAL(valueChanged(int)), horizontalSlider8, SLOT(setValue(int)));
	connect(horizontalSlider8, SIGNAL(valueChanged(int)), spinBox8, SLOT(setValue(int)));
	
	connect(spinBox9, SIGNAL(valueChanged(int)), horizontalSlider9, SLOT(setValue(int)));
	connect(horizontalSlider9, SIGNAL(valueChanged(int)), spinBox9, SLOT(setValue(int)));
	
	connect(spinBox10, SIGNAL(valueChanged(int)), horizontalSlider10, SLOT(setValue(int)));
	connect(horizontalSlider10, SIGNAL(valueChanged(int)), spinBox10, SLOT(setValue(int)));
	
	connect(spinBox11, SIGNAL(valueChanged(int)), horizontalSlider11, SLOT(setValue(int)));
	connect(horizontalSlider11, SIGNAL(valueChanged(int)), spinBox11, SLOT(setValue(int)));
	
	connect(spinBox12, SIGNAL(valueChanged(int)), horizontalSlider12, SLOT(setValue(int)));
	connect(horizontalSlider12, SIGNAL(valueChanged(int)), spinBox12, SLOT(setValue(int)));
	
	connect(actionNew, SIGNAL(triggered()), this, SLOT(fileaction()));
	connect(actionRun, SIGNAL(triggered()), this, SLOT(iteration()));
	connect(actionQuery_Image, SIGNAL(triggered()), this, SLOT(showimage()));
	connect(actionAbout, SIGNAL(triggered()), this, SLOT(about()));
	connect(actionAbout_Author, SIGNAL(triggered()), this, SLOT(aboutAuthor()));

//	connect(actionExit, SIGNAL(triggered()), this, SLOT(closeAllWindows()));
//	connect(newAction, SIGNAL(triggered()), this, SLOT(newFile()))

	connect(run, SIGNAL(clicked()), this, SLOT(iteration()));

	connect(display, SIGNAL(clicked()), this, SLOT(setImage_wrapper()));

	setImage();

}
void SeqImg :: about() {
	   QMessageBox::about(this, tr("About project"),
	             tr("The <b>Similarity Calculator</b> calculates similar image with regard to "
	            		 "the query image."
	            		 "Similarity Calculation is done using Haar Decomposition and Jacobs Equation"));

}
void SeqImg :: aboutAuthor() {
	   QMessageBox::about(this, tr("About project"),
	             tr("Author: Shirish Reddy P"));

}
void SeqImg :: showimage() {
	cvNamedWindow("Query Image",1);
	IplImage* qImg = cvLoadImage( fileName13.toStdString().c_str());
	IplImage *sec = cvCreateImage(cvSize(256,256),8,3);
	cvResize(qImg, sec, CV_INTER_LINEAR);
	cvShowImage("Query Image", sec);
	cvWaitKey(0);
	cvDestroyWindow("Query Image");
	cvReleaseImage(&qImg);
	cvReleaseImage(&sec);
}
void SeqImg :: fileaction() {
	HaarWavelet H;
	cout<<"FILE ACTION\n";
	fileName = QFileDialog::getOpenFileName(this);

	cout<<fileName.toStdString();
	IplImage* first = cvLoadImage(fileName.toStdString().c_str());
	IplImage *sec = cvCreateImage(cvSize(256,256),8,3);
	cvResize(first,sec,CV_INTER_LINEAR);


    sec = H.decompose_Image_b(sec); //Decomposition along blue channel
    cvNamedWindow("Decomposing Image",1);
    cvShowImage("Decomposing Image",sec);
    cvWaitKey(0);

    sec = H.decompose_Image_g(sec); //Decomposition along green channel
    cvNamedWindow("Decomposing Image",1);
    cvShowImage("Decomposing Image",sec);
    cvWaitKey(0);

    sec = H.decompose_Image_r(sec); //Decomposition along red channel
    cvNamedWindow("Decomposing Image",1);
    cvShowImage("Decomposing Image",sec);
    cvWaitKey(0);

	RgbImage imgDec(sec);
    ofstream rgb_pos("rgb_pos.txt",ios::out);

    int arr_r[65535], arr_g[65535], arr_b[65535];
    int k=0;
    for(int i=0; i<32; i++) {
    	for(int j=0; j<32; j++) {
    		k = i+32*j;
    		arr_r[k] = (int)imgDec[i][j].r;
    		arr_g[k] = (int)imgDec[i][j].g;
    		arr_b[k] = (int)imgDec[i][j].b;
    		rgb_pos<<arr_r[k]<<"\t"<<arr_g[k]<<"\t"<<arr_b[k]<<"\n";//<<i<<" "<<j<<"\n";

    	}
    }
    rgb_pos.close();

}
/**
 * Defining iteration to be iterated over the fitness value assigned by the user
 * Called when user clicks RUN button in the UI
 * Handles subsequent horizontal and vertical crossover with the high fitness value
 * image
 */
void SeqImg :: iteration()
{

	int fitness[12];
	string highfit;
	fitness[0] = spinBox1->value();
	fitness[1] = spinBox2->value();
	fitness[2] = spinBox3->value();
	fitness[3] = spinBox4->value();
	fitness[4] = spinBox5->value();
	fitness[5] = spinBox6->value();
	fitness[6] = spinBox7->value();
	fitness[7] = spinBox8->value();
	fitness[8] = spinBox9->value();
	fitness[9] = spinBox10->value();
	fitness[10]= spinBox11->value();
	fitness[11]= spinBox12->value();

	int max = 0;
	int index =0;
	for(int i=0; i<12; i++) {
		if(fitness[i]>max) {
			max = fitness[i];
			index = i;
		}
	}
	cout<<max<<endl;
	switch(index) {
	case 0 :
			highfit = fileName1.toStdString();
			cout<<highfit<<endl;
			break;
	case 1 :
			highfit=fileName2.toStdString();
			cout<<highfit<<endl;
			break;
	case 2 :
			highfit=fileName3.toStdString();
			cout<<highfit;
			break;
	case 3 :
			highfit=fileName4.toStdString();
			cout<<highfit;
			break;
	case 4 :
			highfit=fileName5.toStdString();
			cout<<highfit;
			break;
	case 5 :
			highfit=fileName6.toStdString();
			cout<<highfit;
			break;
	case 6 :
			highfit=fileName7.toStdString();
			cout<<highfit;
			break;
	case 7 :
			highfit=fileName8.toStdString();
			cout<<highfit;
			break;
	case 8 :
			highfit=fileName9.toStdString();
			cout<<highfit;
			break;
	case 9:
			highfit=fileName10.toStdString();
			cout<<highfit;
			break;
	case 10:
			highfit=fileName11.toStdString();
			cout<<highfit;
			break;
	case 11:
			highfit=fileName12.toStdString();
			cout<<highfit;
			break;
	default :
		break;
	}
	char *cstr_2, *pch_2;
    cstr_2 = new char[highfit.size()+1];
    strcpy(cstr_2, highfit.c_str());
    pch_2 = strtok(cstr_2,".");
    cout<<pch_2<<endl;

	Chromosome C;
	C.horizontalCrossover(pch_2);
	C.verticalCrossover("hybrid2.txt");

	string temp_str;
	ifstream hyb("hybrid2.txt",ios::in);
	ofstream rgb("rgb_pos.txt",ios::out);

	while(!hyb.eof()) {
		for(int i=0; i<3; i++) {
			hyb>>temp_str;
			rgb<<temp_str;
			rgb<<"\t";
		}
		rgb<<"\n";
	}

	rgb.close();
	hyb.close();

	Similarity Si;
	long wav;
    map<float,string> sim;
    map<float,string> :: iterator mit;

    char *cstr_1, *pch_1;
    //cout<<val1[0][0];
    string str;
    ifstream infile("demo.txt", ios::in);
    int count = 0;
    while(!infile.eof()) {
    	count++;
    	progressBar->setValue(count);
    	infile>>str;
    //	cout<<str<<"\n";
        cstr_1 = new char[str.size()+1];
        strcpy(cstr_1, str.c_str());
        pch_1 = strtok(cstr_1,".");
        wav = Si.wave_coeff_loc_aware("hybrid2.txt",pch_1);
		sim[wav] = str;
        delete [] cstr_1;
    }
    infile.close();

    ofstream loc_file("local2.txt",ios::out);
    for(mit = sim.begin();mit!=sim.end(); mit++)
    {
    	loc_file<<((*mit).second).c_str()<<"\n";
    }
    loc_file.close();

	cout<<"HELLO\nHELLO\n";
}
/**
 * @Desc: Wrapper for setting images in the image lables on UI
 * Display button calls this function.
 */
void SeqImg :: setImage_wrapper()
{
	cout<<"SETTING IMAGE\n";

	ifstream file("/home/shirish/Desktop/Education/qt/seqImg/local2.txt", ios::in);
	char n[1000];

    file >> n;
    fileName13 = n;
    if(fileName.toStdString().size()!=0)
        fileName13 = fileName;

    QImage image13(fileName13);
	imageLabel13->setBackgroundRole(QPalette::Base);
    imageLabel13->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel13->setScaledContents(true);
    if (image13.isNull()) {
         QMessageBox::information(this, tr("Image Viewer"),
                             tr("Cannot load1 %1.").arg(fileName13));
          return;
     }
    imageLabel13->setPixmap(QPixmap::fromImage(image13));


	file >> n;
	fileName1 = n;
    QImage image1(fileName1);

    imageLabel1->setBackgroundRole(QPalette::Base);
    imageLabel1->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel1->setScaledContents(true);
    if (image1.isNull()) {
         QMessageBox::information(this, tr("Image Viewer"),
                             tr("Cannot load %1.").arg(fileName1));
          return;
     }
    imageLabel1->setPixmap(QPixmap::fromImage(image1));

    file >> n;
    fileName2 = n;
    QImage image2(fileName2);
	imageLabel2->setBackgroundRole(QPalette::Base);
    imageLabel2->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel2->setScaledContents(true);
    if (image2.isNull()) {
         QMessageBox::information(this, tr("Image Viewer"),
                             tr("Cannot load %1.").arg(fileName2));
          return;
     }
     imageLabel2->setPixmap(QPixmap::fromImage(image2));

     file >> n;
     fileName3 = n;
     QImage image3(fileName3);
 	 imageLabel3->setBackgroundRole(QPalette::Base);
     imageLabel3->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
     imageLabel3->setScaledContents(true);
     if (image3.isNull()) {
          QMessageBox::information(this, tr("Image Viewer"),
                              tr("Cannot load %1.").arg(fileName3));
           return;
      }
     imageLabel3->setPixmap(QPixmap::fromImage(image3));

     file >> n;
     fileName4 = n;
     QImage image4(fileName4);
 	 imageLabel4->setBackgroundRole(QPalette::Base);
     imageLabel4->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
     imageLabel4->setScaledContents(true);
     if (image4.isNull()) {
          QMessageBox::information(this, tr("Image Viewer"),
                              tr("Cannot load %1.").arg(fileName4));
           return;
      }
     imageLabel4->setPixmap(QPixmap::fromImage(image4));

     file >> n;
     fileName5 = n;
     QImage image5(fileName3);
 	 imageLabel5->setBackgroundRole(QPalette::Base);
     imageLabel5->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
     imageLabel5->setScaledContents(true);
     if (image5.isNull()) {
          QMessageBox::information(this, tr("Image Viewer"),
                              tr("Cannot load %1.").arg(fileName5));
           return;
      }
     imageLabel5->setPixmap(QPixmap::fromImage(image5));

     file >> n;
     fileName6 = n;
     QImage image6(fileName6);
 	 imageLabel6->setBackgroundRole(QPalette::Base);
     imageLabel6->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
     imageLabel6->setScaledContents(true);
     if (image6.isNull()) {
          QMessageBox::information(this, tr("Image Viewer"),
                              tr("Cannot load %1.").arg(fileName6));
           return;
      }
     imageLabel6->setPixmap(QPixmap::fromImage(image6));

     file >> n;
     fileName7 = n;
     QImage image7(fileName7);
 	 imageLabel7->setBackgroundRole(QPalette::Base);
     imageLabel7->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
     imageLabel7->setScaledContents(true);
     if (image7.isNull()) {
          QMessageBox::information(this, tr("Image Viewer"),
                              tr("Cannot load %1.").arg(fileName7));
           return;
      }
     imageLabel7->setPixmap(QPixmap::fromImage(image7));

     file >> n;
     fileName8 = n;
     QImage image8(fileName8);
 	 imageLabel8->setBackgroundRole(QPalette::Base);
     imageLabel8->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
     imageLabel8->setScaledContents(true);
     if (image8.isNull()) {
          QMessageBox::information(this, tr("Image Viewer"),
                              tr("Cannot load %1.").arg(fileName8));
           return;
      }
     imageLabel8->setPixmap(QPixmap::fromImage(image8));

     file >> n;
     fileName9 = n;
     QImage image9(fileName9);
 	 imageLabel9->setBackgroundRole(QPalette::Base);
     imageLabel9->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
     imageLabel9->setScaledContents(true);
     if (image9.isNull()) {
          QMessageBox::information(this, tr("Image Viewer"),
                              tr("Cannot load %1.").arg(fileName9));
           return;
      }
     imageLabel9->setPixmap(QPixmap::fromImage(image9));

     file >> n;
     fileName10 = n;
     QImage image10(fileName10);
 	 imageLabel10->setBackgroundRole(QPalette::Base);
     imageLabel10->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
     imageLabel10->setScaledContents(true);
     if (image10.isNull()) {
          QMessageBox::information(this, tr("Image Viewer"),
                              tr("Cannot load %1.").arg(fileName10));
           return;
      }
     imageLabel10->setPixmap(QPixmap::fromImage(image10));

     file >> n;
     fileName11 = n;
     QImage image11(fileName11);
 	 imageLabel11->setBackgroundRole(QPalette::Base);
     imageLabel11->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
     imageLabel11->setScaledContents(true);
     if (image11.isNull()) {
          QMessageBox::information(this, tr("Image Viewer"),
                              tr("Cannot load %1.").arg(fileName11));
           return;
      }
     imageLabel11->setPixmap(QPixmap::fromImage(image11));

     file >> n;
     fileName12 = n;
     QImage image12(fileName12);
 	 imageLabel12->setBackgroundRole(QPalette::Base);
     imageLabel12->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
     imageLabel12->setScaledContents(true);
     if (image12.isNull()) {
          QMessageBox::information(this, tr("Image Viewer"),
                              tr("Cannot load %1.").arg(fileName12));
           return;
      }
     imageLabel12->setPixmap(QPixmap::fromImage(image12));

     file.close();

}

/**
 * Initial Setup for the UI.
 * Setting up images on the image labels in the UI
 */
void SeqImg :: setImage()
{

	ifstream file("/home/shirish/Desktop/Education/qt/seqImg/local.txt", ios::in);
	char n[1000];

    file >> n;
    fileName13 = n;
    QImage image13(fileName13);
	 imageLabel13->setBackgroundRole(QPalette::Base);
    imageLabel13->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel13->setScaledContents(true);
    if (image13.isNull()) {
         QMessageBox::information(this, tr("Image Viewer"),
                             tr("Cannot load1 %1.").arg(fileName13));
          return;
     }
    imageLabel13->setPixmap(QPixmap::fromImage(image13));


	file >> n;
	fileName1 = n;
    QImage image1(fileName1);

    imageLabel1->setBackgroundRole(QPalette::Base);
    imageLabel1->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel1->setScaledContents(true);
    if (image1.isNull()) {
         QMessageBox::information(this, tr("Image Viewer"),
                             tr("Cannot load %1.").arg(fileName1));
          return;
     }
    imageLabel1->setPixmap(QPixmap::fromImage(image1));
		 
    file >> n;
    fileName2 = n;
    QImage image2(fileName2);
	imageLabel2->setBackgroundRole(QPalette::Base);
    imageLabel2->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel2->setScaledContents(true);
    if (image2.isNull()) {
         QMessageBox::information(this, tr("Image Viewer"),
                             tr("Cannot load %1.").arg(fileName2));
          return;
     }
     imageLabel2->setPixmap(QPixmap::fromImage(image2));

     file >> n;
     fileName3 = n;
     QImage image3(fileName3);
 	 imageLabel3->setBackgroundRole(QPalette::Base);
     imageLabel3->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
     imageLabel3->setScaledContents(true);
     if (image3.isNull()) {
          QMessageBox::information(this, tr("Image Viewer"),
                              tr("Cannot load %1.").arg(fileName3));
           return;
      }
     imageLabel3->setPixmap(QPixmap::fromImage(image3));

     file >> n;
     fileName4 = n;
     QImage image4(fileName4);
 	 imageLabel4->setBackgroundRole(QPalette::Base);
     imageLabel4->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
     imageLabel4->setScaledContents(true);
     if (image4.isNull()) {
          QMessageBox::information(this, tr("Image Viewer"),
                              tr("Cannot load %1.").arg(fileName4));
           return;
      }
     imageLabel4->setPixmap(QPixmap::fromImage(image4));

     file >> n;
     fileName5 = n;
     QImage image5(fileName3);
 	 imageLabel5->setBackgroundRole(QPalette::Base);
     imageLabel5->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
     imageLabel5->setScaledContents(true);
     if (image5.isNull()) {
          QMessageBox::information(this, tr("Image Viewer"),
                              tr("Cannot load %1.").arg(fileName5));
           return;
      }
     imageLabel5->setPixmap(QPixmap::fromImage(image5));

     file >> n;
     fileName6 = n;
     QImage image6(fileName6);
 	 imageLabel6->setBackgroundRole(QPalette::Base);
     imageLabel6->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
     imageLabel6->setScaledContents(true);
     if (image6.isNull()) {
          QMessageBox::information(this, tr("Image Viewer"),
                              tr("Cannot load %1.").arg(fileName6));
           return;
      }
     imageLabel6->setPixmap(QPixmap::fromImage(image6));

     file >> n;
     fileName7 = n;
     QImage image7(fileName7);
 	 imageLabel7->setBackgroundRole(QPalette::Base);
     imageLabel7->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
     imageLabel7->setScaledContents(true);
     if (image7.isNull()) {
          QMessageBox::information(this, tr("Image Viewer"),
                              tr("Cannot load %1.").arg(fileName7));
           return;
      }
     imageLabel7->setPixmap(QPixmap::fromImage(image7));

     file >> n;
     fileName8 = n;
     QImage image8(fileName8);
 	 imageLabel8->setBackgroundRole(QPalette::Base);
     imageLabel8->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
     imageLabel8->setScaledContents(true);
     if (image8.isNull()) {
          QMessageBox::information(this, tr("Image Viewer"),
                              tr("Cannot load %1.").arg(fileName8));
           return;
      }
     imageLabel8->setPixmap(QPixmap::fromImage(image8));

     file >> n;
     fileName9 = n;
     QImage image9(fileName9);
 	 imageLabel9->setBackgroundRole(QPalette::Base);
     imageLabel9->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
     imageLabel9->setScaledContents(true);
     if (image9.isNull()) {
          QMessageBox::information(this, tr("Image Viewer"),
                              tr("Cannot load %1.").arg(fileName9));
           return;
      }
     imageLabel9->setPixmap(QPixmap::fromImage(image9));

     file >> n;
     fileName10 = n;
     QImage image10(fileName10);
 	 imageLabel10->setBackgroundRole(QPalette::Base);
     imageLabel10->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
     imageLabel10->setScaledContents(true);
     if (image10.isNull()) {
          QMessageBox::information(this, tr("Image Viewer"),
                              tr("Cannot load %1.").arg(fileName10));
           return;
      }
     imageLabel10->setPixmap(QPixmap::fromImage(image10));

     file >> n;
     fileName11 = n;
     QImage image11(fileName11);
 	 imageLabel11->setBackgroundRole(QPalette::Base);
     imageLabel11->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
     imageLabel11->setScaledContents(true);
     if (image11.isNull()) {
          QMessageBox::information(this, tr("Image Viewer"),
                              tr("Cannot load %1.").arg(fileName11));
           return;
      }
     imageLabel11->setPixmap(QPixmap::fromImage(image11));

     file >> n;
     fileName12 = n;
     QImage image12(fileName12);
 	 imageLabel12->setBackgroundRole(QPalette::Base);
     imageLabel12->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
     imageLabel12->setScaledContents(true);
     if (image12.isNull()) {
          QMessageBox::information(this, tr("Image Viewer"),
                              tr("Cannot load %1.").arg(fileName12));
           return;
      }
     imageLabel12->setPixmap(QPixmap::fromImage(image12));

     file.close();

}
