# OpenScanTable

Welcome to the OpenScanTable project – a modular platform for automated 3D scanning and photography. This project enables users to precisely capture objects from various angles by providing a customizable mount suitable for a wide range of recording devices, including the Revopoint Mini V1 3D scanner and webcams.

## Key Features

- **Modular Design:** Adaptable to different recording devices such as 3D scanners, cameras, and more.
- **Controlled Movements:** Manages the distance, tilt, and rotation of the recording device for optimal results.
- **Automated Scans:** Adjustable scan routines with definable rotation and tilt angles, plus repetitions for complete 360° scans.
- **Bluetooth Control:** Connects to a PC as a Bluetooth device for automated commands, e.g., triggering captures.
- **Web Interface:** Controlled via a user-friendly web interface for easy operation and configuration.
- **3D Printable Components:** All files for 3D printing are available in the hardware folder.

## Technical Details

- **Mainboard:** MKS Tinybee with an ESP32.
- **Programming:** Developed using PlatformIO with the Arduino Library.
- **Automatic Distance Control:** A sensor automatically adjusts the scanner's distance to the object.
- **Versatility:** Suitable for single capture scans with RevoScan or photogrammetry projects with automated image captures.

## Additional Hardware

To assemble OpenScanTable, you will need some additional hardware-
For a complete list of parts and specifications, please refer to the [BOM.md](./BOM.md)(Bill of Materials) in this repository.

## Use Cases

- **3D Scanning:** Perfect for detailed 3D models of objects, supported by precise control over capture parameters.
- **Photography:** Ideal for product photography, research and development, where varying perspectives are needed.
- **Photogrammetry:** Enables the creation of 3D models from a series of photographs, including techniques like focus stacking.

## Installation Guide for OpenScanStable

Follow these steps to install and set up your OpenScanStable system. This guide assumes you have a basic understanding of electronics and are familiar with Visual Studio Code and PlatformIO.

### Pre-requisites

- Visual Studio Code installed on your computer.
- Basic knowledge of using Visual Studio Code and PlatformIO.
- A MKS TinyBee board or a compatible board.

### Installation Steps

1. **Download and Install PlatformIO Plugin in Visual Studio Code**

   - Open Visual Studio Code.
   - Navigate to the Extensions view by clicking on the square icon on the sidebar or pressing `Ctrl+Shift+X`.
   - Search for "PlatformIO IDE".
   - Click on "Install" to install the PlatformIO IDE extension.

2. **Clone the Repository and Open the Project**

   - Use Git to clone the repository to your local computer. If you're not familiar with Git, you can find numerous guides online to get started.
   - Once cloned, open the folder in Visual Studio Code by selecting `File > Open Folder` and navigating to the cloned project folder.

3. **Prepare and Upload the Firmware to the MKS Tinybee Board**

   - In the PlatformIO sidebar, navigate to the project environment for the MKS Tinybee board.
   - **Build File System Image**
     - First, you need to build the file system image that will be used by the ESP32. This contains the web interface and other necessary files.
     - Find and click on the "Build Filesystem Image" task to compile the image.
   - **Upload File System Image**
     - After building the file system image, upload it to your board by clicking on the "Upload Filesystem Image" task.
   - **Build**
     - Next, compile the main firmware by selecting the "Build" task. This compiles all the source code into a binary file.
   - **Upload**
     - Once the build process is complete, upload the firmware to your MKS Tinybee board by selecting the "Upload" task.

4. **Boot the Mainboard**

   - After uploading the firmware, reboot the MKS Tinybee board to start the newly uploaded software.

5. **Connect Laptop/PC to ESP32 via Bluetooth (For Keyboard Input)**

   - Enable Bluetooth on your laptop or PC.
   - Search for available Bluetooth devices and connect to the ESP32 module named usually as `ESP32 Keyboard` or a similar name provided in your project documentation.

6. **Connect to OpenScanStable via WiFi for the Interface**

   - On your computer or a WiFi-enabled device, search for the WiFi network named "OpenScanTable".
   - Connect to this network using the password provided in your project documentation.
   - Once connected, you can access the web interface by navigating to the IP address specified in the project documentation.

7. **Perform Motor Test and Adjust Drivers**

   - It's crucial to perform a motor test to ensure everything is working correctly.
   - Access the motor test feature through the web interface. Follow the instructions provided to initiate the test.
   - While testing, adjust the motor drivers to supply as much current as needed but as little as possible to prevent overheating and ensure optimal performance.

## Preview

![OpenScanTable in action](path-to-gif)

This GIF showcases the OpenScanTable device in operation, demonstrating its versatility and ease of use.

## Contributing

The OpenScanTable project thrives on community contribution. We encourage anyone interested to contribute, whether it's through code contributions, creating 3D printing files, or developing new features. Forks and pull requests are warmly welcomed!

## License

This project is open source under an MIT license. For more information, see the LICENSE file.

## Contact

For questions, suggestions, or contributions, please create an issue in the GitHub repository or contact us directly.

We look forward to your contribution and are excited to see what you will create with OpenScanTable!
