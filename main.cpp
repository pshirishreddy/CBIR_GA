#include <iostream>
#include <QApplication>
#include <QDialog>
#include <highgui.h>
#include <cv.h>
#include "HaarWavelet.h"
#include "System.h"
#include "Similarity.h"
#include "headers.h"
#include "QuickSort.h"
#include <time.h>
#include "images.h"
#include "Chromosome.h"

using namespace std;

int main(int argc, char* argv[])
{

		HaarWavelet H;
	    System Sy;
	    Similarity Si;
	    IplImage *first = cvLoadImage("db/s29_10.jpg");
	    IplImage *sec = cvCreateImage(cvSize(256,256),8,3);
	    IplImage *gray = cvCreateImage(cvSize(256,256),8,1);
	    cvNamedWindow("query Image",1);

	    cvResize(first,sec,CV_INTER_LINEAR);
	    cvShowImage("query Image",sec);
	    cvWaitKey(0);
	   // cvNamedWindow("query_Image",1);
	    //cvShowImage("query_Image",first);

	    /**
	     * Color Decomposition along each channel of color
	     */

	    RgbImage imgA(first);
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
	   // cvNamedWindow("first",1);
	   // cvShowImage("first",sec);
	   // cvWaitKey(0);

	    /**
	     * storing the wavelet coeffieciens of query image in rgb_pos.txt
	     */

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

		/**
		 * Starting decomposition of images in the database
		 * stores wavelet coefficients in respective filenames
		 */

	    cvCvtColor(sec,gray,CV_BGR2GRAY);
	    //cvShowImage("query_res",gray);
	    //cvWaitKey(0);
	    //gray = H.decompose_Image(gray);
	    //cvShowImage("query_res",gray);
	    //cvWaitKey(0);


	    IplImage *seq_sec = cvCreateImage(cvSize(256,256),8,3);
	    IplImage *seq_gray = cvCreateImage(cvSize(256,256),8,1);

	    float wav = 0;
	    map<float,string> sim;
	    map<float,string> :: iterator mit;
	    list<string> file_na = Sy.file_names("db/");
	    list<string> :: iterator lit;


	    /**
	     * Uncomment the below in order to initiate storage of wavelet coefficients
	     * in external files
	     *
	     * Also store the filenames of the images in filename demo.txt
	     */

	    /*  char *pch;
			char *cstr;
			IplImage* img_seq;

	        for(lit = file_na.begin(); lit!=file_na.end(); lit++) {
	    	cout<<(*lit)<<endl;
	    	img_seq = cvLoadImage((*lit).c_str());
	    	cvShowImage("test",img_seq);
	    	//cvWaitKey(0);
	    	cvResize(img_seq,seq_sec,CV_INTER_LINEAR);

	        //RgbImage imgA(first);
	        //cout<<(int)imgA[0][0].b<<" "<<(int)imgA[0][0].g<<" "<<(int)imgA[0][0].r<<endl ;
	        seq_sec = H.decompose_Image_b(seq_sec);
	        cvNamedWindow("Image",1);
	        cvShowImage("Image",seq_sec);
	        //cvWaitKey(0);

	        seq_sec = H.decompose_Image_g(seq_sec);
	        cvNamedWindow("Image",1);
	        cvShowImage("Image",seq_sec);
	        //cvWaitKey(0);

	        seq_sec = H.decompose_Image_r(seq_sec);
	        cvNamedWindow("Image",1);
	        cvShowImage("Image",seq_sec);
	        //cvWaitKey(0);

	        RgbImage SeqImg(seq_sec);
	        //ofstream

	        cout<<(*lit).c_str();
	        cstr = new char[(*lit).size()+1];
	        strcpy(cstr, (*lit).c_str());
	        pch = strtok(cstr,".");
	        cout<<"\n"<<pch;
	        k=0;
	        ofstream temp_file(pch, ios::out);
		    for(int i=0; i<32; i++) {
		    	for(int j=0; j<32; j++) {
		    		k = i+32*j;
		    		arr_r[k] = (int)SeqImg[i][j].r;
		    		arr_g[k] = (int)SeqImg[i][j].g;
		    		arr_b[k] = (int)SeqImg[i][j].b;
		    	//	if(arr_r[k] !=0 || arr_g[k] !=0 || arr_b[k] != 0)
		    			temp_file<<arr_r[k]<<"\t"<<arr_g[k]<<"\t"<<arr_b[k]<<"\n";//<<i<<" "<<j<<"\n";

		    	}
		    }
		    temp_file.close();


			cvCvtColor(seq_sec,seq_gray,CV_BGR2GRAY);

			//single channel
			//seq_gray = H.decompose_Image(seq_gray);
			wav = Si.wave_coeff_stg(gray,seq_gray);
			//printf ("It took you %.2lf seconds to type your name.\n", dif );
			//cvShowImage("test",seq_gray);
			//cvWaitKey(0);
			// end single channel

			sim[wav] = *lit;
			cout<<"\n"<<wav<<"\n";
			cvReleaseImage(&img_seq);
			delete [] cstr;
	    }

	    ofstream outfile("demo.txt",ios::out);
	    for(mit = sim.begin();mit!=sim.end(); mit++)
	    {
	    	outfile<<((*mit).second).c_str()<<"\n";
	    }
	    outfile.close();*/

	    /**
	     * Chromosome Construction using the rgb values of images
	     */

	    char *cstr_1, *pch_1;
	    string str;
	    ifstream infile("demo.txt", ios::in);
	    while(!infile.eof()) {
	    	infile>>str;
	    	//cout<<str<<"\n";
	        cstr_1 = new char[str.size()+1];
	        strcpy(cstr_1, str.c_str());
	        pch_1 = strtok(cstr_1,".");
	        wav = Si.wave_coeff_loc_aware("rgb_pos.txt",pch_1);
			sim[wav] = str;
	        delete [] cstr_1;
	    }
	    infile.close();

	    ofstream loc_file("local.txt",ios::out);
	    for(mit = sim.begin();mit!=sim.end(); mit++)
	    {
	    	loc_file<<((*mit).second).c_str()<<"\n";
	    }
	    loc_file.close();

	    /** End Test Chromosome **/


	    cvReleaseImage(&seq_sec);
	    cvReleaseImage(&seq_gray);
	    cvReleaseImage(&first);
	    cvReleaseImage(&gray);
	    cvDestroyWindow("Image");
	    cvDestroyWindow("dbm1");
	    cvDestroyWindow("dbm2");
	    cvDestroyWindow("dbm_1");
	    cvDestroyWindow("dbm_2");

		cvDestroyWindow("dbm");

	/* Ending openCV code */

	cout<<"Hello";
	QApplication app(argc, argv);
	SeqImg *dialog = new SeqImg;
		
	dialog->show();
	
	return app.exec();
}
