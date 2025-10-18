# YouTube Video/Playlist Downloader

A powerful and user-friendly Python script designed to download YouTube videos or entire playlists in your preferred quality, directly to your computer. This cross-platform tool is compatible with Windows, Linux, and macOS, making it accessible for all users.

## Table of Contents

1. [Features](#features)
2. [Dependencies](#dependencies)
3. [Installation Guide](#installation-guide)
    - [1. Clone the Repository](#1-clone-the-repository)
    - [2. Using the Makefile (Recommended)](#2-using-the-makefile-recommended)
    - [3. Manual Setup](#3-manual-setup)
4. [Usage](#usage)
5. [Examples](#examples)
6. [Troubleshooting](#troubleshooting)
7. [License](#license)
8. [Contribution](#contribution)
9. [Project Structure](#project-structure)
10. [Additional Resources](#additional-resources)

---

## Features

-   **Download Single Videos**: Easily download individual YouTube videos by providing their URL.
-   **Download Playlists**: Download entire YouTube playlists or choose specific videos from a playlist.
-   **Choose Video Quality**: Select from multiple video quality options (Best, High, Medium, Low).
-   **Cross-Platform Compatibility**: Works seamlessly on Windows, Linux, and macOS.
-   **Automated Setup**: Use a Makefile to automate environment setup and dependency installation.
-   **Virtual Environment Support**: Ensures project dependencies are isolated and managed efficiently.

---

## Dependencies

To run this script, the following dependencies are required:

1. **Python 3.x**
    - Ensure Python 3 is installed on your system.
    - [Download Python](https://www.python.org/downloads/)
2. **yt-dlp**
    - A command-line tool to download videos from YouTube and other sites.
3. **ffmpeg**
    - A multimedia framework for handling video, audio, and other multimedia files and streams.

---

## Installation Guide

### 1. Clone the Repository

First, clone this repository to your local machine using Git:

```bash
git clone https://github.com/orcalinux/youtube_downloader.git
cd youtube_downloader
```

### 2. Using the Makefile (Recommended)

A `Makefile` is provided to automate the setup process, including creating a virtual environment, installing dependencies, and running the application.

#### **a. Ensure `make` is Installed**

-   **Linux/macOS**: `make` is typically pre-installed. Verify by running:

    ```bash
    make --version
    ```

-   **Windows**: Install [Make for Windows](http://gnuwin32.sourceforge.net/packages/make.htm) or use [Windows Subsystem for Linux (WSL)](https://docs.microsoft.com/en-us/windows/wsl/install) to access Unix-like tools.

#### **b. Set Up the Virtual Environment and Install Dependencies**

Run the following command in the project directory:

```bash
make install
```

**What This Does:**

-   Creates a virtual environment named `venv`.
-   Installs Python dependencies listed in `requirements.txt`.
-   Checks if `ffmpeg` is installed on your system.

_If `ffmpeg` is not installed, follow the instructions in [Manual Setup](#3-manual-setup) to install it._

#### **c. Run the Application**

After installation, execute the script using:

```bash
make run
```

**What This Does:**

-   Activates the virtual environment.
-   Runs `app.py` within the virtual environment.

#### **d. Clean the Project**

To remove the virtual environment and clean up dependencies, use:

```bash
make clean
```

---

### 3. Manual Setup

If you prefer not to use the `Makefile`, follow these steps to set up the project manually.

#### **a. Create a Virtual Environment**

Navigate to the project directory and create a virtual environment named `venv`:

```bash
python3 -m venv venv
```

#### **b. Activate the Virtual Environment**

-   **Linux/macOS:**

    ```bash
    source venv/bin/activate
    ```

-   **Windows:**

    ```bash
    venv\Scripts\activate
    ```

#### **c. Install Python Dependencies**

With the virtual environment activated, install the required Python packages:

```bash
pip install --upgrade pip
pip install -r requirements.txt
```

#### **d. Install `ffmpeg`**

Ensure `ffmpeg` is installed on your system.

-   **Windows:**

    1. Download the latest `ffmpeg` release from [ffmpeg.org](https://ffmpeg.org/download.html).
    2. Extract the downloaded archive.
    3. Add the `bin` directory of `ffmpeg` to your system's PATH.

-   **Linux:**

    ```bash
    sudo apt-get update
    sudo apt-get install ffmpeg
    ```

-   **macOS (Using Homebrew):**

    ```bash
    brew install ffmpeg
    ```

---

## Usage

After setting up the environment and installing dependencies, you can run the YouTube downloader script.

### **Run the Script**

Activate the virtual environment (if not already activated):

-   **Linux/macOS:**

    ```bash
    source venv/bin/activate
    ```

-   **Windows:**

    ```bash
    venv\Scripts\activate
    ```

Run the application:

```bash
python app.py
```

### **Follow the Prompts**

1. **Enter the URL**: Provide the URL of the YouTube video or playlist you wish to download.
2. **Select Playlist or Single Video**: If the URL is a playlist, choose whether to download the entire playlist or specific videos.
3. **Choose Quality**: Select your preferred video quality (Best, High, Medium, Low).
4. **Download**: The script will download the selected video(s) and save them to your `Downloads` folder.

---

## Examples

### Example 1: Downloading a Single Video

```bash
python app.py
```

-   **Input**:
    -   **URL**: `https://youtu.be/W13gbCLVU40`
    -   **Quality**: `2` (High 1080p)
-   **Output**: The video is downloaded and saved to your `Downloads` folder.

### Example 2: Downloading an Entire Playlist

```bash
python app.py
```

-   **Input**:
    -   **URL**: `https://www.youtube.com/playlist?list=PLxwbQuwnqw4fFmABIFU_xFP-Sp5DKW-b2`
    -   **Download Entire Playlist**: `y`
    -   **Quality**: `1` (Best quality)
-   **Output**: All videos in the playlist are downloaded to your `Downloads` folder.

### Example 3: Downloading Specific Videos from a Playlist

```bash
python app.py
```

-   **Input**:
    -   **URL**: `https://www.youtube.com/playlist?list=PLxwbQuwnqw4fFmABIFU_xFP-Sp5DKW-b2`
    -   **Download Entire Playlist**: `n`
    -   **Select Videos**: `1, 3, 5`
    -   **Quality**: `3` (Medium quality)
-   **Output**: Only videos 1, 3, and 5 from the playlist are downloaded to your `Downloads` folder.

---

## Troubleshooting

-   **Network Errors**: Ensure your internet connection is stable.
-   **Permission Issues**: Make sure you have write permissions to the `Downloads` directory.
-   **Missing Dependencies**: Verify that `yt-dlp` and `ffmpeg` are installed correctly and accessible via your system's PATH.
-   **ModuleNotFoundError**: If you encounter `ModuleNotFoundError: No module named 'yt_dlp'`, ensure you've installed `yt-dlp` within your virtual environment:

    ```bash
    pip install yt-dlp
    ```

-   **ffmpeg Not Found**: If the script cannot locate `ffmpeg`, ensure it is installed and added to your system's PATH.

---

## License

This script is provided under the MIT License. You are free to use, modify, and distribute this script. See the [LICENSE](LICENSE) file for more details.

---

## Contribution

Contributions are welcome! If you encounter any issues or have suggestions for improvements, feel free to submit an issue or open a pull request on the [GitHub repository](https://github.com/orcalinux/youtube_downloader).

---

## Project Structure

```
.
├── app.py
├── LICENSE
├── Makefile
├── README.md
└── requirements.txt
```

-   **app.py**: The main Python script for downloading YouTube videos and playlists.
-   **LICENSE**: The MIT License file.
-   **Makefile**: Automates environment setup, dependency installation, and running the application.
-   **README.md**: Project documentation.
-   **requirements.txt**: Lists Python dependencies.

---

## Additional Resources

-   **yt-dlp Documentation**: [https://github.com/yt-dlp/yt-dlp](https://github.com/yt-dlp/yt-dlp)
-   **ffmpeg Documentation**: [https://ffmpeg.org/documentation.html](https://ffmpeg.org/documentation.html)
-   **Python Virtual Environments**: [https://docs.python.org/3/library/venv.html](https://docs.python.org/3/library/venv.html)
-   **Makefile Basics**: [GNU Make Manual](https://www.gnu.org/software/make/manual/make.html)
