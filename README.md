# Manipulating-PGM-Portable-Gray-Map-images
# PGM Image Processor

This project provides a `PGMImage` class for loading, saving, and manipulating PGM (Portable Gray Map) images. It includes functionalities such as creating a negative image, applying mean and median filters, rotating, flipping, resizing, and cropping the image.

## Features

1. **LoadImage**: Loads a PGM image from a file.
2. **SaveImage**: Saves the current image to a file.
3. **Create_Negative**: Creates a negative of the current image.
4. **Mean_Filter**: Applies a mean filter to the image.
5. **Median_Filter**: Applies a median filter to the image.
6. **Rotate**: Rotates the image by an arbitrary angle.
7. **RotateClockwise**: Rotates the image 90 degrees clockwise.
8. **RotateCounterClockwise**: Rotates the image 90 degrees counter-clockwise.
9. **FlipHorizontal**: Flips the image horizontally.
10. **FlipVertical**: Flips the image vertically.
11. **Resize**: Resizes the image to new dimensions.
12. **CropImage**: Crops the image to specified dimensions.
13. **Savefliphorizontal**: Saves the horizontally flipped image.
14. **Saveflipvertical**: Saves the vertically flipped image.
15. **Savecounterclock**: Saves the counter-clockwise rotated image.

## Code

The main code is in `pgm_editor.cpp`.

## Compilation and Execution

### Compilation

To compile the program, use a C++ compiler like g++:

```sh
g++ -o pgm_editor pgm_editor.cpp

