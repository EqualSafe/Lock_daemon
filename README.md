# Lock_daemon
Daemon responsible for lock/unlock commands and maintaining the statuses of multiple access points.

## Getting Started

To use this project, follow these steps after cloning the repository:

### Prepare Certificates

1. Inside the `src` folder of this project, create a new folder named `certs`.
2. Place all necessary AWS certificates inside the `certs` folder. These are required for AWS IoT integration.

### Build Instructions

Follow these commands to build the project using Docker:

1. Pull the Docker image:
    ```bash
    docker pull fjarr/allsafe_deadlock_builder:latest
    ```

2. Start the Docker container and access its shell:
    ```bash
    docker run -it -v ${PWD}:/project --name lock_build fjarr/allsafe_deadlock_builder:latest bash
    ```

3. Once inside the container's shell, navigate to the project directory (if you're not already there), and then run these commands:
    ```bash
    mkdir build
    cd build
    cmake .. -DCMAKE_INSTALL_PREFIX=/aws-iot-device-sdk-cpp-v2/
    make
    ```
    This compiles the project and generates the `lock_sys` binary within the `build` directory.

The binary should be in the `build` directory and named `./lock_sys`.

### Running the Project

After building, you can run `./lock_sys` to start the daemon.
