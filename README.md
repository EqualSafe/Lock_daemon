# Lock_daemon
Daemon responsible for lock/unlock commands and maintaining the statuses of multiple access points.

## Getting Started

To use this project, follow these steps after cloning the repository:

### Prepare Certificates

1. Inside the `src` folder of this project, create a new folder named `certs`.
2. Place all necessary AWS certificates inside the `certs` folder. These are required for AWS IoT integration.

### Build Instructions (DEV)

You can build the project using Docker by following these steps:

1. Pull the Docker image:
    ```bash
    docker pull fjarr/allsafe_deadlock_builder:latest
    ```

2. Start the Docker container and access its shell:
    ```bash
    docker run --privileged -it -v ${PWD}:/project fjarr/allsafe_deadlock_builder:latest bash
    ```

3. Once inside the container's shell, you have two options to compile the project:

    **Option A: Using the `build_project.sh` Script**

    If a `build_project.sh` script is available in your project directory, simply execute it:
    ```bash
    ./build_project.sh
    ```
    This script automatically handles the creation of the build directory, runs CMake with the specified installation prefix, and compiles the project.

    **Option B: Manually Running Build Commands**

    If you prefer to manually compile the project or the script is not available, run these commands:
    ```bash
    mkdir build
    cd build
    cmake .. -DCMAKE_INSTALL_PREFIX=/aws-iot-device-sdk-cpp-v2/
    make
    ```
    This compiles the project and generates the `lock_sys` binary within the `build` directory.

The binary will be located in the `build` directory and named `./lock_sys`.

### Running the Project (DEV)

After building, you can run `./lock_sys` to start the daemon.

### Deployment Instructions (PROD)

To deploy the `lock_daemon`, use the following steps:

1. Pull the Docker image:
    ```bash
    docker pull fjarr/lock_daemon:latest
    ```

2. Deploy the service using systemd:

    - Copy the content of the file in /rootfs/etc/systemd/system/lock_daemon.service to /etc/systemd/system/lock_daemon.service
    you can use:
    ```
    sudo nano /etc/systemd/system/lock_daemon.service
    ```


3. Reload systemd to recognize the new service:
    ```bash
    sudo systemctl daemon-reload
    ```

4. Enable the service to start on boot, and start the service:
    ```bash
    sudo systemctl enable lock_daemon.service
    sudo systemctl start lock_daemon.service
    ```

5. Verify the service is running correctly:
    ```bash
    sudo systemctl status lock_daemon.service
    ```