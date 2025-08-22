# Image Editor

A comprehensive command-line image editing application written in C++ that provides various filters and transformations for BMP images.

## Overview

This image editor is a handmade C++ application that allows users to apply various filters and transformations to BMP images. It works with grayscale images and provides an interactive menu-driven interface for applying different effects.
, The RGB code is the same one as the grey scale code except we add a third dimension to the image with the number 3  : [3]   which represents the degree of the three color levels of RGB Red Green Blue , we can create any color we want by adding certain amounts of each of the three colors
## Features

### Basic Filters
- **Black & White**: Converts image to black and white using average grayscale threshold
- **Invert**: Inverts all colors in the image
- **Darken/Lighten**: Adjusts image brightness by 50%

### Geometric Transformations
- **Flip**: Flips image horizontally or vertically
- **Rotate**: Rotates image by 90°, 180°, or 270°
- **Enlarge**: Enlarges a selected quarter of the image to full size
- **Shrink**: Reduces image size by 1/2, 1/3, or 1/4
- **Crop**: Crops image to a specified rectangular region

### Advanced Effects
- **Merge**: Combines two images by averaging pixel values
- **Mirror**: Creates mirror effect on selected half of image
- **Shuffle**: Rearranges the four quarters of an image in custom order
- **Blur**: Applies blur effect by averaging surrounding pixels
- **Edge Detection**: Identifies and highlights edges in the image
- **Skew**: Applies horizontal or vertical skewing at custom angles

## How It Works

### Image Processing
The application processes images as 2D arrays of grayscale values (0-255), where:
- 0 represents black
- 255 represents white
- Values in between represent different shades of gray

### Core Functions

#### `blackwhite()`
- Calculates average grayscale value of entire image
- Sets pixels above average to white (255), below to black (0)

#### `invert()`
- Subtracts each pixel value from 255 to get opposite color
- Formula: `new_pixel = 255 - original_pixel`

#### `merge()`
- Loads a second image and combines with current image
- Averages corresponding pixel values: `(pixel1 + pixel2) / 2`

#### `flip()`
- **Horizontal**: Swaps pixels across vertical center line
- **Vertical**: Swaps pixels across horizontal center line

#### `rotate()`
- Uses temporary array to store rotated pixel positions
- Applies rotation matrix transformation to pixel coordinates

#### `enlarge()`
- Selects one quarter (128x128) and scales it to full size (256x256)
- Each original pixel becomes a 2x2 block in the enlarged image

#### `shuffle()`
- Divides image into four 128x128 quarters
- Allows user to specify new order for quarters
- Maps each quarter to new position in output image

#### `blur()`
- Applies 3x3 averaging filter 6 times
- Each pixel becomes average of itself and 8 surrounding pixels

#### `detectedges()`
- First converts image to black and white
- Compares each pixel with neighbors
- If difference ≥ 35, marks as edge (black), otherwise white

#### `skewhorizontally()` / `skewvertically()`
- Uses trigonometric calculations to determine pixel displacement
- Applies perspective transformation based on user-specified angle



## Dependencies

- **bmplib**: Custom BMP file handling library
- **Standard C++ libraries**: iostream, fstream, cstring, cmath


### Usage
1. Place BMP images in the application directory
2. Run the executable
3. Enter image filename (without .bmp extension)
4. Select filters from the menu
5. Save edited image with custom filename

## Technical Details

### Image Format
- Supports 256x256 grayscale BMP images
- Uses unsigned char arrays for pixel storage
- RGB support available but not fully implemented

## Limitations

- Fixed image size (256x256 pixels)
- Grayscale only (no color support)
- Some filters may have edge case issues
- Limited error handling for invalid inputs

## Future Improvements

- Support for different image sizes
- Color image processing
- Batch processing capabilities
- GUI interface
- Additional filter algorithms
- Better error handling and validation

## Sample BMP images for testing:
- `crowd.bmp`
- `elephant.bmp`
- `House.bmp`
- `mario.bmp`
- `parots.bmp`
- `photographer.bmp`


