#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;

#define fast ios_base::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);

unsigned char image[SIZE][SIZE];
unsigned char iRGB[SIZE][SIZE][RGB];

void loadImage();
void saveImage();

void blackwhite() {
    int sum = 0;
    int avg;
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            sum += image[i][j];
        }
    }
    avg = (sum / 256) / 255;
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            if (image[i][j] >= avg)
                image[i][j] = 255;
            else
                image[i][j] = 0;
        }
    }
}

void invert() {
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            image[i][j] = 255 - image[i][j];
        }
    }
}

void merge() {
    unsigned char tmp[SIZE][SIZE];
    char imageFileName[100];
    cout << "Enter the name of the image you wish to merge: ";
    cin >> imageFileName;
    strcat(imageFileName, ".bmp");
    readGSBMP(imageFileName, tmp);
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            image[i][j] = (image[i][j] + tmp[i][j]) / 2;
        }
    }
}

void flip() {
    cout << "\n1- Flip horizontally\n"
            "2- Flip vertically\n";
    int a;
    int x;
    cin >> a;
    if (a == 1) {
        for (int i = 0; i < 128; i++) {
            for (int j = 0; j < 256; j++) {
                x = image[i][j];
                image[i][j] = image[256 - i][j];
                image[256 - i][j] = x;
            }
        }
    } else if (a == 2) {
        for (int i = 0; i < 256; i++) {
            for (int j = 0; j < 128; j++) {
                x = image[i][j];
                image[i][j] = image[i][256 - j];
                image[i][256 - j] = x;
            }
        }
    } else {
        cout << "Wrong input, please try again\n";
    }
}

void darkenlighten() {
    cout << "\n1- Darken\n"
            "2- Lighten\n";
    int v;
    cin >> v;
    if (v == 1) {
        for (int i = 0; i < 256; i++) {
            for (int j = 0; j < 256; j++) {
                image[i][j] /= 2;
            }
        }
    } else if (v == 2) {
        for (int i = 0; i < 256; i++) {
            for (int j = 0; j < 256; j++) {
                image[i][j] += (255 - image[i][j]) / 2;
            }
        }
    } else {
        cout << "Wrong input, please try again\n";
    }
}

void rotate() {
    cout << "\n1- Rotate 90 degrees\n"
            "2- Rotate 180 degrees\n"
            "3- Rotate 270 degrees\n";
    unsigned char tmp[SIZE][SIZE];
    int a;
    cin >> a;
    if (a == 1) {
        for (int i = 0; i < 3; i++) {
            for (int i = 0; i < 256; i++) {
                for (int j = 0; j < 256; j++) {
                    tmp[j][256 - i] = image[i][j];
                }
            }
            for (int i = 0; i < 256; i++) {
                for (int j = 0; j < 256; j++) {
                    image[i][j] = tmp[i][j];
                }
            }
        }
    } else if (a == 2) {
        for (int i = 0; i < 2; i++) {
            for (int i = 0; i < 256; i++) {
                for (int j = 0; j < 256; j++) {
                    tmp[j][256 - i] = image[i][j];
                }
            }
            for (int i = 0; i < 256; i++) {
                for (int j = 0; j < 256; j++) {
                    image[i][j] = tmp[i][j];
                }
            }
        }
    } else if (a == 3) {
        for (int i = 0; i < 256; i++) {
            for (int j = 0; j < 256; j++) {
                tmp[j][256 - i] = image[i][j];
            }
        }
        for (int i = 0; i < 256; i++) {
            for (int j = 0; j < 256; j++) {
                image[i][j] = tmp[i][j];
            }
        }
    } else {
        cout << "Wrong input, please try again\n";
    }
}

void enlarge() {
    cout << "\n1- Quarter 1\n"
            "2- Quarter 2\n"
            "3- Quarter 3\n"
            "4- quarter 4\n";
    unsigned char tmp[SIZE][SIZE];
    int a;
    cin >> a;
    if (a == 1) {
        for (int i = 0; i < 128; i++) {
            for (int j = 0; j < 128; j++) {
                tmp[2 * i][2 * j] = image[i][j];
                tmp[2 * i][2 * j + 1] = image[i][j];
                tmp[2 * i + 1][2 * j] = image[i][j];
                tmp[2 * i + 1][(j * 2) + 1] = image[i][j];
            }
        }
        for (int i = 0; i < 256; i++) {
            for (int j = 0; j < 256; j++) {
                image[i][j] = tmp[i][j];
            }
        }
    } else if (a == 2) {
        for (int i = 0; i < 128; i++) {
            for (int j = 0; j < 128; j++) {
                tmp[2 * i][2 * j] = image[i][j + 128];
                tmp[2 * i][2 * j + 1] = image[i][j + 128];
                tmp[2 * i + 1][2 * j] = image[i][j + 128];
                tmp[2 * i + 1][(j * 2) + 1] = image[i][j + 128];
            }
        }
        for (int i = 0; i < 256; i++) {
            for (int j = 0; j < 256; j++) {
                image[i][j] = tmp[i][j];
            }
        }
    } else if (a == 3) {
        for (int i = 0; i < 128; i++) {
            for (int j = 0; j < 128; j++) {
                tmp[2 * i][2 * j] = image[i + 128][j];
                tmp[2 * i][2 * j + 1] = image[i + 128][j];
                tmp[2 * i + 1][2 * j] = image[i + 128][j];
                tmp[2 * i + 1][(j * 2) + 1] = image[i + 128][j];
            }
        }
        for (int i = 0; i < 256; i++) {
            for (int j = 0; j < 256; j++) {
                image[i][j] = tmp[i][j];
            }
        }
    } else if (a == 4) {
        for (int i = 0; i < 128; i++) {
            for (int j = 0; j < 128; j++) {
                tmp[2 * i][2 * j] = image[i + 128][j + 128];
                tmp[2 * i][2 * j + 1] = image[i + 128][j + 128];
                tmp[2 * i + 1][2 * j] = image[i + 128][j + 128];
                tmp[2 * i + 1][(j * 2) + 1] = image[i + 128][j + 128];
            }
        }
        for (int i = 0; i < 256; i++) {
            for (int j = 0; j < 256; j++) {
                image[i][j] = tmp[i][j];
            }
        }
    } else {
        cout << "Wrong input, please try again\n";
    }
}

void mirror() {
    cout << "\n1- Left half\n"
            "2- Right half\n"
            "3- Upper half\n"
            "4- Lower half\n";
    int a;
    cin >> a;
    if (a == 1) {
        for (int i = 0; i < 256; i++) {
            for (int j = 0; j < 128; j++) {
                image[i][256 - j] = image[i][j];
            }
        }
    } else if (a == 2) {
        for (int i = 0; i < 256; i++) {
            for (int j = 0; j < 128; j++) {
                image[i][j] = image[i][256 - j];
            }
        }
    } else if (a == 3) {
        for (int i = 0; i < 128; i++) {
            for (int j = 0; j < 256; j++) {
                image[256 - i][j] = image[i][j];
            }
        }
    } else if (a == 4) {
        for (int i = 0; i < 128; i++) {
            for (int j = 0; j < 256; j++) {
                image[i][j] = image[256 - i][j];
            }
        }
    } else {
        cout << "Wrong input, please try again\n";
    }
}

void crop() {
    int x, y, l, w;
    unsigned char tmp[SIZE][SIZE];

    cout << "\nPlease enter x,y coordinates of the point to crop around\n";
    cin >> x >> y;
    cout << "Please enter l and width of size of rectangle you wish to keep\n";
    cin >> l >> w;
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            tmp[i][j] = 255;
        }
    }
    for (int i = y; i < l + y; i++) {
        for (int j = x; j < w + x; j++) {
            tmp[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            image[i][j] = tmp[i][j];
        }
    }
}

void shuffle() {
    unsigned char tmp[SIZE][SIZE];
    cout << "Please enter order of the quarters to shuffle :";
    int a, b, c, d, ai, aj, bi, bj, ci, cj, di, dj;
    cin >> a;
    cin >> b;
    cin >> c;
    cin >> d;
    if (a == 1) {
        ai = 0;
        aj = 0;
    } else if (a == 2) {
        ai = 0;
        aj = 128;
    } else if (a == 3) {
        ai = 128;
        aj = 0;
    } else if (a == 4) {
        ai = 128;
        aj = 128;
    }

    for (int i = 0; i < 128; i++) {
        for (int j = 0; j < 128; j++) {
            tmp[i][j] = image[i + ai][j + aj];
        }
    }

    if (b == 1) {
        bi = 0;
        bj = 0;
    } else if (b == 2) {
        bi = 0;
        bj = 128;
    } else if (b == 3) {
        bi = 128;
        bj = 0;
    } else if (b == 4) {
        bi = 128;
        bj = 128;
    }
    for (int i = 0; i < 128; i++) {
        for (int j = 128; j < 256; j++) {
            tmp[i][j] = image[i + bi][j - 128 + bj];
        }
    }

    if (c == 1) {
        ci = 0;
        cj = 0;
    } else if (c == 2) {
        ci = 0;
        cj = 128;
    } else if (c == 3) {
        ci = 128;
        cj = 0;
    } else if (c == 4) {
        ci = 128;
        cj = 128;
    }
    for (int i = 128; i < 256; i++) {
        for (int j = 0; j < 128; j++) {
            tmp[i][j] = image[i - 128 + ci][j + cj];
        }
    }
    if (d == 1) {
        di = 0;
        dj = 0;
    } else if (d == 2) {
        di = 0;
        dj = 128;
    } else if (d == 3) {
        di = 128;
        dj = 0;
    } else if (d == 4) {
        di = 128;
        dj = 128;
    }
    for (int i = 128; i < 256; i++) {
        for (int j = 128; j < 256; j++) {
            tmp[i][j] = image[i - 128 + di][j - 128 + dj];
        }
    }

    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            image[i][j] = tmp[i][j];
        }
    }
}

void blur() {
    unsigned char tmp[SIZE][SIZE];
    for (int x = 0; x < 6; x++) {
        for (int i = 0; i < 256; i++) {
            for (int j = 0; j < 256; j++) {
                tmp[i][j] = (image[i][j] + image[i + 1][j + 1] + image[i][j + 1] + image[i + 1][j] + image[i - 1][j] +
                             image[i][j - 1] + image[i - 1][j - 1] + image[i - 1][j + 1] + image[i + 1][j - 1]) / 9;
            }
        }
        for (int i = 0; i < 256; i++) {
            for (int j = 0; j < 256; j++) {
                image[i][j] = tmp[i][j];
            }
        }
    }
}

void detectedges() {
    blackwhite();
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            if ((abs(image[i][j] - image[i][j + 1]) >= 35) || (abs(image[i][j] - image[i + 1][j]) >= 35)) {
                image[i][j] = 0;
            } else
                image[i][j] = 250;
        }
    }
}

void shrink() {
    cout << "\n1- Shrink 1/2\n"
            "2- Shrink 1/3\n"
            "3- Shrink 1/2\n";
    int a;
    cin >> a;
    if (a == 1) {
        int tmp[SIZE][SIZE];
        for (int i = 0; i < 256; i++) {
            for (int j = 0; j < 256; j++) {
                tmp[i][j] = 255;
            }
        }
        for (int i = 0; i < 128; i++) {
            for (int j = 0; j < 128; j++) {
                tmp[i][j] = (image[2 * i][2 * j] + image[2 * i][2 * j + 1] + image[2 * i + 1][2 * j] +
                              image[2 * i + 1][(j * 2) + 1]) / 4;
            }
        }
        for (int i = 0; i < 256; i++) {
            for (int j = 0; j < 256; j++) {
                image[i][j] = tmp[i][j];
            }
        }
    } else if (a == 2) {
        int tmp[SIZE][SIZE];
        for (int i = 0; i < 256; i++) {
            for (int j = 0; j < 256; j++) {
                tmp[i][j] = 255;
            }
        }
        for (int i = 0; i < 86; i++) {
            for (int j = 0; j < 86; j++) {
                tmp[i][j] = (image[3 * i][3 * j] + image[3 * i][3 * j + 1] + image[3 * i + 1][3 * j] + image[3 * i + 1][(j * 3) + 1] + image[3 * i + 1][3 * j] + image[3 * i][3 * j + 2] + image[3 * i + 2][3 * j + 2]) / 7;
            }
        }
        for (int i = 0; i < 256; i++) {
            for (int j = 0; j < 256; j++) {
                image[i][j] = tmp[i][j];
            }
        }
    } else if (a == 3) {
        for (int x = 0; x < 2; x++) {
            int tmp[SIZE][SIZE];
            for (int i = 0; i < 256; i++) {
                for (int j = 0; j < 256; j++) {
                    tmp[i][j] = 255;
                }
            }
            for (int i = 0; i < 128; i++) {
                for (int j = 0; j < 128; j++) {
                    tmp[i][j] = (image[2 * i][2 * j] + image[2 * i][2 * j + 1] + image[2 * i + 1][2 * j] +
                                  image[2 * i + 1][(j * 2) + 1]) / 4;
                }
            }
            for (int i = 0; i < 256; i++) {
                for (int j = 0; j < 256; j++) {
                    image[i][j] = tmp[i][j];
                }
            }
        }
    }
}

void skewhorizontally() {
    int angle;
    double step, radianian, x, unit;
    cout << "Input the angle in degrees : ";
    cin >> angle;
    angle = 90 - angle;
    radianian = (tan((M_PI * angle) / 180));
    x = 256 / (1 + 1 / radianian);
    step = SIZE - x;
    unit = step / SIZE;
    unsigned char tmp[SIZE][SIZE];
    float y = SIZE / x, count;
    for (int i = 0; i < SIZE; i++) {
        count = 0;
        for (int j = 0; j < x; j++) {
            count += y;
            tmp[i][j] = image[i][int(count)];
        }
    }
    for (int i = SIZE - 1; i >= 0; i--) {
        for (int j = SIZE - 1; j >= 0; j--) {
            image[i][j] = 255;
        }
    }
    for (int i = 0; i < SIZE; i++) {
        int l = step + x, n = 0;
        for (int j = step; j < l; j++) {
            image[i][j] = tmp[i][n];
            n++;
        }
        step -= unit;
    }
}

void skewvertically() {
    int angle;
    double step, radian, x, unit;
    cout << "Input the angle in degrees : ";
    cin >> angle;
    angle = 90 - angle;
    radian = (tan((angle * M_PI) / 180));
    x = 256 / (1 + 1 / radian);
    step = SIZE - x;
    unit = step / SIZE;
    unsigned char tmp[SIZE][SIZE];
    float y = SIZE / x, count;
    for (int i = 0; i < SIZE; i++) {
        count = 0;
        for (int j = 0; j < x; j++) {
            count += y;
            tmp[j][i] = image[int(count)][i];
        }
    }
    for (int i = SIZE - 1; i >= 0; i--) {
        for (int j = SIZE - 1; j >= 0; j--) {
            image[i][j] = 255;
        }
    }
    for (int i = 0; i < SIZE; i++) {
        int l = step + x, n = 0;
        for (int j = step; j < l; j++) {
            image[j][i] = tmp[n][i];
            n++;
        }
        step -= unit;
    }
}

int main() {
    cout << "Welcome to our image editor: \n \n";
    loadImage();
    char choice;
start:
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
        case ('1'):
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
            cout << "Edit successful, Thank you for using our application <3";
            break;
        default:
            cout << "Not available, please try again\n";
            break;
    }
    if (choice != '0') {
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
    readGSBMP(imageFileName, image);
}

void saveImage() {
    char imageFileName[100];
    cout << "Enter the target file name to save your new image: ";
    cin >> imageFileName;
    strcat(imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
}

