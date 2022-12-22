# libE57Format

[![GitHub release (latest by date)](https://img.shields.io/github/v/release/asmaloney/libE57Format)](https://github.com/asmaloney/libE57Format/releases/latest) [![Docs](https://img.shields.io/badge/docs-online-orange)](https://asmaloney.github.io/libE57Format-docs/) [![GitHub](https://img.shields.io/github/license/asmaloney/libE57Format)](LICENSE) ![Build](https://github.com/asmaloney/libE57Format/actions/workflows/build.yml/badge.svg)

libE57Format is a library which provides read & write support for the E57 file format.

## 🚨 Version 3.0 Note 🚨

There have been many changes (especially to the "Simple API") in the upcoming version 3.0 - some of which will require code changes on your end. Please see the [CHANGELOG](CHANGELOG.md) for details.

Since this version is breaking the API, I am happy to discuss any other API-breaking changes which might be useful. Please raise them in [this issue](https://github.com/asmaloney/libE57Format/issues/177).

I plan to let 3.0 sit in the master branch until the end of 2022. If I don't hear any feedback I will go ahead and release it as-is.

## Documentation

The doxygen-generated documentation may be [found here](https://asmaloney.github.io/libE57Format-docs/). These docs are generated and saved in the [libE57Format-docs](https://github.com/asmaloney/libE57Format-docs) repo.

## Build, Install, & Test

Here's how you build & install a release version with the defaults:

```
$ cmake -B E57-build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=E57-install libE57Format
$ cmake --build E57-build --parallel
$ cmake --install E57-build
```

If it can't find the xerces-c library, you can set [CMAKE_PREFIX_PATH](https://cmake.org/cmake/help/latest/variable/CMAKE_PREFIX_PATH.html) to point at it.

```
$ cmake -B E57-build \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=E57-install \
    -DCMAKE_PREFIX_PATH=/path/to/xerces-c \
    libE57Format
```

Once the library is built, you can run the tests like this:

```
$ cd E57-build
$ ./test/testE57
[==========] Running 36 tests from 8 test suites.
[----------] Global test environment set-up.
[----------] 1 test from TestData
[ RUN      ] TestData.RepoExists
...
```

### Dependencies

- [ccache](https://ccache.dev/) (optional): speed up rebuilds using caching
- [clang-format](https://clang.llvm.org/docs/ClangFormat.html): for code formatting
- [Xerces-C++](https://xerces.apache.org/xerces-c/): a validating XML parser

#### Installing Dependencies On Linux (Ubuntu)

```sh
$ sudo apt install libxerces-c-dev clang-format
```

#### Installing Dependencies On macOS (homebrew)

```sh
$ brew install ccache clang-format xerces-c
```

## 🍴 Fork

This is a fork of [E57RefImpl](https://sourceforge.net/projects/e57-3d-imgfmt/). The original source is from [E57RefImpl 1.1.332](https://sourceforge.net/projects/e57-3d-imgfmt/files/E57Refimpl-src/).

The original code had not been touched in years and I wanted to make changes to compile it on macOS. Forking it gave me a bit more freedom to update the code and make changes as required. Everything was stripped out except the main implementation for reading & writing E57.

Notes:

- I changed the name of the project so that it is not confused with the **E57RefImpl** project.
- I changed the main include file's name from `E57Foundation.h` to `E57Format.h` to make sure there is no inclusion confusion.
- Versions of **libE57Format** started at 2.0.
- I made changes for it to compile and run on macOS.
- It no longer depends on [Boost](http://www.boost.org/).
- It now requires [C++14](https://en.cppreference.com/w/cpp/14). (Version 2.x required [C++11](https://en.cppreference.com/w/cpp/11).)

Many, many other changes were made prior to the first release of this fork. See the [CHANGELOG](CHANGELOG.md) and git history for details.

### E57Simple API

Since the original fork, [Jiri Hörner](https://github.com/ptc-jhoerner) added the E57Simple API from the old reference implementation and updated it.

This _Simple API_ has evolved since this original port to fix some problems and to make it more foolproof & easier to use. Please see the [CHANGELOG](CHANGELOG.md) for version 3.

### Tools

[Ryan Baumann](https://github.com/ryanfb) updated the `e57unpack` and `e57validate` tools to work with **libE57Format**. You can find them in the [e57tools](https://github.com/ryanfb/e57tools) repo.

## How To Contribute

These are some of the things you can do to contribute to the project:

### ✍ Write About The Project

If you find the project useful, spread the word! Articles, mastodon posts, tweets, blog posts, instagram photos - whatever you're into. Please include a referral back to the repository page: https://github.com/asmaloney/libE57Format

### ⭐️ Add a Star

If you found this project useful, please consider starring it! It helps me gauge how useful this project is.

### ☝ Raise Issues

If you run into something which doesn't work as expected, raising [an issue](https://github.com/asmaloney/libE57Format/issues) with all the relevant information to reproduce it would be helpful.

### 🐞 Bug Fixes & 🧪 New Things

I am happy to review any [pull requests](https://github.com/asmaloney/libE57Format/pulls). Please keep them as short as possible. Each pull request should be atomic and only address one issue. This helps with the review process.

Note that I will not accept everything, but I welcome discussion. If you are proposing a big change, please raise it as [an issue](https://github.com/asmaloney/libE57Format/issues) first for discussion.

#### Formatting

This project uses [clang-format](https://clang.llvm.org/docs/ClangFormat.html) to format the code. There is a cmake target (_e57-clang-format_) - which runs _clang-format_ on the source files. After changes have been made, and before you submit your pull request, please run the following:

```sh
cmake --build . --target e57-clang-format
```

### 📖 Documentation

The [documentation](https://github.com/asmaloney/libE57Format) is a bit old and could use some lovin'. You can submit changes over in the [libE57Format-docs](https://github.com/asmaloney/libE57Format-docs) repository.

### 💰 Financial

Given that I'm an independent developer without funding, financial support is always appreciated. If you would like to support the project financially (especially if you sell a product which uses this library), you can use the [sponsors page](https://github.com/sponsors/asmaloney) for one-off or recurring support. Thank you!

## License

This project as a whole is licensed under the [**BSL-1.0**](https://opensource.org/licenses/BSL-1.0) license - see the [LICENSE](LICENSE.md) file for details.

Individual source files may contain the following tag instead of the full license text:

    SPDX-License-Identifier: BSL-1.0

Some files are licensed under the **MIT** license - see the [LICENSE-MIT](LICENSE-MIT.txt) file for details.

These files contain the following tag instead of the full license text:

    SPDX-License-Identifier: MIT

Using SPDX enables machine processing of license information based on the [SPDX License Identifiers](https://spdx.org/ids) and makes it easier for developers to see at a glance which license they are dealing with.
