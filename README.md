# Image Analyzer (Qt C++)

An image analysis application that allows users to segment objects by color, calculate their area, and determine boundary (perimeter) coordinates. This project was developed as a technical task using the **Qt** framework.



Key Features

* **Image Loading**: Supports `.png`, `.jpg`, and `.bmp` formats.
* **Interactive Segmentation**: Select an image segment with a single mouse click on any area of the picture.
* **Flood Fill Algorithm**: Efficient stack-based segmentation (non-recursive) with color tolerance support.
* **Data Analysis**:
    * Calculates the area of the selected segment as a percentage of the total image.
    * Identifies the coordinates of pixels forming the boundary (perimeter).
    * Counts the total number of pixels within the segment.
* **Visual Highlighting**: Toggleable red overlay for the selected object to provide better visual feedback.

## Project Architecture

The project is divided into logical blocks to ensure clean code separation:
* **`MainWindow`**: Manages the User Interface (GUI), mouse event handling, and result display.
* **`ImageProcessor`**: Contains the core image processing business logic and the segmentation algorithm.
* **`SegmentationResult`**: A data structure used to pass analysis results between the logic and the interface.

## System Requirements

* **C++17** or higher.
* **CMake 3.16+**.
* **Qt 5** or **Qt 6** (Widgets).

