# sdl-image-slicer
Slice Images by given parameters evenly

## Dependencies
* libsdl2-dev 
* libsdl2-image-dev

## Installation
Just run the build script
```bash
./build.sh
```
You may want to copy the binary to your local bin directory.

## Usage
```bash
# sdl-slicer "/path/to/image" <h-slice-count> <v-slice-count>
sdl-slicer "some-image.png" 2 2
# This will split the image evenly into 4 new images which will be saved
# as "some-image-0.png" through "some-image-3.png" respectively, starting
# from the upper left to the lower right.
```
