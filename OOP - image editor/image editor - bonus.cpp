// FCAI – OOP Programming – 2023 - Assignment 1
// Program Name:	ImageEditor.cpp
// Purpose: This is our handmade coded image editor with filters ready to apply on any picture/image you wish to edit from your library by playing with the colors and positions of each pixel in the photos
//all you need is to just put the image files in the application file to use them and you will find all your edited images saved here with the name you choose!!


//This RGB code is the same one as the grey scale code except we add a third dimension to the image with the number 3  : [3]   which represents the degree of the three color levels of RGB Red Green Blue , we can create any color we want by adding certain amounts of each of the three colors







#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;

#define fast           ios_base::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);


unsigned char image[SIZE][SIZE][RGB]; //identifing the image that we will edit in colored RGB

void loadImage(); // we use this function to load our desired image to the code to use/edit
void saveImage(); // we use this function to save our edited image to the files with a name of our choice


void blackwhite() { // we use this function to identify the dark parts in the image and turn them black and the darkenlighten parts to turn white , we use the average grey scale of the pixels in the photo for a more accurate result
    int sum = 0;
    int avg;
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            for (int k = 0; k < 3; k++) {
                sum += image[i][j][k];
            }
        }
    }
    sum = sum/3;
    avg = ((sum / 256) / 255)/3;
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            for (int k = 0; k < 3; k++) {
                if (image[i][j][0] >= avg)
                    image[i][j][0] = 255;
                else
                    image[i][j][0] = 0;
                image[i][j][1]=image[i][j][0];
                image[i][j][2]=image[i][j][0];
            }
        }
    }
}

void invert() { // we use this function to invert the colors of the image to the opposite by subtracting the biggest grey scale number so each pixel gives us its opposite color
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            for (int k = 0; k < 3; k++) {
                image[i][j][k] = 255 - image[i][j][k];
            }
        }
    }
}

void merge() { // we use this function to me++rge/combine two pictures together by adding another picture to the code and then combining every pixel from the two pictures together by adding their greyscale number then dividing it by two to get a merged image
    unsigned char tmp[SIZE][SIZE][RGB];
    char imageFileName[100];
    cout << "Enter the name of the image you wish to merge: ";
    cin >> imageFileName;
    strcat(imageFileName, ".bmp");
    readRGBBMP(imageFileName, tmp);
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            for (int k = 0; k < 3; k++) {
                image[i][j][k] = (image[i][j][k] + tmp[i][j][k]) / 2;
            }
        }
    }
}


void flip() { // we use this function to flip the image vertically or horizontally by swapping the position of the pixels with each other to get a flipped image
    cout << "\n1- Flip horizontally\n"
            "2- Flip vertically\n";
    int a;
    int x;
    cin >> a;
    if (a == 1) {
        for (int i = 0; i < 128; i++) {
            for (int j = 0; j < 256; j++) {
                for (int k = 0; k < 3; k++) {
                    x = image[i][j][k];
                    image[i][j][k] = image[256 - i][j][k];
                    image[256 - i][j][k] = x;
                }
            }
        }
    } else if (a == 2) {
        for (int i = 0; i < 256; i++) {
            for (int j = 0; j < 128; j++) {
                for (int k = 0; k < 3; k++) {
                    x = image[i][j][k];
                    image[i][j][k] = image[i][256 - j][k];
                    image[i][256 - j][k] = x;
                }
            }
        }
    } else {
        cout << "Wrong input, please try again\n";
    }
}

void darkenlighten() { // we use this function to darken or lighten the image by decreasing the number of the grey scale pixel by 50% to get a darker image or by adding 50% to the grey scale number to get a lightened+ image
    cout << "\n1- Darken\n"
            "2- Lighten\n";
    int v;
    cin >> v;
    if (v == 1) {
        for (int i = 0; i < 256; i++) {
            for (int j = 0; j < 256; j++) {
                for (int k = 0; k < 3; k++) {
                    image[i][j][k] /= 2;
                }
            }
        }
    }else if (v == 2) {
        for (int i = 0; i < 256; i++) {
            for (int j = 0; j < 256; j++) {
                for (int k = 0; k < 3; k++) {

                    image[i][j][k] += (255 - image[i][j][k]) / 2;
                }
            }
        }
    } else {
        cout << "Wrong input, please try again\n";
    }
}

void rotate() { // we use this function to rotate an image by a certain degree by swapping the position of the pixels with each other to the desired target just like the flip function
    //i use tmp as an empty landscape to transfer the pixels to it in the order i need and then copying it back to the original image to save using another loop
    cout << "\n1- Rotate 90 degrees\n"
            "2- Rotate 180 degrees\n"
            "3- Rotate 270 degrees\n";
    unsigned char tmp[SIZE][SIZE][RGB];
    int a;
    cin >> a;
    if (a == 1) {
        for (int i = 0; i < 3; i++) {
            for (int i = 0; i < 256; i++) {
                for (int j = 0; j < 256; j++) {
                    for (int k = 0; k < 3; k++) {
                        tmp[j][256 - i][k] = image[i][j][k];
                    }
                }
            }
            for (int i = 0; i < 256; i++) {
                for (int j = 0; j < 256; j++) {
                    for (int k = 0; k < 3; k++) {
                        image[i][j][k] = tmp[i][j][k];
                    }
                }
            }
        }
    } else if (a == 2) {
        for (int i = 0; i < 2; i++) {
            for (int i = 0; i < 256; i++) {
                for (int j = 0; j < 256; j++) {
                    for (int k = 0; k < 3; k++) {
                        tmp[j][256 - i][k] = image[i][j][k];
                    }
                }
            }
            for (int i = 0; i < 256; i++) {
                for (int j = 0; j < 256; j++) {
                    for (int k = 0; k < 3; k++) {
                        image[i][j][k] = tmp[i][j][k];
                    }
                }
            }
        }
    } else if (a == 3) {
        for (int i = 0; i < 256; i++) {
            for (int j = 0; j < 256; j++) {
                for (int k = 0; k < 3; k++) {
                    tmp[j][256 - i][k] = image[i][j][k];
                }
            }
        }
        for (int i = 0; i < 256; i++) {
            for (int j = 0; j < 256; j++) {
                for (int k = 0; k < 3; k++) {
                    image[i][j][k] = tmp[i][j][k];
                }
            }
        }
    }else {
        cout << "Wrong input, please try again\n";
    }
}

void enlarge() { // we use this function to enlarge a quarter of the image by getting all the pixels of a desired quarter and multiplying it in size horizontally and vertically so the original 128*128 quarter is now a full 256*256 image
    cout << "\n1- Quarter 1\n"
            "2- Quarter 2\n"
            "3- Quarter 3\n"
            "4- quarter 4\n";
    unsigned char tmp[SIZE][SIZE][RGB];
    int a;
    cin >> a;
    if (a == 1) {
        for (int i = 0; i < 128; i++) {
            for (int j = 0; j < 128; j++) {
                for (int k = 0; k < 3; k++) {
                    tmp[2 * i][2 * j][k] = image[i][j][k];
                    tmp[2 * i][2 * j + 1][k] = image[i][j][k];
                    tmp[2 * i + 1][2 * j][k] = image[i][j][k];
                    tmp[2 * i + 1][(j * 2) + 1][k] = image[i][j][k];
                }
            }
        }
        for (int i = 0; i < 256; i++) {
            for (int j = 0; j < 256; j++) {
                for (int k = 0; k < 3; k++) {
                    image[i][j][k] = tmp[i][j][k];
                }
            }
        }
    } else if (a == 2) {
        for (int i = 0; i < 128; i++) {
            for (int j = 0; j < 128; j++) {
                for (int k = 0; k < 3; k++) {
                    tmp[2 * i][2 * j][k] = image[i][j + 128][k];
                    tmp[2 * i][2 * j + 1][k] = image[i][j + 128][k];
                    tmp[2 * i + 1][2 * j][k] = image[i][j + 128][k];
                    tmp[2 * i + 1][(j * 2) + 1][k] = image[i][j + 128][k];
                }
            }
        }
        for (int i = 0; i < 256; i++) {
            for (int j = 0; j < 256; j++) {
                for (int k = 0; k < 3; k++) {
                    image[i][j][k] = tmp[i][j][k];
                }
            }
        }
    } else if (a == 3) {
        for (int i = 0; i < 128; i++) {
            for (int j = 0; j < 128; j++) {
                for (int k = 0; k < 3; k++) {
                    tmp[2 * i][2 * j][k] = image[i + 128][j][k];
                    tmp[2 * i][2 * j + 1][k] = image[i + 128][j][k];
                    tmp[2 * i + 1][2 * j][k] = image[i + 128][j][k];
                    tmp[2 * i + 1][(j * 2) + 1][k] = image[i + 128][j][k];
                }
            }
        }
        for (int i = 0; i < 256; i++) {
            for (int j = 0; j < 256; j++) {
                for (int k = 0; k < 3; k++) {
                    image[i][j][k] = tmp[i][j][k];
                }
            }
        }
    } else if (a == 4) {
        for (int i = 0; i < 128; i++) {
            for (int j = 0; j < 128; j++) {
                for (int k = 0; k < 3; k++) {
                    tmp[2 * i][2 * j][k] = image[i + 128][j + 128][k];
                    tmp[2 * i][2 * j + 1][k] = image[i + 128][j + 128][k];
                    tmp[2 * i + 1][2 * j][k] = image[i + 128][j + 128][k];
                    tmp[2 * i + 1][(j * 2) + 1][k] = image[i + 128][j + 128][k];
                }
            }
        }
        for (int i = 0; i < 256; i++) {
            for (int j = 0; j < 256; j++) {
                for (int k = 0; k < 3; k++) {
                    image[i][j][k] = tmp[i][j][k];
                }
            }
        }
    }else {
        cout << "Wrong input, please try again\n";
    }
}

void mirror() { // we use this function to mirroring a half of the image by copying the pixels of the desired half to the other side in the opposite direction to give us the mirror effect
    cout << "\n1- Left half\n"
            "2- Right half\n"
            "3- Upper half\n"
            "4- Lower half\n";
    int a;
    cin >> a;
    if (a == 1) {
        for (int i = 0; i < 256; i++) {
            for (int j = 0; j < 128; j++) {
                for (int k = 0; k < 3; k++) {
                    image[i][256 - j][k] = image[i][j][k];
                }
            }
        }
    } else if (a == 2) {
        for (int i = 0; i < 256; i++) {
            for (int j = 0; j < 128; j++) {
                for (int k = 0; k < 3; k++) {
                    image[i][j][k] = image[i][256 - j][k];
                }
            }
        }
    } else if (a == 3) {
        for (int i = 0; i < 128; i++) {
            for (int j = 0; j < 256; j++) {
                for (int k = 0; k < 3; k++) {
                    image[256 - i][j][k] = image[i][j][k];
                }
            }
        }
    } else if (a == 4) {
        for (int i = 0; i < 128; i++) {
            for (int j = 0; j < 256; j++) {
                for (int k = 0; k < 3; k++) {
                    image[i][j][k] = image[256 - i][j][k];
                }
            }
        }
    }else {
        cout << "Wrong input, please try again\n";
    }
}


void crop() { // we use this function to crop any part of the image by entering x and y coordinates to determine a point on the image and then entering the l and width of the desired size to crop out of the image by copying it to another empty image and then overwriting it on the original image again
    int x, y, l, w;
    unsigned char tmp[SIZE][SIZE][RGB];

    cout << "\nPlease enter x,y coordinates of the point to crop around\n";
    cin >> x >> y;
    cout << "Please enter l and width of size of rectangle you wish to keep\n";
    cin >> l >> w;
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            for (int k = 0; k < 3; k++) {
                tmp[i][j][k] = 255;
            }
        }
    }
    for (int i = y; i < l+y; i++) {
        for (int j = x; j < w+x; j++) {
            for (int k = 0; k < 3; k++) {
                tmp[i][j][k] = image[i][j][k];
            }
        }
    }
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            for (int k = 0; k < 3; k++) {
                image[i][j][k] = tmp[i][j][k];
            }
        }
    }
}


void shuffle(){ // to do the shuffle filter we have to change the order of the 4 quarters of the image according to the order the user inputs
    //so the user inputs 4 numbers and we us them to identify which quarter of the image we will copy to another empty image to get the shuffled image
    unsigned char tmp[SIZE][SIZE][RGB];
    cout<<"Please enter order of the quarters to shuffle :";
    int a,b,c,d,ai,aj,bi,bj,ci,cj,di,dj;// i use these variables to make an equation that can identify the number that was inputed by the user and get the correct quarter in the right place by changing the starting position of copying the pixels
    cin>>a;
    cin>>b;
    cin>>c;
    cin>>d;
    if(a==1){
        ai=0;
        aj=0;
    }else if(a==2){
        ai=0;
        aj=128;
    }else if(a==3){
        ai=128;
        aj=0;
    }else if(a==4){
        ai=128;
        aj=128;
    }

    for (int i = 0; i < 128; i++) {
        for (int j = 0; j < 128; j++) {
            for (int k = 0; k < 3; k++) {
                tmp[i][j][k] = image[i + ai][j + aj][k];
            }
        }
    }

    if(b==1){
        bi=0;
        bj=0;
    }else if(b==2){
        bi=0;
        bj=128;
    }else if(b==3){
        bi=128;
        bj=0;
    }else if(b==4){
        bi=128;
        bj=128;
    }
    for (int i = 0; i < 128; i++) {
        for (int j = 128; j < 256; j++) {
            for (int k = 0; k < 3; k++) {
                tmp[i][j][k] = image[i + bi][j - 128 + bj][k];
            }
        }
    }

    if(c==1){
        ci=0;
        cj=0;
    }else if(c==2){
        ci=0;
        cj=128;
    }else if(c==3){
        ci=128;
        cj=0;
    }else if(c==4){
        ci=128;
        cj=128;
    }
    for (int i = 128; i < 256; i++) {
        for (int j = 0; j < 128; j++) {
            for (int k = 0; k < 3; k++) {
                tmp[i][j][k] = image[i - 128 + ci][j + cj][k];
            }
        }
    }
    if(d==1){
        di=0;
        dj=0;
    }else if(d==2){
        di=0;
        dj=128;
    }else if(d==3){
        di=128;
        dj=0;
    }else if(d==4){
        di=128;
        dj=128;
    }
    for (int i = 128; i < 256; i++) {
        for (int j = 128; j < 256; j++) {
            for (int k = 0; k < 3; k++) {
                tmp[i][j][k] = image[i - 128 + di][j - 128 + dj][k];
            }
        }
    }


    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            for (int k = 0; k < 3; k++) {
                image[i][j][k] = tmp[i][j][k];
            }
        }
    }
}

void blur(){ // we use this function to blur an image by getting the average color of the pixel and the 8 pixels surrounding it and adding it to the original pixel to get a blurred effect
    unsigned char tmp[SIZE][SIZE][RGB];
    for (int x = 0; x < 6; x++) {
        for (int i = 0; i < 256; i++) {
            for (int j = 0; j < 256; j++) {
                for (int k = 0; k < 3; k++) {
                    tmp[i][j][k] = (image[i][j][k] + image[i + 1][j + 1][k] + image[i][j + 1][k] + image[i + 1][j][k] +
                                 image[i - 1][j][k] +
                                 image[i][j - 1][k] + image[i - 1][j - 1][k] + image[i - 1][j + 1][k] +
                                 image[i + 1][j - 1][k]) / 9;
                }
            }
        }
        for (int i = 0; i < 256; i++) {
            for (int j = 0; j < 256; j++) {
                for (int k = 0; k < 3; k++) {
                    image[i][j][k] = tmp[i][j][k];
                }
            }
        }
    }
}

void detectedges(){ // we use this function to detect the edges in a picture by calculating the difference between the color of a pixel and the pixels surrounding it and if the difference is large then it is identified as an edge and then colored in black and the pixels around it gets colored in white

    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            for (int k = 0; k < 3; k++) {
                if ((abs(image[i][j][k] - image[i][j + 1][k]) >= 35) ||
                    (abs(image[i][j][k] - image[i + 1][j][k]) >= 35)) {
                    image[i][j][k] = 0;
                } else
                    image[i][j][k] = 255;
            }
        }
    }
}


void shrink() { // we use this function to make an image smaller by calculating the average of a block of pixels and turning them into one pixel so we decrease the number of pixels but still keep the same image but with less details as we lose pixels by doing that
    cout << "\n1- Shrink 1/2\n"
            "2- Shrink 1/3\n"
            "3- Shrink 1/2\n";
    int a;
    cin >> a;
    if (a == 1) {
        int tmp[SIZE][SIZE][RGB];
        for (int i = 0; i < 256; i++) {
            for (int j = 0; j < 256; j++) {
                for (int k = 0; k < 3; k++) {
                    tmp[i][j][k] = 255;

                }
            }
        }
            for (int i = 0; i < 128; i++) {
                for (int j = 0; j < 128; j++) {
                    for (int k = 0; k < 3; k++) {
                        tmp[i][j][k] =
                                (image[2 * i][2 * j][k] + image[2 * i][2 * j + 1][k] + image[2 * i + 1][2 * j][k] +
                                 image[2 * i + 1][(j * 2) + 1][k]) / 4;
                    }
                }
            }
            for (int i = 0; i < 256; i++) {
                for (int j = 0; j < 256; j++) {
                    for (int k = 0; k < 3; k++) {
                        image[i][j][k] = tmp[i][j][k];
                    }
                }
            }
        }


        else if (a == 2) {
            int tmp[SIZE][SIZE][RGB];
            for (int i = 0; i < 256; i++) {
                for (int j = 0; j < 256; j++) {
                    for (int k = 0; k < 3; k++) {
                        tmp[i][j][k] = 255;
                    }
                }
            }
            for (int i = 0; i < 86; i++) {
                for (int j = 0; j < 86; j++) {
                    for (int k = 0; k < 3; k++) {
                        tmp[i][j][k] = (image[3 * i][3 * j][k] + image[3 * i][3 * j + 1][k] + image[3 * i + 1][3 * j][k] +
                                     image[3 * i + 1][(j * 3) + 1][k] + image[3 * i + 1][3 * j][k] +
                                     image[3 * i][3 * j + 2][k] +
                                     image[3 * i + 2][3 * j + 2][k]) / 7;
                    }
                }
            }
            for (int i = 0; i < 256; i++) {
                for (int j = 0; j < 256; j++) {
                    for (int k = 0; k < 3; k++) {
                        image[i][j][k] = tmp[i][j][k];
                    }
                }
            }
        } else if (a == 3) {
            for (int x = 0; x < 2; x++) {
                int tmp[SIZE][SIZE][RGB];
                for (int i = 0; i < 256; i++) {
                    for (int j = 0; j < 256; j++) {
                        for (int k = 0; k < 3; k++) {
                            tmp[i][j][k] = 255;
                        }
                    }
                }
                for (int i = 0; i < 128; i++) {
                    for (int j = 0; j < 128; j++) {
                        for (int k = 0; k < 3; k++) {
                            tmp[i][j][k] =
                                    (image[2 * i][2 * j][k] + image[2 * i][2 * j + 1][k] + image[2 * i + 1][2 * j][k] +
                                     image[2 * i + 1][(j * 2) + 1][k]) / 4;
                        }
                    }
                }
                for (int i = 0; i < 256; i++) {
                    for (int j = 0; j < 256; j++) {
                        for (int k = 0; k < 3; k++) {
                            image[i][j][k] = tmp[i][j][k];
                        }
                    }
                }
            }
        }
    }


void skewhorizontally(){ //we use this function to skew/shift an image to the right by a certain angle inputed by the user edge to edge
    int angle;
    double step , radian , x , unit; // we have to calculate how much of the image will be removed according to the angle and calculate where the image will start from the top on x axis to be skewed with the right angle
    cout<<"Input the angle in degrees : ";cin>>angle;
    angle = 90-angle;
    radian = (tan((M_PI * angle)/180));
    x= 256/(1+1/radian); // to get the shrink base l
    step=SIZE-x; // beginning point on x axis
    unit =step/SIZE;
    unsigned char tmp[SIZE][SIZE][RGB];
    float y= SIZE/x,count; // shrink variables for base editing
    for (int i = 0; i < SIZE; i++) {
        count=0;
        for (int j = 0; j < x; j++) {
            count += y; // adding pixels count
            for (int k = 0; k < 3; k++) {
                tmp[i][j][k] = image[i][int(count)][k];
            }
        }
    }
    for (int i = SIZE-1; i >= 0; i--) {
        for (int j = SIZE-1; j >= 0; j--) {
            for (int k = 0; k < 3; k++) {
                image[i][j][k] = 255; //making a white landscape
            }
        }
    }
    for (int i = 0; i < SIZE; i++) {
        int l=step+x,n=0;
        for (int j = step; j < l; j++) {
            for (int k = 0; k < 3; k++) {
                image[i][j][k] = tmp[i][n][k];
            }
                n++;

        }
        step-=unit;// diagonal shaping by horizontal pixels line
    }

}

void skewvertically() { //we use this function to skew/shift an image upwards by a certain angle inputed by the user edge to edge
    int angle;
    double step, radian, x, unit;
    cout << "Input the angle in degrees : ";
    cin >> angle;
    angle = 90 - angle;
    radian = (tan((angle * M_PI) / 180));
    x = 256 / (1 + 1 / radian); // to get the shrink height l
    step = SIZE - x; //  empty space to skip
    unit = step / SIZE;
    unsigned char tmp[SIZE][SIZE][RGB];
    float y = SIZE / x, count; // shrink variables for height editing
    for (int i = 0; i < SIZE; i++) {
        count = 0;
        for (int j = 0; j < x; j++) {
            count += y; // adding pixels count
            for (int k = 0; k < 3; k++) {
                tmp[j][i][k] = image[int(count)][i][k];
            }
        }
    }
    for (int i = SIZE - 1; i >= 0; i--) {
        for (int j = SIZE - 1; j >= 0; j--) {
            for (int k = 0; k < 3; k++) {
                image[i][j][k] = 255; //declaring white image in background
            }
        }
    }
    for (int i = 0; i < SIZE; i++) {
        int l = step + x, n = 0;
        for (int j = step; j < l; j++) {
            for (int k = 0; k < 3; k++) {
                image[j][i][k] = tmp[n][i][k];
            }
            n++;
        }
        step -= unit;// diagonal shaping by vertical pixels line
    }
}


int main() {
    cout << "Welcome to our image editor the colored RGB version:  \n \n";
    loadImage();
    char choice;
    start:; // we use this command to give the code a looping style so you can keep applying filters on the same image until you exit out of the code
    cout << "\nPlease select a filter to apply or 's' to save or enter '0' to exit :\n"
            "\n"
            "1- Black & White Filter\n"
            "2- Invert Filter\n"
            "3- Merge Filter\n"
            "4- Flip Image\n"
            "5- Darken and Lighten Image\n"
            "6- Rotate Image\n"
            "7- Detect Image Edges\n"
            "8- Enlarge Image\n"
            "9- Shrink Image\n"
            "a- Mirror 1/2 Image\n"
            "b- Shuffle Image\n"
            "c- Blur Image\n"
            "d- Crop Image\n"
            "e- Skew Image horizontally (Right)\n"
            "f- Skew Image vertically (Up)\n"
            "s- Save the image to a file\n"
            "0- Exit\n"
            "\n Pick filter -> ";

    cin >> choice;
    switch (choice) {
        case ('1') :
            blackwhite();
            break;

        case ('2'):
            invert();
            break;

        case ('3'):
            merge();
            break;

        case ('4'):
            flip();
            break;

        case ('5'):
            darkenlighten();
            break;

        case ('6'):
            rotate();
            break;

        case ('7'):
            detectedges();
            break;

        case ('8'):
            enlarge();
            break;

        case ('9'):
            shrink();
            break;

        case ('a'):
            mirror();
            break;

        case ('b'):
            shuffle();
            break;

        case ('c'):
            blur();
            break;

        case ('d'):
            crop();
            break;

        case ('e'):
            skewhorizontally();
            break;

        case ('f'):
            skewvertically();
            break;

        case ('s'):
            saveImage();
            break;

        case ('0'):

            cout << "Edit succesful ,Thank you for using our application <3"; // exit code to close the application after finishing
            break;

        default:
            cout << "Not available , please try again\n"; //if no correct filter choice is inputed this message is displayed
            break;

    }
    if (choice !=
        '0') { // we use this function so we can stop and exit out of the code when we enter the character 0 or keep repeating the code until '0' is inputed
        goto start;
    }
    fast

    return 0;
}

void loadImage() {
    char imageFileName[100];

    cout << "Enter the name of the image you wish to edit: ";
    cin >> imageFileName;

    strcat(imageFileName, ".bmp");
    readRGBBMP(imageFileName, image);

}

void saveImage() {
    char imageFileName[100];

    cout << "Enter the target file name to save your new image: ";
    cin >> imageFileName;

    strcat(imageFileName, ".bmp");
    writeRGBBMP(imageFileName, image);
}


