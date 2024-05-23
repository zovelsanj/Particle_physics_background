This documentation focuses solely on the setup of `ROOT` in Ubuntu with pre-compiled binary and executing `ROOT C++` programs with Visual Studio Code. 
`ROOT` can be installed either from source or from pre-compiled binary packages.
For more deatils refer to [official documentation](https://root.cern/install/).

# Install `ROOT`
On most Linux distros (tested on Ubuntu 22.04), `ROOT` can be installed with `snap` as follows:
```
sudo snap install root-framework
```

After the installation, `ROOT` CLI can be directly accessed via alias `root`. In the case of any other conflicting installations, following command can be used:
```
snap run root-framework
```

With `snap`, the installation locations are as follows:
```
Include Dir: /snap/root-framework/931/usr/local/include/
Compiler: /snap/bin/root or /snap/bin/root.exe
```

You may also find the same include files at `/snap/root-framework/current/usr/local/include/`, this is because `current` is the `symlink` of `931`.

# Setup in VS Code
Since VS Code, has many programming-friendly features such as IntelliSense, Debugger, etc., it is much convenient to use VS Code instead of traditional commandline-based editors and gedit. To use the `ROOT C++` libraries in VS Code you just need to set the include dir path at `Inlcude Path` in `C/C++ Configurations` as shown below:
![vscode_setup](../../images/vscode_setup.png)

This is a simple way to leverage the `ROOT C++` libraries with VS Code. However, there other ways to setup such as [autocompletion-with-vs-code](https://root-forum.cern.ch/t/autocompletion-with-vs-code/38188/3) and [root-on-vscode](https://github.com/AlbertoPdRF/root-on-vscode/blob/master/.vscode/launch.json).

After the setup, you will see the `IntelliSense` working as shown below.
![intellisense](../../images/intellisense.png)
![intellisense](../../images/intellisense-1.png)

# Useful References
1. [C++ codes documentation](https://root.cern/doc/master/group__tutorial__hist.html)
2. [ROOT Primer](https://root.cern/primer/#interpretation-and-compilation)
3. [Tutorial for Summer Students](https://indico.cern.ch/event/395198/)
4. [Physics Matters Youtube Tutorial](https://www.youtube.com/watch?v=KPz-dNjdx40&list=PLLybgCU6QCGWLdDO4ZDaB0kLrO3maeYAe)