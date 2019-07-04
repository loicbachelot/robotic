//
// Created by loic on 07/10/16.
//

#include <stdio.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <zconf.h>
#include "serial.h"
#include "portserie.h"


void detectionRouge(IplImage *img, int *avx, int *avy) {
    CvScalar p;
    int x, y, k, compteur = 1;
    for (y = 0; y < img->height; y++) {
        for (x = 0; x < img->width; x++) {
            // récupération d'un pointeur sur le pixel de coordonnées (x,y)
            p = cvGet2D(img, y, x);
            //if ((p.val[0] < color.val[0] - 20) && p.val[0]  && p.val[2] < 255)) {
            if ((2 * p.val[0]) < (p.val[2]) && (2 * p.val[1]) < (p.val[2])) {
                for (k = 0; k < img->nChannels; ++k) {
                    p.val[k] = 0;
                }
                *avx = *avx + x;
                *avy = *avy + y;
                compteur++;
            }
            cvSet2D(img, y, x, p);

        }
    }
    //recupération de la position moyenne de rouge
    *avx = *avx / compteur;
    *avy = *avy / compteur;
}

int main() {
    //init arduino
    Serial_com sp;
    serial_open(&sp, "/dev/ttyACM0");
    initialisation(&sp);
    //init de la cible
    int avx, avy;
    char buff[6];
    char send[6];
    int angle = 90155;
    sprintf(send, "%d", angle);
    // Touche clavier
    char key; //pour quitter le programme
    // Image
    IplImage *image;
    // Capture vidéo
    CvCapture *capture;
    // Ouvrir le flux vidéo
    capture = cvCreateCameraCapture(1);
    if (!capture) {
        printf("Ouverture du flux vidéo impossible !\n");
        return 1;
    }
    cvNamedWindow("tracking rouge", CV_WINDOW_AUTOSIZE);

    serial_write(&sp, send);

    usleep(1000000);

    while (key != 'q' && key != 'Q') {
        // On récupère une image
        image = cvQueryFrame(capture);
        //traitement de l'image
        detectionRouge(image, &avx, &avy);
        // On affiche l'image dans une fenêtre
        cvShowImage("tracking rouge", image);


        //a refaire
        if ((avx - (image->width / 2)) < 20) {
            angle = angle - 1000;
        } else if ((avx - (image->width / 2)) > 20) {
            angle = angle + 1000;
        }

        if ((avy - (image->height / 2)) > 20) {
            angle = angle - 1;
        } else if ((avy - (image->height / 2)) < 20) {
            angle = angle + 1;
        }

        sprintf(send, "%d", angle);
        printf("direction dans la boucle %s\n", send);
        serial_write(&sp, send);
        usleep(1000000);


        //pour quitter le programme
        key = (char) cvWaitKey(1);
    }

    cvWaitKey(10);
    cvReleaseCapture(&capture);
    cvDestroyWindow("tracking rouge");
    serial_close(&sp);
    return 0;
}
