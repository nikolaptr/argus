# ARGUS Ground Station

An open source ESP-IDF based ground station.

## Building it yourself

Please follow the steps:

1. Configure [ESP-IDF Extension for VS Code](https://github.com/espressif/vscode-esp-idf-extension/blob/master/README.md).

2. Clone the ARGUS Ground Station and open project using VS Code.

3. Bring up VS Code command pallete (`Ctrl + Shift + P`) and run `ESP-IDF: Add vscode configuration folder`.

    > NOTE: This step is needed to initialize `c_cpp_properties.json` used by
    C/C++ extension.

4. Refer to [Using the ESP-IDF Extension for VS Code](https://github.com/espressif/vscode-esp-idf-extension/blob/master/README.md#using-the-esp-idf-extension-for-vs-code) to learn how to use ESP-IDF extension.

## How to contribute

Feel free to contribute to this project! You just need to follow next steps:

1. **[Fork](https://docs.github.com/en/pull-requests/collaborating-with-pull-requests/working-with-forks/fork-a-repo) ARGUS Ground
Station**

2. **Configure code formatting tools:**

    ARGUS Ground Station uses `pre-commit` and `clang-format` to maintain
    consistent code formatting. Before committing your changes, ensure that your
    code is properly formatted.

    * **Install [pre-commit](https://pre-commit.com/):**
    ```
    pip install pre-commit
    ```

    * **Install Git Hooks:**
    ```
    pre-commit install
    ```

    * **Install [clang-format](https://clang.llvm.org/docs/ClangFormat.html):**

        * **Linux**: `sudo apt-get install clang-format`
        * **MacOS**: `brew install clang-format`
        * **Windows**: Download from [LLVM's website](https://llvm.org/)

    Once set up, `pre-commit` will automatically run `clang-format` on your
    code before each commit, ensuring consistent formatting.

3. **Create a new branch:**
    ```
    git checkout -b feat/your-feature-name
    ```

4. **Commit your changes**
    ```
    git add .
    git commit -m "Commit message"
    ```

    > NOTE: To keep everything consistent we use [Conventional commits](https://www.conventionalcommits.org/en/v1.0.0/)

5. **Push your branch to your fork:**
    ```
    git push origin feat/your-feature-name
    ```

6. **Submit a Poll Request**

Thank you for your contribution!