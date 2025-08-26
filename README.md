# C++ Winsock Network Library

This project is a foundational network programming library built with the C++ language and the Winsock API. It provides a simple and clean interface for developing network applications using both TCP and UDP protocols. The library is designed to be a starting point for building more complex network-enabled software.

---

## Key Features

- **TCP Sockets:** Provides reliable, connection-oriented communication with dedicated classes for clients and servers.
- **UDP Sockets:** Enables fast, connectionless communication for scenarios where low latency is critical.
- **Packet Management:** A robust `Packet` class for serializing and deserializing data, making it easy to send and receive structured information.
- **Endpoint Handling:** Simple `Endpoint` and `DNS_RESOLVER` classes to manage IP addresses, ports, and hostname resolution.
- **Error Management:** Includes custom `NetworkError` classes to handle network-specific errors gracefully and efficiently.

---

## Getting Started

To get a local copy of the project up and running, follow these simple steps.

### Prerequisites

- A C++ compiler (Visual Studio 2022 is recommended).
- Windows SDK.

### Building the Project

1.  Clone the repository or download the source code as a ZIP file.
2.  Open the `Winsock.sln` file with Visual Studio.
3.  Build the solution (`Ctrl + Shift + B` or `Build -> Build Solution`).

---

## Project Status and Roadmap

This project is currently in the early stages of development. While the core functionality is in place, there may be bugs, missing features, and areas for optimization. Your feedback and contributions are highly appreciated!

### Known Issues & Future Work
-   [Add a list here] - For example:
    -   IPv6 support is not yet implemented.
    -   Asynchronous I/O (I/O completion ports) is not yet integrated for high-performance applications.
    -   Need to add unit tests for better code reliability.
    -   Further bug fixes and performance improvements.

---

## How to Contribute

We welcome contributions from the community! If you'd like to help, please feel free to:

1.  Fork the repository.
2.  Create a new branch (`git checkout -b feature/your-feature`).
3.  Make your changes.
4.  Commit your changes (`git commit -m 'Add new feature'`).
5.  Push to the branch (`git push origin feature/your-feature`).
6.  Create a Pull Request.

---

## License

This project is licensed under the MIT License - see the `LICENSE` file for details.
