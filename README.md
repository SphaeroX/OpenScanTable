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

## Use Cases

- **3D Scanning:** Perfect for detailed 3D models of objects, supported by precise control over capture parameters.
- **Photography:** Ideal for product photography, research and development, where varying perspectives are needed.
- **Photogrammetry:** Enables the creation of 3D models from a series of photographs, including techniques like focus stacking.

## Getting Started

### Prerequisites

- MKS Tinybee board with ESP32
- Compatible recording devices (3D scanner, camera, etc.)
- PlatformIO with Arduino Library

### Installation

1. Clone the repository to your local computer.
2. Open the project in PlatformIO.
3. Upload the code to your MKS Tinybee board.
4. Connect your recording device to the mount.
5. Launch the web interface to control the scanning routines.

## Contributing

The OpenScanTable project thrives on community contribution. We encourage anyone interested to contribute, whether it's through code contributions, creating 3D printing files, or developing new features. Forks and pull requests are warmly welcomed!

## License

This project is open source under an MIT license. For more information, see the LICENSE file.

## Contact

For questions, suggestions, or contributions, please create an issue in the GitHub repository or contact us directly.

We look forward to your contribution and are excited to see what you will create with OpenScanTable!
